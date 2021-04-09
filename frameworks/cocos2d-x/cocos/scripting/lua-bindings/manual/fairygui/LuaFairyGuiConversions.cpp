
#include "LuaFairyGuiConversions.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

void margin_to_luaval(lua_State* L, const fairygui::Margin& _margin)
{
    lua_newtable(L);
    lua_pushstring(L, "left");
    lua_pushnumber(L, (lua_Number)_margin.left);
    lua_rawset(L, -3);
    lua_pushstring(L, "top");
    lua_pushnumber(L, (lua_Number)_margin.top);
    lua_rawset(L, -3);
    lua_pushstring(L, "right");
    lua_pushnumber(L, (lua_Number)_margin.right);
    lua_rawset(L, -3);
    lua_pushstring(L, "bottom");
    lua_pushnumber(L, (lua_Number)_margin.bottom);
    lua_rawset(L, -3);
}

bool luaval_to_margin(lua_State* L, int lo, fairygui::Margin* outValue, const char* funcName)
{
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok) {
        lua_pushstring(L, "left");
        lua_gettable(L, lo);
        outValue->left = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "top");
        lua_gettable(L, lo);
        outValue->top = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "right");
        lua_gettable(L, lo);
        outValue->right = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "bottom");
        lua_gettable(L, lo);
        outValue->bottom = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }

    return ok;
}

void TweenValue_to_luaval(lua_State *L, const fairygui::TweenValue &tweenValue)
{
    lua_newtable(L);
    
    lua_pushstring(L, "x");
    lua_pushnumber(L, (lua_Number)tweenValue.x);
    lua_rawset(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, (lua_Number)tweenValue.y);
    lua_rawset(L, -3);

    lua_pushstring(L, "z");
    lua_pushnumber(L, (lua_Number)tweenValue.z);
    lua_rawset(L, -3);

    lua_pushstring(L, "w");
    lua_pushnumber(L, (lua_Number)tweenValue.w);
    lua_rawset(L, -3);

    lua_pushstring(L, "d");
    lua_pushnumber(L, (lua_Number)tweenValue.d);
    lua_rawset(L, -3);
}

void luaval_to_TweenValue(lua_State *L, int lo, fairygui::TweenValue *outValue, const char *funcName)
{
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "z");
        lua_gettable(L, lo);
        outValue->z = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "w");
        lua_gettable(L, lo);
        outValue->w = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "d");
        lua_gettable(L, lo);
        outValue->d = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
}
