


#include "scripting/lua-bindings/manual/fairygui/lua_cocos2dx_fairygui_manual.hpp"
#include "scripting/lua-bindings/auto/lua_cocos2dx_fairygui_auto.hpp"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"


#include "FairyGUI.h"
#include "scripting/lua-bindings/manual/fairygui/LuaFairyGuiConversions.h"
#include "utils/UBBParser.h"

USING_NS_FGUI;

typedef enum {
    UICONFIG_MUSIC
} UIConfig_HandlerType;

static int lua_fairygui_UIEventDispatcher_addEventListener(lua_State* L)
{
    int argc = 0;
    fairygui::UIEventDispatcher* cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.UIEventDispatcher", 0, &tolua_err)) goto tolua_lerror;
#endif
    cobj = static_cast<fairygui::UIEventDispatcher*>(tolua_tousertype(L, 1, 0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == cobj) {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_UIEventDispatcher_addEventListener'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (2 == argc) {
        int eventType;
        ok &= luaval_to_int32(L, 2, (int*)&eventType, "fairygui.UIEventDispatcher:addEventListener");
        if (!ok) {
            tolua_error(L, "invalid arguments in function 'lua_fairygui_UIEventDispatcher_addEventListener'", nullptr);
            return 0;
        }
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L, 3, "LUA_FUNCTION", 0, &tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (toluafix_ref_function(L, 3, 0));

        cobj->addEventListener(eventType, [=](fairygui::EventContext* context) {
            object_to_luaval<fairygui::EventContext>(L, "fairygui.EventContext", context);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
            });
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)cobj, handler, (ScriptHandlerMgr::HandlerType)eventType);// fake a HandlerType
        return 0;
    }
    if (3 == argc) {
        int eventType;
        int tag;
        ok &= luaval_to_int32(L, 2, (int*)&eventType, "fairygui.UIEventDispatcher:addEventListener");
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L, 3, "LUA_FUNCTION", 0, &tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (toluafix_ref_function(L, 3, 0));
        ok &= luaval_to_int32(L, 4, (int*)&tag, "fairygui.UIEventDispatcher:addEventListener");
        if (!ok) {
            tolua_error(L, "invalid arguments in function 'lua_fairygui_UIEventDispatcher_addEventListener'", nullptr);
            return 0;
        }

        cobj->addEventListener(eventType, [=](fairygui::EventContext* context) {
            object_to_luaval<fairygui::EventContext>(L, "fairygui.EventContext", context);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
            }, fairygui::EventTag(tag));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)cobj, handler, (ScriptHandlerMgr::HandlerType)eventType);// fake a HandlerType
        return 0;
    }

    luaL_error(L, "'addEventListener' function of UIEventDispatcher has wrong number of arguments: %d, was expecting 2~3\n", argc);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(L, "#ferror in function 'addEventListener'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIEventDispatcher_dispatchEvent(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::UIEventDispatcher *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "fairygui.UIEventDispatcher", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::UIEventDispatcher *)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_UIEventDispatcher_dispatchEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "fairygui.UIEventDispatcher:dispatchEvent");
        if (!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_UIEventDispatcher_dispatchEvent'", nullptr);
            return 0;
        }
        bool ret = cobj->dispatchEvent(arg0);
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }
    if (argc == 2)
    {
        int arg0;
        cocos2d::Ref *arg1;
        ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "fairygui.UIEventDispatcher:dispatchEvent");
        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref", &arg1, "fairygui.UIEventDispatcher:dispatchEvent");
        if (!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_UIEventDispatcher_dispatchEvent'", nullptr);
            return 0;
        }
        bool ret = cobj->dispatchEvent(arg0, (void *)arg1);
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }
    if (argc == 3)
    {
        int arg0;
        cocos2d::Ref *arg1;
        cocos2d::Value arg2;
        ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "fairygui.UIEventDispatcher:dispatchEvent");
        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref", &arg1, "fairygui.UIEventDispatcher:dispatchEvent");
        ok &= luaval_to_ccvalue(tolua_S, 4, &arg2, "fairygui.UIEventDispatcher:dispatchEvent");
        if (!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_UIEventDispatcher_dispatchEvent'", nullptr);
            return 0;
        }
        bool ret = cobj->dispatchEvent(arg0, (void *)arg1, arg2);
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.UIEventDispatcher:dispatchEvent", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_UIEventDispatcher_dispatchEvent'.", &tolua_err);
    return 0;
#endif
}

static void extendUIEventDispatcher(lua_State* L)
{
    lua_pushstring(L, "fairygui.UIEventDispatcher");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "addEventListener", lua_fairygui_UIEventDispatcher_addEventListener);
        tolua_function(L, "dispatchEvent", lua_fairygui_UIEventDispatcher_dispatchEvent);
    }
    lua_pop(L, 1);
}

#pragma region - UIPackage

