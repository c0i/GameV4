local FDemoView = require("test.fgui.FDemoView")

local FMailItem = require ("test.fgui.FMailItem")
local FListEffectView = class("FListEffectView", FDemoView)

local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GComponent = fairygui.GComponent
local Window = fairygui.Window
local PopupDirection = fairygui.PopupDirection
local GRoot = fairygui.GRoot


local UIRoot

-- FListEffectView


function FListEffectView:ctor()
    print("FListEffectView create")
    UIRoot = GRoot:getInstance()
end

function FListEffectView:continueInit()
    UIPackage:addPackage("UI/Extension")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""
    UIObjectFactory:setPackageItemExtension("ui://Extension/mailItem", function() return FMailItem:create() end)

    self._view = UIPackage:createObject("Extension", "Main")
    UIRoot:addChild(self._view)

    self._list = self._view:getChild("mailList")

    for i = 0, 9 do
        local item = self._list:addItemFromPool()
        item:setFetched(i % 3 == 0)
        item:setRead(i % 2 == 0)
        item:setTime("5 Nov 2015 16:24:33")
        item:setTitle("Mail title here")
    end

    self._list:ensureBoundsCorrect()
    local delay = 1.0
    for i = 0, 9 do
        local item = self._list:getChildAt(i)
        if (self._list:isChildInView(item)) then
            item:playEffect(delay)
            delay =  delay + 0.2
        else
            break
        end
    end
end

return FListEffectView
