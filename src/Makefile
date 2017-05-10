CFLAGS = -std=c99 -g -Wall -I $(INCLUDES)
LIB = -lSDL2 -lSDL2_ttf

INCLUDES = headers #ressources objects
src=App.c Game.c IA.c Board.c Rules.c
heads=App.h Game.h IA.h Board.h Rules.h Types.h
objects=$(src:.c=.o)

all : App

App : App.c
	gcc $(CFLAGS) -o $@ $^ $(LIB)

Rules.o : Types.h

%.o : %.c
	gcc $(CFLAGS) -o $^


App-test : App.c
	gcc $(CFLAGS) $^ -o App $(LIB)

App-dev : App.c
	gcc -std=c99 -g App.c -lSDL2 -o App -lSDL2_ttf


.PHONY : clean, mrproper
clean :
	rm -rf *.o
	rm -rf *.h.gch

mrproper : clean
	rm -rf App