static int lua_fairygui_UIConfig_set_defaultFont(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::defaultFont = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_defaultFont'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_buttonSound(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::buttonSound = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_buttonSound'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_buttonSoundVolumeScale(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::buttonSoundVolumeScale = lua_tonumber(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_buttonSoundVolumeScale'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_defaultScrollStep(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::defaultScrollStep = lua_tointeger(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_defaultScrollStep'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_defaultScrollDecelerationRate(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::defaultScrollDecelerationRate = lua_tonumber(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_defaultScrollDecelerationRate'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_defaultScrollTouchEffect(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isboolean(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::defaultScrollTouchEffect = lua_toboolean(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_defaultScrollTouchEffect'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_defaultScrollBounceEffect(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isboolean(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::defaultScrollBounceEffect = lua_toboolean(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_defaultScrollBounceEffect'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_defaultScrollBarDisplay(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::defaultScrollBarDisplay = (fairygui::ScrollBarDisplayType)lua_tointeger(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_defaultScrollBarDisplay'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_verticalScrollBar(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::verticalScrollBar = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_verticalScrollBar'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_horizontalScrollBar(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::horizontalScrollBar = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_horizontalScrollBar'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_touchDragSensitivity(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::touchDragSensitivity = lua_tointeger(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_touchDragSensitivity'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_clickDragSensitivity(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::clickDragSensitivity = lua_tointeger(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_clickDragSensitivity'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_touchScrollSensitivity(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::touchScrollSensitivity = lua_tointeger(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_touchScrollSensitivity'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_defaultComboBoxVisibleItemCount(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isnumber(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::defaultComboBoxVisibleItemCount = lua_tointeger(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_defaultComboBoxVisibleItemCount'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_globalModalWaiting(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::globalModalWaiting = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_globalModalWaiting'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_modalLayerColor(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_istable(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    {
        Color4F colorf;
        luaval_to_color4f(L, 2, &colorf);
        fairygui::UIConfig::modalLayerColor = colorf;
    }
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_modalLayerColor'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_tooltipsWin(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::tooltipsWin = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_tooltipsWin'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_bringWindowToFrontOnClick(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isboolean(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::bringWindowToFrontOnClick = lua_toboolean(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_bringWindowToFrontOnClick'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_windowModalWaiting(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::windowModalWaiting = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_windowModalWaiting'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_popupMenu(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::popupMenu = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_popupMenu'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_popupMenu_seperator(lua_State *L)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isstring(L, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif

    fairygui::UIConfig::popupMenu_seperator = lua_tostring(L, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_popupMenu_seperator'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIConfig_set_onMusicCallback(lua_State *L)
{
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "fairygui.UIConfig", 0, &tolua_err))
        goto tolua_lerror;
#endif

    if lua_isnil (L, 2)
    {
        fairygui::UIConfig::onMusicCallback = nullptr;
        // cheat, use fairygui::UIConfig::registerFont address for ref object *_*
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)fairygui::UIConfig::registerFont, (ScriptHandlerMgr::HandlerType)UICONFIG_MUSIC);
        return 0;
    }
#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif

    refid = (toluafix_ref_function(L, 2, 0));
    fairygui::UIConfig::onMusicCallback = [=](const std::string &path) {
        LuaEngine::getInstance()->getLuaStack()->pushFunctionByHandler(refid);
        lua_pushlstring(L, path.c_str(), path.length());
        int error = lua_pcall(L, 1, 0, 0); // 1 pararm, 0 return
        if (error)
        {
            CCLOG("[LUA ERROR] %s", lua_tostring(L, -1));
            lua_pop(L, 1); // remove error message from stack
        }
    };
    ScriptHandlerMgr::getInstance()->addObjectHandler((void *)fairygui::UIConfig::registerFont, refid, (ScriptHandlerMgr::HandlerType)UICONFIG_MUSIC);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_UIConfig_set_onMusicCallback'.", &tolua_err);
    return 0;
#endif
}

static void extendUIConfig(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.UIConfig");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        // variable
        tolua_variable(tolua_S, "defaultFont", nullptr, lua_fairygui_UIConfig_set_defaultFont);
        tolua_variable(tolua_S, "buttonSound", nullptr, lua_fairygui_UIConfig_set_buttonSound);
        tolua_variable(tolua_S, "buttonSoundVolumeScale", nullptr, lua_fairygui_UIConfig_set_buttonSoundVolumeScale);
        tolua_variable(tolua_S, "defaultScrollStep", nullptr, lua_fairygui_UIConfig_set_defaultScrollStep);
        tolua_variable(tolua_S, "defaultScrollDecelerationRate", nullptr, lua_fairygui_UIConfig_set_defaultScrollDecelerationRate);
        tolua_variable(tolua_S, "defaultScrollTouchEffect", nullptr, lua_fairygui_UIConfig_set_defaultScrollTouchEffect);
        tolua_variable(tolua_S, "defaultScrollBounceEffect", nullptr, lua_fairygui_UIConfig_set_defaultScrollBounceEffect);
        tolua_variable(tolua_S, "defaultScrollBarDisplay", nullptr, lua_fairygui_UIConfig_set_defaultScrollBarDisplay);
        tolua_variable(tolua_S, "verticalScrollBar", nullptr, lua_fairygui_UIConfig_set_verticalScrollBar);
        tolua_variable(tolua_S, "horizontalScrollBar", nullptr, lua_fairygui_UIConfig_set_horizontalScrollBar);
        tolua_variable(tolua_S, "touchDragSensitivity", nullptr, lua_fairygui_UIConfig_set_touchDragSensitivity);
        tolua_variable(tolua_S, "clickDragSensitivity", nullptr, lua_fairygui_UIConfig_set_clickDragSensitivity);
        tolua_variable(tolua_S, "touchScrollSensitivity", nullptr, lua_fairygui_UIConfig_set_touchScrollSensitivity);
        tolua_variable(tolua_S, "defaultComboBoxVisibleItemCount", nullptr, lua_fairygui_UIConfig_set_defaultComboBoxVisibleItemCount);
        tolua_variable(tolua_S, "globalModalWaiting", nullptr, lua_fairygui_UIConfig_set_globalModalWaiting);
        tolua_variable(tolua_S, "modalLayerColor", nullptr, lua_fairygui_UIConfig_set_modalLayerColor);
        tolua_variable(tolua_S, "tooltipsWin", nullptr, lua_fairygui_UIConfig_set_tooltipsWin);
        tolua_variable(tolua_S, "bringWindowToFrontOnClick", nullptr, lua_fairygui_UIConfig_set_bringWindowToFrontOnClick);
        tolua_variable(tolua_S, "windowModalWaiting", nullptr, lua_fairygui_UIConfig_set_windowModalWaiting);
        tolua_variable(tolua_S, "popupMenu", nullptr, lua_fairygui_UIConfig_set_popupMenu);
        tolua_variable(tolua_S, "popupMenu_seperator", nullptr, lua_fairygui_UIConfig_set_popupMenu_seperator);
        tolua_variable(tolua_S, "onMusicCallback", nullptr, lua_fairygui_UIConfig_set_onMusicCallback);
    }
    lua_pop(tolua_S, 1);
}

#pragma region GObject

static int lua_fairygui_GObject_get_id(lua_State *L)
{
    fairygui::GObject *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GObject", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GObject *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_get_id'", nullptr);
        return 0;
    }
#endif

    tolua_pushstring(L, cobj->id.c_str());
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_get_id'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GObject_get_name(lua_State *L)
{
    fairygui::GObject *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GObject", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GObject *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_get_name'", nullptr);
        return 0;
    }
#endif

    tolua_pushstring(L, cobj->name.c_str());
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_get_name'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GObject_set_name(lua_State *L)
{
    fairygui::GObject *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GObject", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GObject *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_set_name'", nullptr);
        return 0;
    }
#endif

    cobj->name = tolua_tostring(L, 2, "");
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_set_name'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GObject_get_sourceSize(lua_State *L)
{
    fairygui::GObject *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GObject", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GObject *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_get_sourceSize'", nullptr);
        return 0;
    }
#endif

    size_to_luaval(L, cobj->sourceSize);
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_get_sourceSize'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GObject_get_initSize(lua_State *L)
{
    fairygui::GObject *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GObject", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GObject *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_get_initSize'", nullptr);
        return 0;
    }
#endif

    size_to_luaval(L, cobj->initSize);
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_get_initSize'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GObject_get_minSize(lua_State *L)
{
    fairygui::GObject *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GObject", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GObject *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_get_minSize'", nullptr);
        return 0;
    }
#endif

    size_to_luaval(L, cobj->minSize);
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_get_minSize'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GObject_get_maxSize(lua_State *L)
{
    fairygui::GObject *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GObject", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GObject *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_get_maxSize'", nullptr);
        return 0;
    }
#endif

    size_to_luaval(L, cobj->maxSize);
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_get_maxSize'.", &tolua_err);
    return 0;
#endif
}

static void extendGObject(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.GObject");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        // variable
        tolua_variable(tolua_S, "id", lua_fairygui_GObject_get_id, nullptr);
        tolua_variable(tolua_S, "name", lua_fairygui_GObject_get_name, lua_fairygui_GObject_set_name);
        tolua_variable(tolua_S, "sourceSize", lua_fairygui_GObject_get_sourceSize, nullptr);
        tolua_variable(tolua_S, "initSize", lua_fairygui_GObject_get_initSize, nullptr);
        tolua_variable(tolua_S, "minSize", lua_fairygui_GObject_get_minSize, nullptr);
        tolua_variable(tolua_S, "maxSize", lua_fairygui_GObject_get_maxSize, nullptr);
    }
    lua_pop(tolua_S, 1);
}

#pragma region PopupMenu
static int _lua_fairygui_PopupMenu_addItem(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::PopupMenu *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "fairygui.PopupMenu", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::PopupMenu *)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_PopupMenu_addItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 2)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0, "fairygui.PopupMenu:addItem");
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 3, 0));
        if (!ok || 0 == handler)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_PopupMenu_addItem'", nullptr);
            return 0;
        }
        // CCLOG("%s:%s", __FUNCTION__, arg0.c_str());
        fairygui::GButton *ret = cobj->addItem(arg0, [=](fairygui::EventContext *context) {
            object_to_luaval<fairygui::EventContext>(tolua_S, "fairygui.EventContext", context);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
        });
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)cobj, handler);
        object_to_luaval<fairygui::GButton>(tolua_S, "fairygui.GButton", (fairygui::GButton *)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.PopupMenu:addItem", argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_PopupMenu_addItem'.", &tolua_err);
    return 0;
