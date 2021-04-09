local FDemoView = require("test.fgui.fdemoview")

local FTreeViewView = class("FTreeViewView", FDemoView)
local UIPackage = fairygui.UIPackage
local UIConfig = fairygui.UIConfig
local GTween = fairygui.GTween
local UIObjectFactory = fairygui.UIObjectFactory
local UIEventType = fairygui.UIEventType
local GRoot = fairygui.GRoot
local GTreeNode = fairygui.GTreeNode

local tools = require ("tools.tools")

local UIRoot 
function FTreeViewView:ctor()
    print("FTreeViewView create")
    UIRoot = GRoot:getInstance()
end

function FTreeViewView:continueInit()
    UIPackage:addPackage("UI/TreeView")
    UIConfig.horizontalScrollBar = ""
    UIConfig.verticalScrollBar = ""

    self._view = UIPackage:createObject("TreeView", "Main")
    UIRoot:addChild(self._view)

    self._tree1 = self._view:getChild('tree')
    self._tree1:addEventListener(UIEventType.ClickItem, handler(self, self.onClickNode))

    self._tree2 = self._view:getChild('tree2')
    self._tree2:on(UIEventType.ClickItem, handler(self, self.onClickNode))
    self._tree2.treeNodeRender = handler(self, self.renderTreeNode)


    local topNode = GTreeNode:create(true)
    topNode:setData("I'm a top node")
    self._tree2:getRootNode():addChild(topNode)
    for i = 0, 4 do
        local node = GTreeNode:create()
        node:setData("Hello" .. i)
        topNode:addChild(node)
    end

    local aFolderNode = GTreeNode:create(true)
    aFolderNode:setData('A folder node')
    topNode:addChild(aFolderNode)
    for i = 0, 4 do
        local node = GTreeNode:create()
        node:setData("Good " .. i)
        aFolderNode:addChild(node)
    end

    for index = 1, 3 do
        local node = GTreeNode:create()
        node:setData("World " .. index)
        topNode:addChild(node)
    end

    local anotherTopNode = GTreeNode:create()
    anotherTopNode:setData({"ui://TreeView/heart", "I'm a top node too"}) -- c++: ValueVector({Value("I'm a top node too"), Value("ui://TreeView/heart")})
    self._tree2:getRootNode():addChild(anotherTopNode)
end

function FTreeViewView:onClickNode(context)
    local node = context:getData():treeNode()
    print("click node ", node:getText())
end

function FTreeViewView:renderTreeNode(node, obj)
    print('renderTreeNode -> node:getData():getType()', node:getData())

    local btn = node:getCell()
    if (node:isFolder()) then
        btn:setText(node:getData())
    elseif type(node:getData()) == 'table' then
    -- else if (node:getData().getType() == Value::Type::VECTOR)
    -- {
        local data = node:getData() 
        btn:setIcon(data[1])
        btn:setText(data[2])
    -- }
    else
        btn:setIcon("ui://TreeView/file")
        btn:setText(node:getData())
    end
end

return FTreeViewView
