local FDemoView = require("test.fgui.fdemoview")

local FModalWaitingView = class("FModalWaitingView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GComponent = fairygui.GComponent
local Window = fairygui.Window

-- FModalWaitingView

function FModalWaitingView:ctor()
    print("FModalWaitingView create")
end

function FModalWaitingView:continueInit()
    UIPackage:addPackage("UI/ModalWaiting")
    UIConfig.globalModalWaiting = "ui://ModalWaiting/GlobalModalWaiting"
    UIConfig.windowModalWaiting = "ui://ModalWaiting/WindowModalWaiting"

    self._view = UIPackage:createObject("ModalWaiting", "Main")
    self.groot:addChild(self._view)

    self._testWin = Window:create()
    self._testWin:retain()
    self._testWin:setContentPane(UIPackage:createObject("ModalWaiting", "TestWin"))
    self._testWin:getContentPane():getChild("n1"):addClickListener(function()
        self._testWin:showModalWait()
        -- //simulate a asynchronous request
        self._testWin:delayCall(3, function()
            self._testWin:closeModalWait()
        end)
    end)

    self._view:getChild("n0"):addClickListener(function() self._testWin:show() end)

    self.groot:showModalWait()

    -- //simulate a asynchronous request
    self._testWin:delayCall(3, function()
        self.groot:closeModalWait()
    end)
end

return FModalWaitingView