#endif
}

static void extendPopupMenu(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.PopupMenu");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "addItem", _lua_fairygui_PopupMenu_addItem);
    }
    lua_pop(tolua_S, 1);
}

#pragma region Transition

static int lua_fairygui_Transition_play(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::Transition *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "fairygui.Transition", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::Transition *)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_Transition_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        cobj->play();
        return 0;
    }
    if (argc == 1)
    {
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 2, 0));
        if (0 == handler)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_Transition_play'", nullptr);
            return 0;
        }
        cobj->play([=]() {
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 0);
        });
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)cobj, handler);
        return 0;
    }
    if (argc == 2)
    {
        int arg0;
        double arg1;
        ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 3, &arg1, "fairygui.Transition:play");
        cobj->play(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        int arg0;
        double arg1;
        ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 3, &arg1, "fairygui.Transition:play");
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 4, 0));
        if (!ok || 0 == handler)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_Transition_play'", nullptr);
            return 0;
        }
        cobj->play(arg0, arg1, [=]() {
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 0);
        });
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)cobj, handler);
        return 0;
    }
    if (argc == 4)
    {
        int arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_int32(tolua_S, 2, &arg0, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 3, &arg1, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 4, &arg2, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 5, &arg3, "fairygui.Transition:play");
        cobj->play(arg0, arg1, arg2, arg3);
        return 0;
    }
    if (argc == 5)
    {
        int arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_int32(tolua_S, 2, &arg0, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 3, &arg1, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 4, &arg2, "fairygui.Transition:play");
        ok &= luaval_to_number(tolua_S, 5, &arg3, "fairygui.Transition:play");
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 6, 0));
        if (!ok || 0 == handler)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_Transition_play'", nullptr);
            return 0;
        }
        cobj->play(arg0, arg1, arg2, arg3, [=]() {
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 0);
        });
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)cobj, handler);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.Transition:play", argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_Transition_play'.", &tolua_err);
    return 0;
