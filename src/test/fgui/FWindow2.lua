
local FWindow2 = class('FWindow2', function ()
    return fairygui.Window:create()
end)

local GTween = fairygui.GTween
local UIPackage = fairygui.UIPackage
local UIEventType = fairygui.UIEventType

function FWindow2:ctor()
    print(tolua.type(self))
    self:addEventListener(UIEventType.OnInit, handler(self, self.onInit))

    self.doShowAnimationDelegate = handler(self, self.doShowAnimation)
    self.doHideAnimationDelegate = handler(self, self.doHideAnimation)
end

function FWindow2:onInit()
    print('FWindow2.OnInit')
    self:setContentPane(UIPackage:createObject('Basics', 'WindowB'))
    self:center()
end

function FWindow2:doShowAnimation()
    self:setScale(0.1, 0.1)
    self:setPivot(0.5, 0.5)

    GTween:to(self:getScale(), cc.p(1, 1), 0.3)
    :setTarget(self, fairygui.TweenPropType.Scale)
    :onComplete(handler(self, self.onShown))
 end

function FWindow2:doHideAnimation()
    GTween:to(self:getScale(), cc.p(0.1, 0.1), 0.3)
    :setTarget(self, fairygui.TweenPropType.Scale)
    :onComplete(handler(self, self.hideImmediately))
end

function FWindow2:onShown()
    print('FWindow2.onShow')
    self:getContentPane():getTransition('t1'):play()
end

function FWindow2:onHide()
    print('FWindow2.onHide()')
    self:getContentPane():getTransition('t1'):stop()

    self:doHideAnimation()
end

return FWindow2
