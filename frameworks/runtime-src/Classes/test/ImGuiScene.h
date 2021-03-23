#pragma once

#include "cocos2d.h"

#if defined(CC_PLATFORM_PC)

#include "ImGuiEXT/CCImGuiEXT.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ImGuiScene : public Scene {
public:
    CREATE_FUNC(ImGuiScene);

    ImGuiScene();
    void onEnter() override;
    void onExit() override;
    void onImGuiDraw();
};

#endif // CC_PLATFORM_PC