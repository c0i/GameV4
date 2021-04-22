
local FDemoView = require ("test.fgui.FDemoView")

local FTransitionView = class('FTransitionView', FDemoView)
local UIPackage = fairygui.UIPackage
local GTween = fairygui.GTween

function FTransitionView:ctor()
    print('FTransitionView create')
end

function FTransitionView:continueInit()
    print('%p', self)
    self.index = 111
    UIPackage:addPackage("UI/Transition")
    local view = UIPackage:createObject('Transition', 'Main')
    self.groot:addChild(view)

    self._btnGroup = view:getChild("g0")
    print('self._btnGroup', tolua.type(self._btnGroup))

    self._g1 = UIPackage:createObject("Transition", "BOSS")
    self._g1:retain()
    self._g2 = UIPackage:createObject("Transition", "BOSS_SKILL")
    self._g2:retain()
    self._g3 = UIPackage:createObject("Transition", "TRAP")
    self._g3:retain()
    self._g4 = UIPackage:createObject("Transition", "GoodHit")
    self._g4:retain()
    self._g5 = UIPackage:createObject("Transition", "PowerUp")
    self._g5:retain()
    self._g5:getTransition("t0"):setHook("play_num_now", handler(self, self.playNum))
    self._g6 = UIPackage:createObject("Transition", "PathDemo")
    self._g6:retain()

    view:getChild("btn0"):addClickListener(function ()
        self:__play(self._g1)
    end)
    view:getChild("btn1"):addClickListener(function ()
        self:__play(self._g2)
    end)
    view:getChild("btn2"):addClickListener(function ()
        self:__play(self._g3)
    end)
    view:getChild("btn3"):addClickListener(function (ctx)
        self:__play4(ctx)
    end)
    view:getChild("btn4"):addClickListener(function (ctx)
        self:__play5(ctx)
    end)
    view:getChild("btn5"):addClickListener(function ()
        self:__play(self._g6)
    end)
end


function FTransitionView:__play(target)
    self._btnGroup:setVisible(false)
    self.groot:addChild(target)
    local t = target:getTransition("t0")
    t:play(function ()
        self._btnGroup:setVisible(true)
        self.groot:removeChild(target)
    end)
end

function FTransitionView:__play4( context)
    self._btnGroup:setVisible(false)
    self._g4:setPosition(self.groot:getWidth() - self._g4:getWidth() - 20, 100)
    self.groot:addChild(self._g4)
    local t = self._g4:getTransition("t0")
    t:play(3, 0, function ()
        self._btnGroup:setVisible(true)
        self.groot:removeChild(self._g4)
    end)
end

function FTransitionView:__play5( context)
    self._btnGroup:setVisible(false)
    self._g5:setPosition(20, self.groot:getHeight() - self._g5:getHeight() - 100)
    self.groot:addChild(self._g5)
    local t = self._g5:getTransition("t0")
    self._startValue = 10000
    local add = 1000 --+ rand_0_1() * 2000
    self._endValue = self._startValue + add
    self._g5:getChild("value"):setText(self._startValue)
    self._g5:getChild("add_value"):setText(add)
    t:play(function ()
        self._btnGroup:setVisible(true)
        self.groot:removeChild(self._g5)
    end)
end

function FTransitionView:playNum()
    local tweener = GTween:to(self._startValue, self._endValue, 0.3)
    tweener:onUpdate(function (tweener)
        print('tweener.value.x', tweener.value.x)
        self._g5:getChild('value'):setText(math.floor(tweener.value.x))
    end)
end


return FTransitionView
