//بسم الله الرحمن الرحيم

#include "../include/elgtk.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <string.h>

static int elg_application_run(lua_State* L);
static int elg_signal_connect(lua_State* L);
static int elg_object_unref(lua_State* L);
static int elg_signal_call(gpointer instance, const char *detailed_signal);

static int elgtk_widget_show(lua_State *L);
static int elgtk_application_new(lua_State *L);
static int elgtk_application_window_new(lua_State *L);
static int elgtk_window_set_title(lua_State *L);

int elg_init(lua_State* L)
{
    luaL_dostring(L, "g = require(\"include.elg\")");
    lua_getglobal(L, "g");
    if(lua_istable(L, -1))
    {
        lua_getfield(L, -1, "application");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "run");
            lua_pushcfunction(L, elg_application_run);
            lua_settable(L, -3);
        }lua_pop(L, 1);

        lua_getfield(L, -1, "signal");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "connect");
            lua_pushcfunction(L, elg_signal_connect);
            lua_settable(L, -3);
        }lua_pop(L, 1);

        lua_getfield(L, -1, "object");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "unref");
            lua_pushcfunction(L, elg_object_unref);
            lua_settable(L, -3);
        }lua_pop(L, 1);
    }lua_pop(L, 1);

    return 0;
}

int elgtk_init(lua_State *L)
{
    luaL_dostring(L, "elgtk = require(\"include.elgtk\")");
    lua_getglobal(L, "elgtk");
    if(lua_istable(L, -1))
    {
        //****************************************************
        //widget
        lua_getfield(L, -1, "widget");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "show");
            lua_pushcfunction(L, elgtk_widget_show);
            lua_settable(L, -3);
        }lua_pop(L, 1);
        //****************************************************

        //****************************************************
        //applcation
        lua_getfield(L, -1, "application");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "new");
            lua_pushcfunction(L, elgtk_application_new);
            lua_settable(L, -3);
        }lua_pop(L, 1);
        //****************************************************


        //****************************************************
        //applcation_window
        lua_getfield(L, -1, "application_window");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "new");
            lua_pushcfunction(L, elgtk_application_window_new);
            lua_settable(L, -3);
        }lua_pop(L, 1);
        //****************************************************

        //****************************************************
        //applcation_window
        lua_getfield(L, -1, "window");
        if(lua_istable(L, -1))
        {
            lua_pushliteral(L, "set_title");
            lua_pushcfunction(L, elgtk_window_set_title);
            lua_settable(L, -3);
        }lua_pop(L, 1);
        //****************************************************

    }lua_pop(L, 1);

    return 0;
}

static int elgtk_widget_show(lua_State *L)
{
    GtkWidget* widget = (GtkWidget*)(lua_topointer(L, 1));
    gtk_widget_show(GTK_WIDGET(widget));
    return 0;
}

static int elgtk_application_new(lua_State *L)
{
    const char* application_id = lua_tostring(L, 1);
    int flags = (int)lua_tonumber(L, 2);
    
    GtkApplication* app = gtk_application_new(application_id, flags);
    lua_pushlightuserdata(L, app);
    return 1;
}

static int elgtk_application_window_new(lua_State *L)
{
    GtkApplication* app = (GtkApplication*)lua_topointer(L, 1);
    GtkWidget*  window = gtk_application_window_new(app);
    lua_pushlightuserdata(L, window);
    return 1;
}

static int elgtk_window_set_title(lua_State *L)
{
    GtkWidget* window = (GtkWidget*)lua_topointer(L, 1);
    const char* title = lua_tostring(L, 2);
    gtk_window_set_title(GTK_WINDOW(window), title);
    return 0;
}

static int elg_application_run(lua_State* L)
{
    GtkApplication* app = (GtkApplication*)lua_topointer(L, 1);
    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    lua_pushnumber(L, status);
    return 1;
}

static int elg_object_unref(lua_State* L)
{
    gpointer object = (gpointer)lua_topointer(L, 1);
    g_object_unref(object);
    return 0;
}

static int elg_signal_connect(lua_State* L)
{
    void* instance = (void *)lua_topointer(L, 1);
    const char* detailed_signal = lua_tostring(L, 2);
    
    {//setting up the lua state 
        g_object_set_data(G_OBJECT(instance), "lua_State", L);
    }

    {//setting up the function
        lua_pushvalue(L, 3);
        int function_index = luaL_ref(L, LUA_REGISTRYINDEX);
        const char* appendix_str = "_function";
        char data_name[strlen(detailed_signal) + strlen(appendix_str) + 1];
        data_name[0]='\0';
        strcat(data_name, detailed_signal);
        strcat(data_name, appendix_str);
        g_object_set_data(G_OBJECT(instance), data_name, (void*)(function_index));
    }

    g_signal_connect(G_OBJECT(instance), G_CALLBACK(detailed_signal), elg_signal_call, detailed_signal);
    return 0;
}

static int elg_signal_call(gpointer instance, const char* detailed_signal)
{
    lua_State* L = (lua_State*)g_object_get_data(instance, "lua_State");

    char function_name[strlen(detailed_signal) + strlen("_function") + 1];
    function_name[0] = '\0';
    strcat(function_name, detailed_signal);
    strcat(function_name, "_function");
    int function_index = (int)g_object_get_data(instance, function_name);

    gpointer data = g_object_get_data(instance, detailed_signal);

    lua_rawgeti(L, LUA_REGISTRYINDEX, function_index);
    lua_pushlightuserdata(L, instance);
    lua_pushlightuserdata(L, data);
    
    lua_call(L, 2, 0);
}

