
local FDemoView = require ("test.fgui.fdemoview")

local FBasicsView = class('FBasicsView', FDemoView)
local fgui = fairygui

function FBasicsView:ctor()
    print('FBasicsView create')
    self._demoObjects = {}
end

function FBasicsView:continueInit()

    fgui.UIConfig.buttonSound = "ui://Basics/click"
    fgui.UIConfig.verticalScrollBar = "ui://Basics/ScrollBar_VT";
    fgui.UIConfig.horizontalScrollBar = "ui://Basics/ScrollBar_HZ";
    fgui.UIConfig.tooltipsWin = "ui://Basics/WindowFrame";
    fgui.UIConfig.popupMenu = "ui://Basics/PopupMenu";

    fgui.UIPackage:addPackage("UI/Basics");
    local view = fgui.UIPackage:createObject('Basics', 'Main')
    self.groot:addChild(view)


    local backBtn = view:getChild('btn_Back')
    backBtn:setVisible(false)
    backBtn:addClickListener(function (ctx)
        print('click back')
        self._cc:setSelectedIndex(0)
        backBtn:setVisible(false)
    end)
    self.backBtn = backBtn


    self._demoContainer = view:getChild("container")
    self._cc = view:getController("c1")

    local cnt = view:numChildren()
    for index = 0, cnt-1 do
        local obj = view:getChildAt(index)
        print('obj', tolua.type(obj))
        if (obj:getGroup() and obj:getGroup().name == 'btns') then
            print(obj:getGroup().name)
            obj:addClickListener(handler(self, self.runDemo))
        end
    end
end

function FBasicsView:runDemo(ctx)
    local name = ctx:getSender().name
    local type = name:sub(5, name:len())
    local obj = fgui.UIPackage:createObject("Basics", "Demo_" .. type)
    self._demoObjects[type] = obj

    self._demoContainer:removeChildren()
    self._demoContainer:addChild(obj)
    self._cc:setSelectedIndex(1)
    self.backBtn:setVisible(true)

    print('type:', type)
    if type == 'Text' then
        self:playText()
    elseif type == 'Depth' then
        self:playDepth()
    elseif type == 'Window' then
        self:playWindow()
    elseif type == 'Drag&Drop' then
        self:playDragDrop()
    elseif type == 'Popup' then
        self:playPopup()
    elseif type == 'ProgressBar' then
        self:playProgress()
    end
end

function FBasicsView:playText()
    local obj = self._demoObjects['Text']

    obj:getChild('n12'):on(fairygui.UIEventType.ClickLink, function (ctx)
        local t = ctx:getSender()
        print(ctx:getDataValue(), tolua.type(ctx))
        local text = ctx:getDataValue() -- @FIXME: 曾经出现过 bug
        t:setText('[img]ui://Basics/pet[/img][color=#FF0000]You click the link[/color]:' .. text)
    end)
    obj:getChild("n25"):addClickListener(function (ctx)
        obj:getChild("n24"):setText(obj:getChild("n22"):getText());
    end)
end

function FBasicsView:playDepth()
    local obj = self._demoObjects['Depth']
    local testContainer = obj:getChild('n22')
    local fixedObj = testContainer:getChild('n0')
    fixedObj:setSortingOrder(100)
    fixedObj:setDraggable(true)

    local numChildren = testContainer:numChildren()
    local i = 0
    while i < numChildren do
        local child = testContainer:getChildAt(i)
        if child ~= fixedObj then
            testContainer:removeChildAt(i)
            numChildren = numChildren - 1
        else
            i = i + 1
        end
    end

    local startPos = fixedObj:getPosition()
    obj:getChild('btn0'):onClick(function (ctx)
        local graph = fgui.GGraph:create()
        startPos.x = startPos.x + 10
        startPos.y = startPos.y + 10
        graph:setPosition(startPos.x, startPos.y);
        graph:drawRect(150, 150, 1,  cc.c4f(0,0,0,1), cc.c4f(1,0,0,1))
        obj:getChild('n22'):addChild(graph)
    end)

    obj:getChild('btn1'):onClick(function (ctx)
        local graph = fgui.GGraph:create()
        startPos.x = startPos.x + 10
        startPos.y = startPos.y + 10
        graph:setPosition(startPos.x, startPos.y);
        graph:drawRect(150, 150, 1,  cc.c4f(0,0,0,1), cc.c4f(0,1,0,1))
        graph:setSortingOrder(200)
        obj:getChild('n22'):addChild(graph)
    end)
