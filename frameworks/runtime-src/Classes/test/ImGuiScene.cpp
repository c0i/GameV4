#include "ImGuiScene.h"
#include "ui/CocosGUI.h"

#if defined(CC_PLATFORM_PC)

static bool show_test_window = true;
static bool show_another_window = true;
static ImVec4 clear_color = ImColor(114, 144, 154);

ImGuiScene::ImGuiScene()
{
}

void ImGuiScene::onEnter()
{
    Scene::onEnter();
    
    auto button = cocos2d::ui::Button::create();
    button->setTitleText("CLICK ME");
    button->setTitleFontSize(64);
    button->addClickEventListener([](Ref* o) {
        static int cnt = 0;
        CCLOG("CLICK ME %d", cnt++);
    });
    button->setPosition(getContentSize() / 2);
    addChild(button);
    ImGuiEXT::getInstance()->addRenderLoop("#im01", CC_CALLBACK_0(ImGuiScene::onImGuiDraw, this), this);
}

void ImGuiScene::onExit()
{
    Scene::onExit();
    ImGuiEXT::getInstance()->removeRenderLoop("#im01");
}

void ImGuiScene::onImGuiDraw()
{
    // 1. Show a simple window
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    {
        ImGui::Begin("window");
        static float f = 0.0f;
        ImGui::Text("Hello, world!");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float*)&clear_color);
        if (ImGui::Button("Test Window")) show_test_window ^= 1;
        if (ImGui::Button("Another Window")) show_another_window ^= 1;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 2. Show another simple window, this time using an explicit Begin/End pair
    if (show_another_window)
    {
        ImGui::SetNextWindowSize(ImVec2(170, 80), ImGuiCond_FirstUseEver);
        ImGui::Begin("Another Window", &show_another_window);

        ImGui::Text("Hello");
        ImGui::End();
    }

    // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
    if (show_test_window)
    {
        ImGui::ShowDemoWindow();
    }
}

#endif // CC_PLATFORM_PC
