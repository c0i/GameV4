local FDemoView = require("test.fgui.FDemoView")

local FBagView = class("FBagView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GComponent = fairygui.GComponent
local Window = fairygui.Window

local BagWindow = require ("test.fgui.BagWindow")

-- FBagView

function FBagView:ctor()
    print("FBagView create")
end

function FBagView:continueInit()
    UIPackage:addPackage("UI/Bag")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""

    self._view = UIPackage:createObject("Bag", "Main")
    self.groot:addChild(self._view)

    self._bagWindow = BagWindow:create()
    self._bagWindow:retain()
    self._view:getChild("bagBtn"):addClickListener(function()  self._bagWindow:show() end)
end

return FBagView
