local FDemoView = require("test.fgui.FDemoView")

local FHitTestView = class("FHitTestView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType

function FHitTestView:ctor()
    print("FHitTestView create")
end

function FHitTestView:continueInit()
    UIPackage:addPackage("UI/HitTest")

    self._view = UIPackage:createObject("HitTest", "Main")
    self.groot:addChild(self._view)
end

return FHitTestView
