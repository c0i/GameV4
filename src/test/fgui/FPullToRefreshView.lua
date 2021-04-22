local FDemoView = require("test.fgui.FDemoView")

local FPullToRefreshView = class("FPullToRefreshView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GComponent = fairygui.GComponent

-- ScrollPaneHeader

local ScrollPaneHeader = class('ScrollPaneHeader', function ()
    return GComponent:create()
end)

function ScrollPaneHeader:ctor()
    self:on(UIEventType.OnConstruct, handler(self, self.onConstruct))
end

function ScrollPaneHeader:isReadyToRefresh()
    return self._c1:getSelectedIndex() == 1
end

function ScrollPaneHeader:onConstruct()
    self._c1 = self:getController("c1")

    self:addEventListener(UIEventType.SizeChange,  handler(self, self.onSizeChanged))
end

function ScrollPaneHeader:onSizeChanged(ctx)
    print('>onSizeChanged')
    if (self._c1:getSelectedIndex() == 2 or self._c1:getSelectedIndex() == 3) then
        return
    end

    if (self:getHeight() > self.sourceSize.height) then
        self._c1:setSelectedIndex(1)
    else
        self._c1:setSelectedIndex(0)
    end
end

function ScrollPaneHeader:setRefreshStatus(value)
    self._c1:setSelectedIndex(value)
end

-- FPullToRefreshView

function FPullToRefreshView:ctor()
    print("FPullToRefreshView create")
end

function FPullToRefreshView:continueInit()
    UIPackage:addPackage("UI/PullToRefresh")
    UIObjectFactory:setPackageItemExtension("ui://PullToRefresh/Header", function () return ScrollPaneHeader:create() end)

    self._view = UIPackage:createObject("PullToRefresh", "Main")
    self.groot:addChild(self._view)

    self._list1 = self._view:getChild("list1")
    self._list1.itemRenderer = handler(self, self.renderListItem1)
    self._list1:setVirtual()
    self._list1:setNumItems(1)
    self._list1:addEventListener(UIEventType.PullDownRelease, handler(self, self.onPullDownToRefresh))

    self._list2 = self._view:getChild("list2")
    self._list2.itemRenderer = handler(self, self.renderListItem2)
    self._list2:setVirtual()
    self._list2:setNumItems(1)
    self._list2:addEventListener(UIEventType.PullUpRelease, handler(self, self.onPullUpToRefresh))
end

function FPullToRefreshView:renderListItem1(index, obj)
    obj:setText("Item " .. (self._list1:getNumItems() - index - 1))
end

function FPullToRefreshView:renderListItem2(index, obj)
    obj:setText("Item " .. index)
end

function FPullToRefreshView:onPullDownToRefresh(ctx)
    print('onPullDownToRefresh')
    local header = self._list1:getScrollPane():getHeader()
    print(tolua.type(header))

    if header:isReadyToRefresh() then
        header:setRefreshStatus(2)
        self._list1:getScrollPane():lockHeader(header.sourceSize.height)

        -- -- //Simulate a async resquest
        header:delayCall(2, function ()
            print('delay 2')
            self._list1:setNumItems(self._list1:getNumItems() + 5)

            -- //Refresh completed
            header:setRefreshStatus(3)
            self._list1:getScrollPane():lockHeader(35)

            header:delayCall(2, function ()
                header:setRefreshStatus(0)
                self._list1:getScrollPane():lockHeader(0)
            end)
        end)
    end
end

function FPullToRefreshView:onPullUpToRefresh(ctx)
    print('onPullUpToRefresh')
    local footer = self._list2:getScrollPane():getFooter()

    footer:getController("c1"):setSelectedIndex(1)
    self._list2:getScrollPane():lockFooter(footer.sourceSize.height)

    -- //Simulate a async resquest

    footer:delayCall(2, function ()
        self._list2:setNumItems(self._list2:getNumItems() + 5)

        -- //Refresh completed
        footer:getController("c1"):setSelectedIndex(0)
        self._list2:getScrollPane():lockFooter(0)
    end)
end


return FPullToRefreshView
