

local Window = fairygui.Window
local GTween = fairygui.GTween
local UIPackage = fairygui.UIPackage
local UIEventType = fairygui.UIEventType
local TweenPropType = fairygui.TweenPropType


local BagWindow = class('BagWindow', function ()
    return Window:create()
end)

function BagWindow:ctor()
    print(tolua.type(self))
    self:addEventListener(UIEventType.OnInit, handler(self, self.onInit))
    self:addEventListener(UIEventType.OnShown, handler(self, self.onShown))
    self:addEventListener(UIEventType.OnHide, handler(self, self.onHide))
    self.doHideAnimationDelegate = handler(self, self.doHideAnimation)
    self.doShowAnimationDelegate = handler(self, self.doShowAnimation)
end

function BagWindow:onInit()
    print('BagWindow.OnInit')
    self:setContentPane(UIPackage:createObject('Bag', 'BagWin'))
    self:center()
    self:setModal(true)

    self._list = self:getContentPane():getChild("list")
    self._list:addEventListener(UIEventType.ClickItem, handler(self, self.onClickItem))
    self._list.itemRenderer = handler(self, self.renderListItem)
    self._list:setNumItems(45)
end

function BagWindow:renderListItem(index, obj)
    obj:setIcon("icons/i" .. (math.random(1, 10)-1) .. ".png")
    obj:setText(math.random(1, 100))
end

function BagWindow:onShown()
    print('>onShow')
end
function BagWindow:onHide()
    print('>onHide')
end

function BagWindow:doShowAnimation()
    self:setScale(0.1, 0.1)
    self:setPivot(0.5, 0.5)

    GTween:to(self:getScale(), cc.p(1,1), 0.3)
    :setTarget(self, TweenPropType.Scale)
    :onComplete(handler(self, self.onShown))
end

function BagWindow:doHideAnimation()
    --@FIXME: hideImmediately

    GTween:to(self:getScale(), cc.p(0.1, 0.1), 0.3)
    :setTarget(self, TweenPropType.Scale)
    -- :onUpdate(function (ctx)
    --     local value = ctx.value
    --     print(value.x, value.y)
    -- end)
    :onComplete(handler(self, self.hideImmediately))
end

function BagWindow:onClickItem(context)
    local item = context:getData() --tolua.cast(context:getData(), 'fairygui.GObject')
    print('item', tolua.type(item), tolua.type(context))
    self:getContentPane():getChild("n11"):setIcon(item:getIcon())
    self:getContentPane():getChild("n13"):setText(item:getText())
end

return BagWindow
