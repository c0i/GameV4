
local FDemoView = require ("test.fgui.fdemoview")

local FMenuView = class('FMenuView', FDemoView)

function FMenuView:ctor()
    FMenuView.super:ctor() -- init FDemoView
end

function FMenuView:continueInit()

    print('FMenuView:continueInit')
    local groot = fairygui.GRoot:getInstance()
    fairygui.UIPackage:addPackage("UI/MainMenu")
    local view = fairygui.UIPackage:createObject("MainMenu", "Main")
    groot:addChild(view)

    view:getChild('n1'):onClick(function (ctx)
        require('test.fgui.FBasicsView'):new():run()
    end)

    view:getChild('n2'):onClick(function (ctx)
        require ("test.fgui.FTransitionView"):new():run()
    end)
    view:getChild('n4'):onClick(function (ctx)
        require ("test.fgui.FVirtualListView"):new():run()
    end)

    view:getChild('n5'):onClick(function (ctx)
        require ("test.fgui.FLoopListView"):new():run()
    end)

    view:getChild('n6'):onClick(function (ctx)
        require ("test.fgui.FHitTestView"):new():run()
    end)

    view:getChild('n7'):onClick(function (ctx)
        require ("test.fgui.FPullToRefreshView"):new():run()
    end)

    view:getChild("n8"):onClick(function (ctx)
        require ("test.fgui.FModalWaitingView"):new():run()
    end)
    view:getChild("n9"):onClick(function (ctx)
        require ("test.fgui.FJoystickView"):new():run()
    end)
    view:getChild("n10"):onClick(function (ctx)
        require ("test.fgui.FBagView"):new():run()
    end)
    view:getChild("n11"):onClick(function (ctx)
        require ("test.fgui.FChatView"):new():run()
    end)
    view:getChild("n12"):onClick(function (ctx)
        require ("test.fgui.FListEffectView"):new():run()
    end)
    view:getChild("n13"):onClick(function (ctx)
        require ("test.fgui.FScrollPaneView"):new():run()
    end)
    view:getChild("n14"):onClick(function (ctx)
        require ("test.fgui.FTreeViewView"):new():run()
    end)
    view:getChild("n15"):onClick(function (ctx)
        require ("test.fgui.FGuideView"):new():run()
    end)
    view:getChild("n16"):onClick(function (ctx)
        require ("test.fgui.FCooldownView"):new():run()
    end)
end

return FMenuView
