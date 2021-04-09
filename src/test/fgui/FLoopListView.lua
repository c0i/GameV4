local FDemoView = require("test.fgui.fdemoview")

local FLoopListView = class("FLoopListView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType

function FLoopListView:ctor()
    print("FLoopListView create")
end

function FLoopListView:continueInit()
    UIPackage:addPackage("UI/LoopList")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""

    self._view = UIPackage:createObject("LoopList", "Main")
    self.groot:addChild(self._view)

    self._list = self._view:getChild("list")
    self._list.itemRenderer = handler(self, self.renderListItem)
    self._list:setVirtualAndLoop()
    self._list:setNumItems(5)
    self._list:on(UIEventType.Scroll, handler(self, self.doSpecialEffect))

    self:doSpecialEffect()
end

function FLoopListView:renderListItem(index, obj)
    print("renderListItem", index)
    obj:setPivot(0.5, 0.5)
    obj:setIcon("ui://LoopList/n" .. (index + 1))
end

function FLoopListView:doSpecialEffect(ctx)
    print("doSpecialEffect")

    -- //change the scale according to the distance to middle
    local midX = self._list:getScrollPane():getPosX() + self._list:getViewWidth() / 2
    local cnt = self._list:numChildren()
    for i = 0, cnt - 1 do
        local obj = self._list:getChildAt(i)
        local dist = math.abs(midX - obj:getX() - obj:getWidth() / 2)
        if (dist > obj:getWidth()) then
            obj:setScale(1, 1)
        else
            local ss = 1 + (1 - dist / obj:getWidth()) * 0.24
            obj:setScale(ss, ss)
        end
    end

    self._view:getChild("n3"):setText((self._list:getFirstChildInView() + 1) % self._list:getNumItems())
end

return FLoopListView
