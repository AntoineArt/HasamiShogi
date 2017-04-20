all:App
	
Piece.o: Piece.c 
	gcc -c Piece.c 
	
Board.o: Board.c
	gcc -c Board.c
	
App: Board.o Piece.o App.c
	gcc App.c -lSDL2 -o App Piece.o Board.o
	rm *.o