#endif
}
static int lua_fairygui_Transition_setHook(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::Transition *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "fairygui.Transition", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::Transition *)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_Transition_setHook'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 2)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0, "fairygui.Transition:setHook");
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 3, 0));
        if (!ok || 0 == handler)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_Transition_setHook'", nullptr);
            return 0;
        }
        cobj->setHook(arg0, [=]() {
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 0);
        });
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)cobj, handler);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.Transition:setHook", argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_Transition_setHook'.", &tolua_err);
    return 0;
#endif
}

static void extendTransition(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.Transition");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "play", lua_fairygui_Transition_play);
        tolua_function(tolua_S, "setHook", lua_fairygui_Transition_setHook);
    }
    lua_pop(tolua_S, 1);
}

#pragma region

static int lua_fairygui_GTweener_onUpdate(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::GTweener *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "fairygui.GTweener", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (fairygui::GTweener *)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_GTweener_onUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 2, 0));
        if (0 == handler)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_Transition_play'", nullptr);
            return 0;
        }
        auto arg0 = [=](fairygui::GTweener* tweener) {
            object_to_luaval<fairygui::GTweener>(tolua_S, "fairygui.GTweener", tweener);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
        };
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)cobj, handler);


        fairygui::GTweener *ret = cobj->onUpdate(arg0);
        object_to_luaval<fairygui::GTweener>(tolua_S, "fairygui.GTweener", (fairygui::GTweener *)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.GTweener:onUpdate", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_GTweener_onUpdate'.", &tolua_err);
#endif

    return 0;
}

static int lua_fairygui_GTweener_onStart(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::GTweener *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "fairygui.GTweener", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (fairygui::GTweener *)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_GTweener_onStart'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        std::function<void(fairygui::GTweener *)> arg0;

        do
        {
            // Lambda binding for lua is not supported.
            assert(false);
        } while (0);
        if (!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_GTweener_onStart'", nullptr);
            return 0;
        }
        fairygui::GTweener *ret = cobj->onStart(arg0);
        object_to_luaval<fairygui::GTweener>(tolua_S, "fairygui.GTweener", (fairygui::GTweener *)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.GTweener:onStart", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_GTweener_onStart'.", &tolua_err);
#endif

    return 0;
}

static int lua_fairygui_GTweener_onComplete(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::GTweener *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "fairygui.GTweener", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (fairygui::GTweener *)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_GTweener_onComplete'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 2, 0));
        if (0 == handler)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_GTweener_onComplete'", nullptr);
            return 0;
        }
        auto arg0 = [=]() {
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 0);
        };
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)cobj, handler);


        if (!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_GTweener_onComplete'", nullptr);
            return 0;
        }
        fairygui::GTweener *ret = cobj->onComplete(arg0);
        object_to_luaval<fairygui::GTweener>(tolua_S, "fairygui.GTweener", (fairygui::GTweener *)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.GTweener:onComplete", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_GTweener_onComplete'.", &tolua_err);
#endif

    return 0;
}
static int lua_fairygui_GTweener_onComplete1(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::GTweener *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "fairygui.GTweener", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (fairygui::GTweener *)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_GTweener_onComplete1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        std::function<void(fairygui::GTweener *)> arg0;

        do
        {
            // Lambda binding for lua is not supported.
            assert(false);
        } while (0);
        if (!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_GTweener_onComplete1'", nullptr);
            return 0;
        }
        fairygui::GTweener *ret = cobj->onComplete1(arg0);
        object_to_luaval<fairygui::GTweener>(tolua_S, "fairygui.GTweener", (fairygui::GTweener *)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.GTweener:onComplete1", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_GTweener_onComplete1'.", &tolua_err);
#endif

    return 0;
}

