local FDemoView = require("test.fgui.fdemoview")

local FChatView = class("FChatView", FDemoView)
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

local function rand_0_1()
    return math.random(1, 100) / 100
end

local Message = class('Message')
function Message:ctor()
    self.sender = nil
    self.senderIcon = nil
    self.msg = nil
    self.fromMe = nil
end

-- FChatView

local function onTag_Emoji(tagName, endLua, attr)
    print('onTag_Emoji', tagName, endLua, attr)
    local str = tagName:sub(2, #tagName)
    str = string.lower(str)
    local replacement = string.format("<img src='ui://Emoji/%s'/>", str)
    return replacement -- MUST return a string
end

function FChatView:ctor()
    print("FChatView create")
    UIRoot = GRoot:getInstance()
    self._messages = {}

    -- ubb parser
    self.ubbparser = fairygui.UBBParserLua:new()
    print('>self.ubbparser', tolua.type(self.ubbparser))
    local tags = {"88","am","bs","bz","ch","cool","dhq","dn","fd","gz","han","hx","hxiao","hxiu"}
    for index, value in ipairs(tags) do
        self.ubbparser:setTagParser(':' .. value, onTag_Emoji)
    end
end

function FChatView:continueInit()
    UIPackage:addPackage("UI/Emoji")
    UIConfig.verticalScrollBar = ""

    self._view = UIPackage:createObject("Emoji", "Main")
    UIRoot:addChild(self._view)

    self._list = self._view:getChild("list")
    self._list:setVirtual()
    self._list.itemProvider = handler(self, self.getListItemResource)
    self._list.itemRenderer = handler(self, self.renderListItem)

    self._input = self._view:getChild("input")
    self._input:addEventListener(UIEventType.Submit, handler(self, self.onSubmit))

    self._view:getChild("btnSend"):addClickListener(handler(self, self.onClickSendBtn))
    self._view:getChild("btnEmoji"):addClickListener(handler(self, self.onClickEmojiBtn))

    self._emojiSelectUI = UIPackage:createObject("Emoji", "EmojiSelectUI")
    self._emojiSelectUI:retain()
    self._emojiSelectUI:getChild("list"):addEventListener(UIEventType.ClickItem, handler(self, self.onClickEmoji))
end

function FChatView:onClickSendBtn(context)
    local msg = self._input:getText()
    if (#msg <= 0) then
        return
    end

    self:addMsg("Unity", "r0", msg, true)
    self._input:setText("")
end

function FChatView:onClickEmojiBtn(context)
    UIRoot:showPopup(self._emojiSelectUI, context:getSender(), PopupDirection.UP)
end

function FChatView:onClickEmoji(context)
    local item = context:getData()
    print('self._input:getText()', self._input:getText())
    print('item', item, tolua.type(item))
    print('item:getText()', item:getText())
    self._input:setText(self._input:getText() .. "[:" .. item:getText() .. "]")
end

function FChatView:onSubmit(context)
    self:onClickSendBtn()
end

function FChatView:renderListItem(index, obj)
    index = index + 1
    print('renderListItem: index', index)
    local item = obj
    local msg = self._messages[index]
    print('msg', msg)
    if (not msg.fromMe) then
        item:getChild("name"):setText(msg.sender)
    end
    item:setIcon("ui://Emoji/" .. msg.senderIcon)

    local tf = item:getChild("msg")
    tf:setText("")
    tf:setWidth(tf.initSize.width)
    -- tf:setText(EmojiParser:getInstance():parse(msg.msg.c_str()))
    tf:setText(self.ubbparser:parse(msg.msg))
    tf:setWidth(tf:getTextSize().width)
end

function FChatView:getListItemResource(index)
    index = index + 1

    local msg = self._messages[index]
    if (msg.fromMe) then
        return "ui://Emoji/chatRight"
    else
        return "ui://Emoji/chatLeft"
    end
end

function FChatView:addMsg(sender, senderIcon, msg, fromMe)
    local isScrollBottom = self._list:getScrollPane():isBottomMost()
    local newMessage = Message:new()
    newMessage.sender = sender
    newMessage.senderIcon = senderIcon
    newMessage.msg = msg
    newMessage.fromMe = fromMe
    table.insert(self._messages, newMessage)

    if (newMessage.fromMe) then
        if (#self._messages == 1 or rand_0_1() < 0.5) then
            local replyMessage = Message:new()
            replyMessage.sender = "FairyGUI"
            replyMessage.senderIcon = "r1"
            replyMessage.msg = "Today is a good day. [:cool]"
            replyMessage.fromMe = false
            table.insert(self._messages, replyMessage)
        end 
    end

    self._list:setNumItems(#self._messages)

    if (isScrollBottom) then
        self._list:getScrollPane():scrollBottom(true)
    end
end

return FChatView
