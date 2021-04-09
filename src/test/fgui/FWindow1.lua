
local FWindow1 = class('FWindow1', function ()
    return fairygui.Window:create()
end)

function FWindow1:ctor()
    print(tolua.type(self))
    self:addEventListener(fairygui.UIEventType.OnInit, function (ctx)
        print('OnInit')
        self:setContentPane(fairygui.UIPackage:createObject('Basics', 'WindowA'))
        self:center()
    end)

    self:addEventListener(fairygui.UIEventType.OnShown, function (ctx)
        local list = self:getContentPane():getChild('n6');
        print(tolua.type(list))
        list:removeChildrenToPool()

        for index = 0, 5 do
            local item = list:addItemFromPool();
            item:setTitle(tostring(index))
            item:setIcon('ui://Basics/r4')
        end
    end)
end

return FWindow1
