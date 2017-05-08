all: App

all-deb: App-deb

clean:
	rm -rf *.o
	rm -rf *.h.gch

Rules.o: Rules.c
	gcc -std=c99 -c Rules.c

Board2.o: Rules.o Board2.c
	gcc -std=c99 Board2.c -o Rules.o

IA.o: IA.c
	gcc -std=c99 -c IA.c

Game.o: IA.o Game.c Board2.o IA.o
	gcc -std=c99 Game.c -o Board2.o IA.o

App: Game.o  App.c
	gcc -std=c99 App -lSDL2 -lSDL2_ttf -o App.c  Game.o



App-dev: App.c
	gcc -std=c99 -g App.c -lSDL2 -o App -lSDL2_ttf



App-deb: Game-deb.o App.c
	gcc -std=c99 -Wall -g App.c Game-deb.o -lSDL2 -o App -lSDL2_ttf 

Game-deb.o: IA-deb.o Game.c Board2-deb.o IA.o
	gcc -std=c99 -Wall Game.c -o Board2-deb.o IA-deb.o

IA-deb.o: Board2-deb.o IA.c
	gcc -std=c99 -Wall IA.c -o Board2-deb.o

Board2-deb.o: Rules-deb.o Board2.c
	gcc -std=c99 -Wall Board2.c -o Rules-deb.o

Rules-deb.o: Rules.c
	gcc -std=c99 -Wall -c Rules.c
