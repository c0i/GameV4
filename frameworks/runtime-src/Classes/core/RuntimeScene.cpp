
#include "RuntimeScene.h"

#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "cocos2d.h"
#include "scripting/lua-bindings/manual/lua_module_register.h"
//#include "scripting/lua-bindings/manual/fairygui/lua_fairygui.hpp"
#include "scripting/lua-bindings/auto/lua_cocos2dx_fairygui_auto.hpp"

// if you want to use the package manager to install more packages, 
// don't modify or remove this function
static int register_all_packages(lua_State* L)
{
#if CC_USE_IMGUI > 0
    sol::state_view lua(L);
    sol_ImGui::Init(lua);

    lua["ImGui"]["draw"] = []() {
        //printf("imgui draw\n");
    };
    ImGuiEXT::getInstance()->addRenderLoop("#im01", [=]() {
        lua["ImGui"]["draw"]();
        }, nullptr);
#endif // CC_USE_IMGUI


    // FairyGui
    //register_fairygui_manual(L);
    // register_all_fairygui(L);

    return 0; //flag for packages manager
}

RuntimeScene::RuntimeScene()
	: GameScene()
{

}
bool RuntimeScene::init()
{
	if (!GameScene::init())
	{
		return false;
	}


    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

    register_all_packages(L);

    LuaStack* stack = engine->getLuaStack();
    stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));

    //register custom function
    //LuaStack* stack = engine->getLuaStack();
    //register_custom_function(stack->getLuaState());


    FileUtils::getInstance()->addSearchPath("src");
    FileUtils::getInstance()->addSearchPath("res");

	return true;
}


RuntimeScene::~RuntimeScene()
{
}

void RuntimeScene::onEnter()
{
    GameScene::onEnter();
    auto engine = LuaEngine::getInstance();
    engine->executeScriptFile("main.lua");
}