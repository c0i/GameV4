
local FDemoView = class('FDemoView')

function FDemoView:ctor()
    self.groot = fairygui.GRoot:getInstance()
end

function FDemoView:continueInit()
end

function FDemoView:init()
    self.groot:setWidth(display.width)
    self.groot:setHeight(display.height)

    print('w,h', self.groot:getHeight(), self.groot:getWidth())
    self:continueInit()

    local groot = fairygui.GRoot:getInstance()
    -- add a closeButton to scene
    local closeButton = fairygui.UIPackage:createObject("MainMenu", "CloseButton")
    closeButton:setPosition(groot:getWidth() - closeButton:getWidth() - 10, groot:getHeight() - closeButton:getHeight() - 10);
    closeButton:addRelation(groot, fairygui.RelationType.Right_Right)
    closeButton:addRelation(groot, fairygui.RelationType.Bottom_Bottom);
    closeButton:setSortingOrder(100000)
    closeButton:onClick(function ( ... )
        print('click button')
        require('test/fgui/fmenuview').new():run()
    end)
    groot:addChild(closeButton)
end

function FDemoView:run()
    self.groot:removeChildren()
    print("fgui groot's children count" , self.groot:numChildren())
    self:init()
end

return FDemoView
