#يسم الله الرحمن الرحيم

CLIBS = -l lua5.4 `pkg-config --libs gtk4`
CFLAGS = `pkg-config --cflags gtk4`

all:
	gcc -c src/elgtk.c $(CFLAGS) -o bin/elgtk.o
	gcc src/main.c bin/elgtk.o $(CLIBS) -o bin/main

