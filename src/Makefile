all:App
	
Piece.o: Piece.c 
	gcc -c Piece.c
	
Board.o: Board.c
	gcc -c Board.c
	
App: Board.o Piece.o App.c
	gcc -o App App.c Piece.o Board.o


clean:
	rm *.o
