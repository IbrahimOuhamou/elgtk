//بسم الله الرحمن الرحيم

#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <luaconf.h>
#include <lauxlib.h>
#include <gtk-4.0/gtk/gtk.h>
#include "../include/elgtk.h"

static void activate(GtkApplication* app, lua_State* L);

int main(int argc, char** argv)
{
    printf("بسم الله الرحمن الرحيم\n");

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    elg_init(L);
    elgtk_init(L);

    GtkApplication* app = gtk_application_new("bismi_allah.bismi_allah.bismi_allah", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), L);

    g_application_run(G_APPLICATION(app), argc, argv);
}

static void activate(GtkApplication* app, lua_State* L)
{
    GtkWidget* window = gtk_application_window_new(app);
    GtkWidget* button = gtk_button_new_with_label("la ilaha illa Allah");
    gtk_window_set_child(GTK_WINDOW(window), button);

    lua_pushlightuserdata(L, window);
    lua_setglobal(L, "window");
    lua_pushlightuserdata(L, button);
    lua_setglobal(L, "button");
    if(LUA_OK != luaL_dofile(L, "bismi_allah.lua"))
    {
        printf("[C] error at lua: ");
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
    }

    gtk_widget_show(window);
}

