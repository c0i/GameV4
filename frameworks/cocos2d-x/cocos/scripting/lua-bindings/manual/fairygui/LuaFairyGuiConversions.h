
#pragma once

#include <unordered_map>
#include <string>

extern "C" {
#include "lua.h"
#include "tolua++.h"
}
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "FairyGUI.h"

#include "scripting/lua-bindings/manual/Lua-BindingsExport.h"

CC_LUA_DLL void margin_to_luaval(lua_State* L, const fairygui::Margin& _margin);
CC_LUA_DLL bool luaval_to_margin(lua_State* L, int lo, fairygui::Margin* outValue, const char* funcName);

CC_LUA_DLL void TweenValue_to_luaval(lua_State *L, const fairygui::TweenValue &tweenValue);
CC_LUA_DLL void luaval_to_TweenValue(lua_State *L, int lo, fairygui::TweenValue *outValue, const char *funcName);