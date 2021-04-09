local FDemoView = require("test.fgui.fdemoview")

local FGuideView = class("FGuideView", FDemoView)
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
function FGuideView:ctor()
    print("FGuideView create")
    UIRoot = GRoot:getInstance()
end

function FGuideView:continueInit()
    UIPackage:addPackage("UI/Guide")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""

    self._view = UIPackage:createObject("Guide", "Main")
    UIRoot:addChild(self._view)

    self._guideLayer = UIPackage:createObject("Guide", "GuideLayer")
    self._guideLayer:makeFullScreen()
    self._guideLayer:addRelation(UIRoot, RelationType.Size)
    self._guideLayer:retain()

    local bagBtn = self._view:getChild('bagBtn')
    bagBtn:addClickListener(function (ctx)
        self._guideLayer:removeFromParent()
    end)

    self._view:getChild('n2'):onClick(function (ctx)
        UIRoot:addChild(self._guideLayer) -- //!!Before using TransformRect(or GlobalToLocal), the object must be added first
        local size = bagBtn:getSize()
        local rect = bagBtn:transformRect(cc.rect(0, 0, size.width, size.height), self._guideLayer)

        local window = self._guideLayer:getChild('window')
        window:setSize(rect.width, rect.height)

        GTween:to(window:getPosition(), cc.p(rect.x, rect.y), 0.5):setTarget(window, TweenPropType.Position)
    end)

end

return FGuideView
