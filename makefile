#يسم الله الرحمن الرحيم

$CLIBS = `pkg-config --libs gtk4` -l lua5.4
$CFLAGS = `pkg-config --cflags gtk4`

all:
	gcc -c src/elgtk.c -o bin/elgtk.o
	gcc src/main.c bin/elgtk.o $(CLIBS) $(CFLAGS) -o bin/main

