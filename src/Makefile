CFLAGS = -std=c99 -g -Wall
LIB = -lSDL2 -lSDL2_ttf

#includeDirs = -rsc not used at this time
src=App.c Game.c IA.c Board2.c Rules.c
heads=App.h Game.h IA.h Board2.h Rules.h Types.h
objects=$(src:.c=.o)

all : App

Rules.o : Rules.c Types.h
	gcc $(CFLAGS) -c $< 

Board2.o : Board2.c Rules.o
	gcc $(CFLAGS) -o $^

IA.o : IA.c Board2.o
	gcc $(CFLAGS) -o $^ 

Game.o : Game.c IA.o 
	gcc $(CFLAGS) -o $^

App : App.c Game.o
	gcc $(CFLAGS) -o $@ $^ $(LIB)
	
App-test : App.c
	gcc $(CFLAGS) $^ -o App $(LIB)
	

App-dev : App.c
	gcc -std=c99 -g App.c -lSDL2 -o App -lSDL2_ttf


.PHONY : clean
clean :
	rm -rf *.o
	rm -rf *.h.gch
