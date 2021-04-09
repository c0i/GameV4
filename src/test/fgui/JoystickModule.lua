
-- cache fairygui
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GComponent = fairygui.GComponent
local Window = fairygui.Window
local GRoot = fairygui.GRoot
local TweenPropType = fairygui.TweenPropType
local UIEventDispatcher = fairygui.UIEventDispatcher

local atan2 = math.atan2
local abs = math.abs
local cos = math.cos
local sin = math.sin
local M_PI = math.pi

-- JoystickModule

local UIRoot
local JoystickModule = class("JoystickModule", function ()
    return UIEventDispatcher:new()
end)

JoystickModule.MOVE = 100
JoystickModule.END = 101

function JoystickModule:ctor(mainView)
    print("JoystickModule create")

    UIRoot = GRoot:getInstance()

    self._button = mainView:getChild("joystick")
    self._button:setChangeStateOnClick(false)

    self._thumb = self._button:getChild("thumb")
    self._touchArea = mainView:getChild("joystick_touch")
    self._center = mainView:getChild("joystick_center")

    self._InitX = self._center:getX() + self._center:getWidth() / 2
    self._InitY = self._center:getY() + self._center:getHeight() / 2
    self.touchId = -1
    self._radius = 150

    self._touchArea:addEventListener(UIEventType.TouchBegin, handler(self, self.onTouchBegin))
    self._touchArea:addEventListener(UIEventType.TouchMove, handler(self, self.onTouchMove))
    self._touchArea:addEventListener(UIEventType.TouchEnd, handler(self, self.onTouchEnd))

    self._tweener = nil
end

function JoystickModule:onTouchBegin(context)
    print('onTouchBegin', context)
    if (self.touchId == -1) then -- //First touch
        local evt = context:getInput()
        self.touchId = evt:getTouchId()

        if (self._tweener ~= nil) then
            self._tweener:kill()
            self._tweener = nil
        end

        local pt = UIRoot:globalToLocal(evt:getPosition())
        local bx = pt.x
        local by = pt.y
        self._button:setSelected(true)

        if (bx < 0) then
            bx = 0
        elseif (bx > self._touchArea:getWidth()) then
            bx = self._touchArea:getWidth()
        end

        if (by > UIRoot:getHeight()) then
            by = UIRoot:getHeight()
        elseif (by < self._touchArea:getY()) then
            by = self._touchArea:getY()
        end

        self._lastStageX = bx
        self._lastStageY = by
        self._startStageX = bx
        self._startStageY = by

        self._center:setVisible(true)
        self._center:setPosition(bx - self._center:getWidth() / 2, by - self._center:getHeight() / 2)
        self._button:setPosition(bx - self._button:getWidth() / 2, by - self._button:getHeight() / 2)

        local deltaX = bx - self._InitX
        local deltaY = by - self._InitY
        local degrees = atan2(deltaY, deltaX) * 180 / M_PI
        self._thumb:setRotation(degrees + 90)

        context:captureTouch()
    end
end

function JoystickModule:onTouchMove(context)
    print('onTouchMove', context)
    local evt = context:getInput()
    if (self.touchId ~= -1 and evt:getTouchId() == self.touchId) then
        local pt = UIRoot:globalToLocal(evt:getPosition())
        local bx = pt.x
        local by = pt.y
        local moveX = bx - self._lastStageX
        local moveY = by - self._lastStageY
        self._lastStageX = bx
        self._lastStageY = by
        local buttonX = self._button:getX() + moveX
        local buttonY = self._button:getY() + moveY

        local offsetX = buttonX + self._button:getWidth() / 2 - self._startStageX
        local offsetY = buttonY + self._button:getHeight() / 2 - self._startStageY

        local rad = atan2(offsetY, offsetX)
        local degree = rad * 180 / M_PI
        self._thumb:setRotation(degree + 90)

        local maxX = self._radius * cos(rad)
        local maxY = self._radius * sin(rad)
        if (abs(offsetX) > abs(maxX)) then
            offsetX = maxX
        end
        if (abs(offsetY) > abs(maxY)) then
            offsetY = maxY
        end

        buttonX = self._startStageX + offsetX
        buttonY = self._startStageY + offsetY
        if (buttonX < 0) then
            buttonX = 0
        end
        if (buttonY > UIRoot:getHeight()) then
            buttonY = UIRoot:getHeight()
        end

        self._button:setPosition(buttonX - self._button:getWidth() / 2, buttonY - self._button:getHeight() / 2)

        self:dispatchEvent(self.MOVE, self, degree)
    end
end

function JoystickModule:onTouchEnd(ctx)
    print('onTouchEnd', ctx)
end

function JoystickModule:onTouchEnd(context)
    local evt = context:getInput()
    if (self.touchId ~= -1 and evt:getTouchId() == self.touchId) then
        self.touchId = -1
        self._thumb:setRotation(self._thumb:getRotation() + 180)
        self._center:setVisible(false)

        local startPos = self._button:getPosition()
        local endPos = cc.p(self._InitX - self._button:getWidth() / 2, self._InitY - self._button:getHeight() / 2)
        self._tweener = GTween:to(startPos, endPos, 0.3)
            :setTarget(self._button, TweenPropType.Position)
            :onComplete(function()
                self._button:setSelected(false)
                self._thumb:setRotation(0)
                self._center:setVisible(true)
                self._center:setPosition(self._InitX - self._center:getWidth() / 2, self._InitY - self._center:getHeight() / 2)
            end)

        self:dispatchEvent(self.END)
    end
end


return JoystickModule
