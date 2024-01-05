//بسم الله الرحمن الرحيم

#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <luaconf.h>
#include <lauxlib.h>
#include <gtk-4.0/gtk/gtk.h>
#include "../include/elgtk.h"

int main()
{
    printf("بسم الله الرحمن الرحيم\n");

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    elg_init(L);
    elgtk_init(L);

    if(LUA_OK != luaL_dofile(L, "bismi_allah.lua"))
    {
        printf("[C] error at lua: ");
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
    }
}

