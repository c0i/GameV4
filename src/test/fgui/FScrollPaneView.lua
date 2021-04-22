local FDemoView = require("test.fgui.FDemoView")

local FScrollPaneView = class("FScrollPaneView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GRoot = fairygui.GRoot

local tools = require ("tools.tools")

local UIRoot
function FScrollPaneView:ctor()
    print("FScrollPaneView create")
    UIRoot = GRoot:getInstance()
end

function FScrollPaneView:continueInit()
    UIPackage:addPackage("UI/ScrollPane")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""

    self._view = UIPackage:createObject("ScrollPane", "Main")
    UIRoot:addChild(self._view)

    self._list = self._view:getChild("list")
    self._list.itemRenderer = handler(self, self.renderListItem)
    self._list:setVirtual()
    self._list:setNumItems(1000)
    self._list:addEventListener(UIEventType.TouchBegin, handler(self, self.onClickList))
end

function FScrollPaneView:renderListItem(index, obj)
    local item = obj
    item:setTitle("Item " .. index)
    item:getScrollPane():setPosX(0) -- //reset scroll pos

    local eventTag = tools.getAddr(self)
    -- //Be carefull, RenderListItem is calling repeatedly, add tag to avoid adding duplicately.
    item:getChild("b0"):addClickListener(handler(self, self.onClickStick), eventTag)-- CC_CALLBACK_1(FScrollPaneView:onClickStick, this), EventTag(this))
    item:getChild("b1"):addClickListener(handler(self, self.onClickDelete), eventTag)-- CC_CALLBACK_1(FScrollPaneView:onClickDelete, this), EventTag(this))
end

function FScrollPaneView:onClickStick(context)
    self._view:getChild("txt"):setText("Stick " .. context:getSender():getParent():getText())
end

function FScrollPaneView:onClickDelete(context)
    self._view:getChild("txt"):setText("Delete " .. context:getSender():getParent():getText())
end

function FScrollPaneView:onClickList(context)
    -- //find out if there is an item in edit status
    local cnt = self._list:numChildren()
    for i = 0, cnt-1 do
        -- body
        local item = self._list:getChildAt(i)
        if (item:getScrollPane():getPosX() ~= 0) then
            -- //Check if clicked on the button
            if (item:getChild("b0"):isAncestorOf(UIRoot:getTouchTarget())
                or item:getChild("b1"):isAncestorOf(UIRoot:getTouchTarget())) then
                return
            end
            item:getScrollPane():setPosX(0, true)
            -- //avoid scroll pane default behavior
            item:getScrollPane():cancelDragging()
            self._list:getScrollPane():cancelDragging()
            break
        end
    end
end

return FScrollPaneView