static int lua_fairygui_GTweener_get_value(lua_State *L)
{
    fairygui::GTweener *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GTweener", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GTweener *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GObject_get_name'", nullptr);
        return 0;
    }
#endif

    TweenValue_to_luaval(L, cobj->value);
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GObject_get_name'.", &tolua_err);
    return 0;
#endif
}


static void extendGTweener(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.GTweener");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        // tolua_variable(tolua_S, "startValue", lua_fairygui_GTweener_get_startValue, 0);
        // tolua_variable(tolua_S, "endValue", lua_fairygui_GTweener_get_endValue, 0);
        tolua_variable(tolua_S, "value", lua_fairygui_GTweener_get_value, 0);
        // tolua_variable(tolua_S, "deltaValue", lua_fairygui_GTweener_get_deltaValuer, 0);

        tolua_function(tolua_S, "onUpdate", lua_fairygui_GTweener_onUpdate);
        tolua_function(tolua_S, "onStart", lua_fairygui_GTweener_onStart);
        tolua_function(tolua_S, "onComplete", lua_fairygui_GTweener_onComplete);
        tolua_function(tolua_S, "onComplete1", lua_fairygui_GTweener_onComplete1);
    }
    lua_pop(tolua_S, 1);
}

#pragma region
static int lua_fairygui_UIObjectFactory_setPackageItemExtension(lua_State *tolua_S)
{
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "fairygui.UIObjectFactory", 0, &tolua_err) ||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err))
    {
        goto tolua_lerror;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 2)
    {
        std::string url;
        int handler;
        luaval_to_std_string(tolua_S, 2, &url, "fairygui.UIObjectFactory:setPackageItemExtension");
        handler = toluafix_ref_function(tolua_S, 3, 0);
        // typeid is a ref of static object
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)&typeid(fairygui::UIObjectFactory), handler);
        fairygui::UIObjectFactory::setPackageItemExtension(url, [=]() -> fairygui::GComponent * {
            LuaEngine::getInstance()->getLuaStack()->pushFunctionByHandler(handler);
            int error = lua_pcall(tolua_S, 0, 1, 0); // 1 pararm, 1 return
            if (error)
            {
                CCLOG("[LUA ERROR] %s", lua_tostring(tolua_S, -1));
                lua_pop(tolua_S, 1); // remove error message from stack
                return nullptr;
            }
            fairygui::GComponent *com = static_cast<fairygui::GComponent *>(tolua_tousertype(tolua_S, -1, 0));
            lua_pop(tolua_S, 1);
            return com;
        });
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "fairygui.UIObjectFactory:setPackageItemExtension", argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_UIObjectFactory_setPackageItemExtension'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_UIObjectFactory_setLoaderExtension(lua_State *tolua_S)
{
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "fairygui.UIObjectFactory", 0, &tolua_err) ||
        !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
    {
        goto tolua_lerror;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        int handler = toluafix_ref_function(tolua_S, 2, 0);
        // typeid is a ref of static object
        ScriptHandlerMgr::getInstance()->addCustomHandler((void *)&typeid(fairygui::UIObjectFactory), handler);
        fairygui::UIObjectFactory::setLoaderExtension([=]() -> fairygui::GLoader * {
            LuaEngine::getInstance()->getLuaStack()->pushFunctionByHandler(handler);
            int error = lua_pcall(tolua_S, 0, 1, 0); // 1 pararm, 1 return
            if (error)
            {
                CCLOG("[LUA ERROR] %s", lua_tostring(tolua_S, -1));
                lua_pop(tolua_S, 1); // remove error message from stack
                return nullptr;
            }
            fairygui::GLoader *loader = static_cast<fairygui::GLoader *>(tolua_tousertype(tolua_S, -1, 0));
            lua_pop(tolua_S, 1);
            return loader;
        });
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "fairygui.UIObjectFactory:setLoaderExtension", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_UIObjectFactory_setLoaderExtension'.", &tolua_err);
    return 0;
#endif
}
static void extendUIObjectFactory(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.UIObjectFactory");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "setPackageItemExtension", lua_fairygui_UIObjectFactory_setPackageItemExtension);
        tolua_function(tolua_S, "setLoaderExtension", lua_fairygui_UIObjectFactory_setLoaderExtension);
    }
    lua_pop(tolua_S, 1);
}

#pragma region
typedef enum
{
    GLIST_ITEM_RENDERER,
    GLIST_ITEM_PROVIDER,
    GTREE_NODE_RENDERER, // GTree is expend from list
    GTREE_NODE_WILLEXPAND
} GList_HandlerType;

static int lua_fairygui_GList_get_itemRenderer(lua_State *L)
{
    fairygui::GList *cobj = nullptr;
    int refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_get_itemRenderer'", nullptr);
        return 0;
    }
