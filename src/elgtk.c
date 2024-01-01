//بسم الله الرحمن الرحيم

#include "../include/elgtk.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static int elgtk_application_new(lua_State *L);
static int elgtk_application_window_new(lua_State *L);

int elgtk_init(lua_State *L)
{
    luaL_dostring(L, "elgtk = require(\"include.elgtk\")");
    lua_getglobal(L, "egtk");
    if(lua_istable(L, -1))
    {
        lua_getfield(L, -1, "application");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "new");
            lua_pushcfunction(L, elgtk_application_new);
            lua_settable(L, -3);
        }lua_pop(L, 1);

        lua_getfield(L, -1, "application_window");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "new");
            lua_pushcfunction(L, elgtk_application_window_new);
            lua_settable(L, -3);
        }lua_pop(L, 1);
    }lua_pop(L, 1);

    return 0;
}

static int elgtk_application_new(lua_State *L)
{
    const char* application_id = lua_tostring(L, 1);
    int flags = (int)lua_tonumber(L, 2);
    
    GtkApplication* app = gtk_application_new(application_id, flags);
    GtkApplication** app_ptr = (GtkApplication**)lua_newuserdata(L, sizeof(GtkApplication*));
    *app_ptr = app;

    return 1;
}

static int elgtk_application_window_new(lua_State *L)
{

}

