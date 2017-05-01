all:App
	
Piece.o: Piece.c 
	gcc -c Piece.c 
	
Board.o: Board.c
	gcc -c Board.c
	
App: Board.o Piece.o App.c
	gcc App.c -lSDL2 -o App Board.o -lSDL2_ttf 
	rm *.o


