#include Board2.h

matrice allocateBoard()
{
	matrice m;
}

void write(int status, coordonnees c)
{
	m.board[c.x][c.y]=status;
}

void movePiece(c1, c2)
{
	write(m.board[c.x][c.y],c2);
	write(0,c1);
}

void updateBoard(int joueur, coordonnees c1, coordonnees c2)
{
	if(mouvementValide(c1,c2)){
		movePiece(c1, c2);
		furtherUpdate(joueur,c2);
	}
	else{printf("Invalid Movement!")}
}

