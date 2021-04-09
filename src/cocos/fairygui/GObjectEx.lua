local GObject = fairygui.GObject
local GTween = fairygui.GTween

-- entend for GObject
function GObject:setEnabled(enable)
    self:setGrayed(not enable)
    self:setTouchable(enable)
    
    -- return self
end

function GObject:addClickListener(cb, tag)
    if tag then
        self:addEventListener(fairygui.UIEventType.Click, cb, tag)
    else
        self:addEventListener(fairygui.UIEventType.Click, cb)
    end

    -- return self
end

function GObject:delayCall(time, cb)
    local tweener = GTween:delayedCall(time):setTarget(self):onComplete(cb)
    -- return tweener
end

-- shortcuts
GObject.onClick = GObject.addClickListener
GObject.on = GObject.addEventListener