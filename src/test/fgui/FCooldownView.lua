local FDemoView = require("test.fgui.fdemoview")

local FCooldownView = class("FCooldownView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GRoot = fairygui.GRoot
local GTreeNode = fairygui.GTreeNode
local RelationType = fairygui.RelationType
local TweenPropType = fairygui.TweenPropType

local tools = require ("tools.tools")

local UIRoot 
function FCooldownView:ctor()
    print("FCooldownView create")
    UIRoot = GRoot:getInstance()
end

function FCooldownView:continueInit()
    UIPackage:addPackage("UI/Cooldown")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""

    dump(UIEventType)
    self._view = UIPackage:createObject("Cooldown", "Main")
    self._view:on(UIEventType.Exit, handler(self, self.onExit))
    self._view:on(UIEventType.Enter, handler(self, self.onEnter)) -- before add to renderer list
    self._view:on(UIEventType.OnDestroy, handler(self, self.onDestroy)) -- before add to renderer list


    UIRoot:addChild(self._view)

    local btn0 = self._view:getChild("b0")
    local btn1 = self._view:getChild("b1")
    btn0:getChild("icon"):setIcon("icons/k0.png")
    btn1:getChild("icon"):setIcon("icons/k1.png")

    GTween:to(0, 100, 5):setTarget(btn0, TweenPropType.Progress):setRepeat(-1)
    GTween:to(10, 0, 10):setTarget(btn1, TweenPropType.Progress):setRepeat(-1)

end

function FCooldownView:onExit()
    print('> onExit')
end

function FCooldownView:onEnter()
    print('> onEnter')
end

function FCooldownView:onDestroy()
    print('> onDestroy')
end

return FCooldownView
