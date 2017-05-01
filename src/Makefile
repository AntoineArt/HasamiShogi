all:App

Rules.o: Rules.c
	gcc -c Rules.c

Board2.o: Rules.o Board2.c
	gcc Board2.c -o Rules.o

IA.o: IA.c
	gcc -c IA.c

Game.o: IA.o Game.c Board2.o IA.o
	gcc Game.c -o Board2.o IA.o


App: Game.o  App.c
	gcc App.c -lSDL2 -o App  Game.o -lSDL2_ttf

clean:
	rm -rf *.o