#endif

    // GLIST_ITEM_RENDERER is a HandlerType
    refid = ScriptHandlerMgr::getInstance()->getObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)GLIST_ITEM_RENDERER);
    if (refid >= 0)
    {
        toluafix_get_function_by_refid(L, refid);
    }
    else
    {
        lua_pushnil(L);
    }
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_get_itemRenderer'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GList_set_itemRenderer(lua_State *L)
{
    fairygui::GList *cobj = nullptr;
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_set_itemRenderer'", nullptr);
        return 0;
    }
#endif

    if lua_isnil (L, 2)
    {
        cobj->itemRenderer = nullptr;
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)GLIST_ITEM_RENDERER);
        return 0;
    }
#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif

    refid = (toluafix_ref_function(L, 2, 0));
    cobj->itemRenderer = [=](int index, fairygui::GObject *gobject) {
        lua_pushinteger(L, index);
        object_to_luaval<fairygui::GObject>(L, "fairygui.GObject", gobject);
        LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(refid, 2);
    };
    // GLIST_ITEM_RENDERER is a HandlerType
    ScriptHandlerMgr::getInstance()->addObjectHandler((void *)cobj, refid, (ScriptHandlerMgr::HandlerType)GLIST_ITEM_RENDERER);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_set_itemRenderer'.", &tolua_err);
    return 0;
#endif
}
static int lua_fairygui_GList_get_itemProvider(lua_State *L)
{
    fairygui::GList *cobj = nullptr;
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_get_itemProvider'", nullptr);
        return 0;
    }
#endif

    // GLIST_ITEM_PROVIDER is a HandlerType
    refid = ScriptHandlerMgr::getInstance()->getObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)GLIST_ITEM_PROVIDER);
    if (refid >= 0)
    {
        toluafix_get_function_by_refid(L, refid);
    }
    else
    {
        lua_pushnil(L);
    }
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_get_itemProvider'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GList_set_itemProvider(lua_State *L)
{
    fairygui::GList *cobj = nullptr;
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_set_itemProvider'", nullptr);
        return 0;
    }
#endif

    if lua_isnil (L, 2)
    {
        cobj->itemProvider = nullptr;
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)GLIST_ITEM_PROVIDER);
        return 0;
    }
#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif

    refid = (toluafix_ref_function(L, 2, 0));
    cobj->itemProvider = [=](int index) -> std::string {
        LuaEngine::getInstance()->getLuaStack()->pushFunctionByHandler(refid);
        lua_pushinteger(L, index);
        int error = lua_pcall(L, 1, 1, 0); // 1 pararm, 1 return
        if (error)
        {
            CCLOG("[LUA ERROR] %s", lua_tostring(L, -1));
            lua_pop(L, 1); // remove error message from stack
            return "";
        }
        std::string rtn = lua_tostring(L, -1);
        lua_pop(L, 1);
        return rtn;
    };
    // GLIST_ITEM_PROVIDER is a HandlerType
    ScriptHandlerMgr::getInstance()->addObjectHandler((void *)cobj, refid, (ScriptHandlerMgr::HandlerType)GLIST_ITEM_PROVIDER);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_set_itemProvider'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GList_get_scrollItemToViewOnClick(lua_State *L)
{
    fairygui::GList *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_get_scrollItemToViewOnClick'", nullptr);
        return 0;
    }
#endif

    lua_pushboolean(L, cobj->scrollItemToViewOnClick);
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_get_scrollItemToViewOnClick'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GList_set_scrollItemToViewOnClick(lua_State *L)
{
    fairygui::GList *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_set_scrollItemToViewOnClick'", nullptr);
        return 0;
    }
#endif

    if lua_isboolean (L, 2)
    {
        cobj->scrollItemToViewOnClick = lua_toboolean(L, 2);
        return 0;
    }
    luaL_error(L, "fairygui.GList:scrollItemToViewOnClick value type MUST be Boolean!");

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_set_scrollItemToViewOnClick'.", &tolua_err);
#endif
    return 0;
}
static int lua_fairygui_GList_get_foldInvisibleItems(lua_State *L)
{
    fairygui::GList *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_get_foldInvisibleItems'", nullptr);
        return 0;
    }
#endif

    lua_pushboolean(L, cobj->foldInvisibleItems);
    return 1;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_get_foldInvisibleItems'.", &tolua_err);
    return 0;
#endif
}

static int lua_fairygui_GList_set_foldInvisibleItems(lua_State *L)
{
    fairygui::GList *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GList", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GList *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_set_foldInvisibleItems'", nullptr);
        return 0;
    }
#endif

    if lua_isboolean (L, 2)
    {
        cobj->foldInvisibleItems = lua_toboolean(L, 2);
        return 0;
    }
    luaL_error(L, "fairygui.GList:foldInvisibleItems value type MUST be Boolean!");

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GList_set_foldInvisibleItems'.", &tolua_err);
#endif
    return 0;
}
static void extendGList(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.GList");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_variable(tolua_S, "itemRenderer", lua_fairygui_GList_get_itemRenderer, lua_fairygui_GList_set_itemRenderer);
        tolua_variable(tolua_S, "itemProvider", lua_fairygui_GList_get_itemProvider, lua_fairygui_GList_set_itemProvider);
        tolua_variable(tolua_S, "scrollItemToViewOnClick", lua_fairygui_GList_get_scrollItemToViewOnClick, lua_fairygui_GList_set_scrollItemToViewOnClick);
        tolua_variable(tolua_S, "foldInvisibleItems", lua_fairygui_GList_get_foldInvisibleItems, lua_fairygui_GList_set_foldInvisibleItems);
    }
    lua_pop(tolua_S, 1);
}

