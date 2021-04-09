
local FMailItem = class('FMailItem', function ()
    return fairygui.GButton:create()
end)

local UIEventType = fairygui.UIEventType

function FMailItem:ctor()
    print(tolua.type(self))
    self:on(UIEventType.OnConstruct, handler(self, self.onConstruct))
end

function FMailItem:onConstruct()
    print('> onConstruct event')
    self.timeText = self:getChild('timeText')
    self.readController = self:getController('IsRead')
    self.fetchController = self:getController("c1")
    self.trans = self:getTransition('t0')

    print('self.timeText', self.timeText)
    print('self.readController', self.readController)
    print('self.fetchController', self.fetchController)
    print('self.trans', self.trans)
end

function FMailItem:setTime(value)
    self.timeText:setText(value)
end

function FMailItem:setRead(value)
    self.readController:setSelectedIndex(value and 1 or 0)
end

function FMailItem:setFetched(value)
    self.fetchController:setSelectedIndex(value and 1 or 0)
end

function FMailItem:playEffect(delay)
    self:setVisible(false)
    self.trans:play(1, delay)
end


return FMailItem