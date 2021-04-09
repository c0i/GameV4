
cc.FileUtils:getInstance():setPopupNotify(false)

require "config"
require "cocos.init"

cc.exports.fgui = fairygui

local function fguimain()
    require('test.fgui.FMenuView').new():run()
end

local function main()
    require("app.MyApp"):create():run()
end

local status, msg = xpcall(fguimain, __G__TRACKBACK__)
if not status then
    print(msg)
end