#pragma region

typedef enum
{
    Window_doHideAnimation,
    Window_doShowAnimation
} Window_HandlerType;
static int lua_fairygui_Window_set_doHideAnimationDelegate(lua_State *L)
{
    fairygui::Window *cobj = nullptr;
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.Window", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::Window *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_set_itemRenderer'", nullptr);
        return 0;
    }
#endif

    if lua_isnil (L, 2)
    {
        cobj->doHideAnimationDelegate = nullptr;
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)Window_doHideAnimation);
        return 0;
    }
#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif

    refid = (toluafix_ref_function(L, 2, 0));
    cobj->doHideAnimationDelegate = [=]() {
        LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(refid, 0);
    };
    // Window_doHideAnimation is a HandlerType
    ScriptHandlerMgr::getInstance()->addObjectHandler((void *)cobj, refid, (ScriptHandlerMgr::HandlerType)Window_doHideAnimation);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_Window_set_doHideAnimationDelegate'.", &tolua_err);
    return 0;
#endif
}
static int lua_fairygui_Window_set_doShowAnimationDelegate(lua_State *L)
{
    fairygui::Window *cobj = nullptr;
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.Window", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::Window *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GList_set_itemRenderer'", nullptr);
        return 0;
    }
#endif

    if lua_isnil (L, 2)
    {
        cobj->doShowAnimationDelegate = nullptr;
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)Window_doShowAnimation);
        return 0;
    }
#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif

    refid = (toluafix_ref_function(L, 2, 0));
    cobj->doShowAnimationDelegate = [=]() {
        LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(refid, 0);
    };
    // Window_doShowAnimation is a HandlerType
    ScriptHandlerMgr::getInstance()->addObjectHandler((void *)cobj, refid, (ScriptHandlerMgr::HandlerType)Window_doShowAnimation);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_Window_set_doShowAnimationDelegate'.", &tolua_err);
    return 0;
#endif
}
static void extendWindow(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.Window");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_variable(tolua_S, "doHideAnimationDelegate", NULL, lua_fairygui_Window_set_doHideAnimationDelegate);
        tolua_variable(tolua_S, "doShowAnimationDelegate", NULL, lua_fairygui_Window_set_doShowAnimationDelegate);
    }
    lua_pop(tolua_S, 1);
}



#pragma region
static int lua_fairygui_EventContext_getData(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::EventContext *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "fairygui.EventContext", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::EventContext *)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_EventContext_getData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        cocos2d::Ref *ret = (cocos2d::Ref *)cobj->getData();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref", ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.EventContext:getData", argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_EventContext_getData'.", &tolua_err);
    return 0;
#endif
}
static void extendEventContext(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.EventContext");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "getData", lua_fairygui_EventContext_getData);
    }
    lua_pop(tolua_S, 1);
}

#pragma region - UBBParserLua

NS_FGUI_BEGIN
class UBBParserLua : public UBBParser
{
public:
    typedef std::function<void(const std::string &tagName, bool end, const std::string &attr, std::string &replacement)> TagHandler;

    UBBParserLua()
    {

    }
    ~UBBParserLua()
    {
        ScriptHandlerMgr::getInstance()->removeObjectAllHandlers(this);
    }

    void setTagParser(const std::string &tagName, TagHandler tagHandler)
    {
        // CCLOG("%s:%s", __FUNCTION__, tagName.c_str());
        _handlers[tagName] = tagHandler;
    }
};
NS_FGUI_END

int lua_fairygui_UBBParserLua_setTagParser(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::UBBParserLua *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "fairygui.UBBParserLua", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (fairygui::UBBParserLua *)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_fairygui_UBBParserLua_setTagParser'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 2)
    {
        std::string arg0;
        //std::function<void(const std::string &, bool, const std::string &, std::string &)> arg1;

        ok &= luaval_to_std_string(tolua_S, 2, &arg0, "fairygui.UBBParserLua:setTagParser");

        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 3, 0));
        auto arg1 = [=](const std::string & tagName, bool end, const std::string & attr, std::string& replacement) {
            // CCLOG("tagName=%s", tagName.c_str());
            // CCLOG("end=%s", end ? "true" : "false");
            // CCLOG("atr=%s", attr.c_str());

            auto stack = LuaEngine::getInstance()->getLuaStack();
            int numResults = 1;
            tolua_pushstring(tolua_S, tagName.c_str());
            tolua_pushboolean(tolua_S, end);
            tolua_pushstring(tolua_S, attr.c_str());
            __Array *resultArray = __Array::createWithCapacity(numResults);
            stack->executeFunctionReturnArray(handler, 3, numResults, *resultArray);

            // set value
            __String *a0 = dynamic_cast<__String *>(resultArray->getObjectAtIndex(0));
            replacement = a0->getCString();
            // CCLOG("replacement=%s", replacement.c_str());
        };
        ScriptHandlerMgr::getInstance()->addCustomHandler(cobj, handler);

        cobj->setTagParser(arg0, arg1);

        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.UBBParserLua:setTagParser", argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_UBBParserLua_setTagParser'.", &tolua_err);
