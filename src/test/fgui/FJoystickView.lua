local FDemoView = require("test.fgui.fdemoview")

local FJoystickView = class("FJoystickView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GComponent = fairygui.GComponent
local Window = fairygui.Window

local JoystickModule = require ("test.fgui.JoystickModule")

-- FJoystickView

function FJoystickView:ctor()
    print("FJoystickView create")
end

function FJoystickView:continueInit()
    UIPackage:addPackage("UI/Joystick")

    self._view = UIPackage:createObject("Joystick", "Main")
    self.groot:addChild(self._view)

    self._joystick = JoystickModule:create(self._view)
    self._joystick:retain() -- @FIXME: how to release

    local tf = self._view:getChild("n9")

    self._joystick:addEventListener(JoystickModule.MOVE, function(ctx) 
        dump(ctx, 'MOVE')
        tf:setText(ctx:getDataValue())
    end)

    self._joystick:addEventListener(JoystickModule.END, function(ctx) 
        dump(ctx, 'END')
        tf:setText("")
    end)
end

return FJoystickView
