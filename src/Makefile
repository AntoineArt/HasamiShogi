CFLAGS = -std=c99
CFLAGSDEB = $(CFLAGS) -Wall

LIB = -lSDL2 -lSDL2-ttf

#includeDirs = -rsc not used at this time
src=App.c Game.c IA.c Board2.c Rules.c
heads=App.h Game.h IA.h Board2.h Rules.h Types.h

all : App

all-deb : App-deb

Rules.o : Rules.c Types.h
	gcc -c $< $(CFLAGS)

Board2.o : Rules.o Board2.c
	gcc -o $^ $(CFLAGS)

IA.o : IA.c
	gcc -c $^ $(CFLAGS)

Game.o : IA.o Game.c Board2.o IA.o
	gcc -o $^ $(CFLAGS)

App : Game.o  App.c
	gcc  App -o $@ $^  $(LIB) $(CFLAGS)


App-deb : Game-deb.o App.c
	gcc -g -o $@ $^ $(LIB) $(CFLAGSDEB) 

Game-deb.o : IA-deb.o Game.c Board2-deb.o IA-deb.o
	gcc -o $^ $(CFLAGSDEB)

IA-deb.o : Board2-deb.o IA.c
	gcc -o $^ $(CFLAGSDEB)

Board2-deb.o : Rules-deb.o Board2.c
	gcc -o $^ $(CFLAGSDEB)

Rules-deb.o : Rules.c Types.h
	gcc  -c $< $(CFLAGSDEB)
	

App-dev : App.c
	gcc -std=c99 -g App.c -lSDL2 -o App -lSDL2_ttf


.PHONY : clean
clean :
	rm -rf *.o
	rm -rf *.h.gch
