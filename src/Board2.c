#include Board2.h

matrice allocateBoard()
{
	board m;
}


void write(int status, coordonates c)
{
	m.board[c.x][c.y] = status;
}

void movePiece(c1, c2)
{
	write(m.board[c1.x][c1.y],c2);
	write(0,c1);
}

void catchPiece(int currentPlayer, coordonates c2) 
{
	
}

void updateBoard(int currentPlayer, coordonates c1, coordonates c2)
{
	if(checkMovement(c1,c2)){
		movePiece(c1, c2);
		catchPiece(currentPlayer,c2);
	}
	else{printf("Invalid Movement!")}
}

