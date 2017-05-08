Rules.o: Rules.c
	gcc -c Rules.c -std=c99

Board2.o: Rules.o Board2.c
	gcc Board2.c -o Rules.o -std=c99

IA.o: IA.c
	gcc -c IA.c -std=c99

Game.o: IA.o Game.c Board2.o IA.o
	gcc Game.c -o Board2.o IA.o -std=c99


App: Game.o  App.c
	gcc App.c -lSDL2 -o App  Game.o -lSDL2_ttf -std=c99

App-dev : App.c
	gcc -g App.c -lSDL2 -o App -lSDL2_ttf -std=c99

clean:
	rm -rf *.o
