
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

local function testImGui(  )

    if ImGui then
        dump(ImGui)

        local color = {100,200,255}
        dump(color)
        ImGui.draw = function ()
            ImGui.Begin('[Lua window]')
            ImGui.Text('[Lua Test]')
            if ImGui.Button('Lua Button') then
                print('Lua Button clicked')
            end
            color = ImGui.ColorEdit3('color', color)
            ImGui.End()
        end
    end
end

function MainScene:onCreate()
    -- add background image
    display.newSprite("HelloWorld.png")
        :move(display.center)
        :addTo(self)

    -- add HelloWorld label
    cc.Label:createWithSystemFont("Hello World", "Arial", 40)
        :move(display.cx, display.cy + 200)
        :addTo(self)

    testImGui()
end

return MainScene