#endif

    return 0;
}
int lua_fairygui_UBBParserLua_constructor(lua_State *tolua_S)
{
    int argc = 0;
    fairygui::UBBParserLua *cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        if (!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'lua_fairygui_UBBParserLua_constructor'", nullptr);
            return 0;
        }
        cobj = new fairygui::UBBParserLua();
        tolua_pushusertype(tolua_S, (void *)cobj, "fairygui.UBBParserLua");
        tolua_register_gc(tolua_S, lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "fairygui.UBBParserLua:UBBParserLua", argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S, "#ferror in function 'lua_fairygui_UBBParserLua_constructor'.", &tolua_err);
#endif

    return 0;
}

static int lua_fairygui_UBBParserLua_finalize(lua_State *tolua_S)
{
    printf("luabindings: finalizing LUA object (UBBParserLua)");
    return 0;
}

int lua_register_fairygui_UBBParserLua(lua_State *tolua_S)
{
    tolua_usertype(tolua_S, "fairygui.UBBParserLua");
    tolua_cclass(tolua_S, "UBBParserLua", "fairygui.UBBParserLua", "fairygui.UBBParser", nullptr);

    tolua_beginmodule(tolua_S, "UBBParserLua");
    tolua_function(tolua_S, "new", lua_fairygui_UBBParserLua_constructor);
    tolua_function(tolua_S, "setTagParser", lua_fairygui_UBBParserLua_setTagParser);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(fairygui::UBBParserLua).name();
    g_luaType[typeName] = "fairygui.UBBParserLua";
    g_typeCast["UBBParserLua"] = "fairygui.UBBParserLua";
    return 1;
}

#pragma region Tree
static int lua_fairygui_GTree_set_treeNodeRender(lua_State *L)
{
    fairygui::GTree *cobj = nullptr;
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GTree", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GTree *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GTree_set_treeNodeRender'", nullptr);
        return 0;
    }
#endif

    if lua_isnil (L, 2)
    {
        cobj->treeNodeRender = nullptr;
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)GTREE_NODE_RENDERER);
        return 0;
    }
#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif

    refid = (toluafix_ref_function(L, 2, 0));
    cobj->treeNodeRender = [=](fairygui::GTreeNode *node, fairygui::GComponent *obj) {
        object_to_luaval<fairygui::GTreeNode>(L, "fairygui.GTreeNode", node);
        object_to_luaval<fairygui::GComponent>(L, "fairygui.GComponent", obj);
        LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(refid, 2);
    };
    ScriptHandlerMgr::getInstance()->addObjectHandler((void *)cobj, refid, (ScriptHandlerMgr::HandlerType)GTREE_NODE_RENDERER);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GTree_set_treeNodeRender'.", &tolua_err);
    return 0;
#endif
}
static int lua_fairygui_GTree_set_treeNodeWillExpand(lua_State *L)
{
    fairygui::GTree *cobj = nullptr;
    LUA_FUNCTION refid = -1;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "fairygui.GTree", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (fairygui::GTree *)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'lua_fairygui_GTree_set_treeNodeWillExpand'", nullptr);
        return 0;
    }
#endif

    if lua_isnil (L, 2)
    {
        cobj->treeNodeWillExpand = nullptr;
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)cobj, (ScriptHandlerMgr::HandlerType)GTREE_NODE_WILLEXPAND);
        return 0;
    }
#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif

    refid = (toluafix_ref_function(L, 2, 0));
    cobj->treeNodeWillExpand = [=](fairygui::GTreeNode *node, bool expand) {
        object_to_luaval<fairygui::GTreeNode>(L, "fairygui.GTreeNode", node);
        lua_pushboolean(L, (int)expand);
        LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(refid, 2);
    };
    ScriptHandlerMgr::getInstance()->addObjectHandler((void *)cobj, refid, (ScriptHandlerMgr::HandlerType)GTREE_NODE_WILLEXPAND);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_fairygui_GTree_set_treeNodeWillExpand'.", &tolua_err);
    return 0;
#endif
}
static void extendGTree(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "fairygui.GTree");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        // variable
        tolua_variable(tolua_S, "treeNodeRender", nullptr, lua_fairygui_GTree_set_treeNodeRender);
        tolua_variable(tolua_S, "treeNodeWillExpand", nullptr, lua_fairygui_GTree_set_treeNodeWillExpand);
    }
    lua_pop(tolua_S, 1);
}

int register_all_fairygui_manual(lua_State *L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
        tolua_module(L, "fairygui", 0);
        tolua_beginmodule(L, "fairygui");
        {
            lua_register_fairygui_UBBParserLua(L);
        }
        tolua_endmodule(L);
        


        // extend
        extendUIEventDispatcher(L);
        extendUIConfig(L);
        extendGObject(L);
        extendPopupMenu(L);
        extendTransition(L);
        extendGTweener(L);
        extendUIObjectFactory(L);
        extendGList(L);
        extendWindow(L);
        extendEventContext(L);
        extendGTree(L);
    }
    lua_pop(L, 1);
    
    return 1;
}