end

function FBasicsView:playDragDrop()
    print('playDragDrop')
    local obj = self._demoObjects['Drag&Drop']
    obj:getChild('a'):setDraggable(true)

    local b = obj:getChild('b');
    b:setDraggable(true)
    b:addEventListener(fgui.UIEventType.DragStart, function (ctx)
        print('DragStart')
        ctx:preventDefault()
        fgui.DragDropManager:getInstance():startDrag(b:getIcon(), b:getIcon(), ctx:getInput():getTouchId())
    end)

    local c = obj:getChild('c')
    c:setIcon('')
    c:addEventListener(fgui.UIEventType.Drop, function (ctx)
        c:setIcon(ctx:getDataValue())
    end)

    local bounds = obj:getChild('n7')
    local rect = bounds:transformRect(cc.rect(0,0,bounds:getWidth(),bounds:getHeight()), self.groot)

    -- //---!!Because at this time the container is on the right side of the stage and beginning to move to left(transition), so we need to caculate the final position
    rect.x = rect.x - obj:getParent():getX()
    -- //----

    local d = obj:getChild('d')
    d:setDraggable(true)
    d:setDragBounds(rect)
end

function FBasicsView:playWindow()
    local obj = self._demoObjects['Window']
    if self._winA == nil then
        self._winA = require('test.fgui.FWindow1').new()
        self._winA:retain()

        self._winB = require('test.fgui.FWindow2').new()
        self._winB:retain()

        obj:getChild('n0'):onClick(function (ctx)
            print('click n0')
            self._winA:show()
        end)
        obj:getChild('n1'):onClick(function (ctx)
            print('click n1')
            self._winB:show()
        end)
    end
end

function FBasicsView:playPopup()

    if self._pm == nil then
        self._pm = fairygui.PopupMenu:create()

        self._pm:retain()
        self._pm:addItem("Item 1", handler(self, self.onClickMenu))
        self._pm:addItem("Item 2", handler(self, self.onClickMenu))
        self._pm:addItem("Item 3", handler(self, self.onClickMenu))
        self._pm:addItem("Item 4", handler(self, self.onClickMenu))
    end

    if not self._popupCom then
        self._popupCom = fairygui.UIPackage:createObject('Basics', 'Component12')
        self._popupCom:retain()
        self._popupCom:center()
    end


    local obj = self._demoObjects["Popup"]
    obj:getChild('n0'):onClick(function (ctx)
        self._pm:show(ctx:getSender(), fairygui.PopupDirection.DOWN)
    end)

    obj:getChild('n1'):onClick(function (ctx)
        self.groot:showPopup(self._popupCom)
    end)

    obj:on(fairygui.UIEventType.RightClick, function (ctx)
        self._pm:show()
    end)

end

function FBasicsView:onClickMenu()
    print('click menu')
end

function FBasicsView:playProgress()
    local obj = self._demoObjects["ProgressBar"]
    local scheduler = cc.Director:getInstance():getScheduler()
    local timerId = scheduler:scheduleScriptFunc(handler(self, self.onPlayProgress), 0.02, false)

    obj:on(fairygui.UIEventType.Exit, function (ctx)
        print('obj exit event')
        scheduler:unscheduleScriptEntry(timerId)
    end)
end

function FBasicsView:onPlayProgress(dt)
    local obj = self._demoObjects['ProgressBar']
    local cnt = obj:numChildren()
    for i = 0, cnt-1 do
        local child = obj:getChildAt(i)
        if child then
            child:setValue(child:getValue() + 1)
            if child:getValue() > child:getMax() then
                child:setValue(child:getMin())
            end
        end
    end
end

return FBasicsView
