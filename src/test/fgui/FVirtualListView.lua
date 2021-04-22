
local FDemoView = require ("test.fgui.FDemoView")

local FVirtualListView = class('FVirtualListView', FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory

local FMailItem = require ("test.fgui.FMailItem")

function FVirtualListView:ctor()
    print('FVirtualListView create')
end

function FVirtualListView:continueInit()
    UIPackage:addPackage("UI/VirtualList")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""
    UIObjectFactory:setPackageItemExtension("ui://VirtualList/mailItem", function ()
        print('help me')
        return FMailItem:new()
    end)

    local _list
    local _view = UIPackage:createObject("VirtualList", "Main")
    self.groot:addChild(_view)

    _view:getChild("n6"):addClickListener(function () _list:addSelection(500, true) end)
    _view:getChild("n7"):addClickListener(function () _list:getScrollPane():scrollTop() end)
    _view:getChild("n8"):addClickListener(function () _list:getScrollPane():scrollBottom() end)

    _list = _view:getChild("mailList")
    _list.itemRenderer = handler(self, self.renderListItem)
    _list:setVirtual()
    _list:setNumItems(1000)
end

function FVirtualListView:renderListItem(index, obj)
    print('renderListItem', index)
    local item = obj
    item:setFetched(index % 3 == 0)
    item:setRead(index % 2 == 0)
    item:setTime("2021 04/32 16:24:33")
    item:setText(index .. " Mail title here")
end

return FVirtualListView
