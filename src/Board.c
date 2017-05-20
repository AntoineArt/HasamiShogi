#include "./headers/Board.h"

void write(game *g, int status, coordinates c)
{
	g->map[c.x][c.y] = status;
}

void movePiece(game *g, coordinates c1, coordinates c2)
{
	write(g,g->map[c1.x][c1.y],c2);
	write(g,0,c1);
}

void catchPiece(game *g, coordinates *tab)
{
	int i;
	for (i = 1; i<tab[0].x; i++) {
			write(g,0,tab[i]);
			if (g->currentPlayer==1) {
				g->countPlayer2--; //the opponant lose pieces
				}
			if (g->currentPlayer==2) {
				g->countPlayer1--; //the opponant lose pieces
				}
		}
}

int checkMove(game *g, coordinates c1, coordinates c2)
{
	if (!(c1.x>=0 && c1.x<=8 && c1.y>=0 && c1.y<=8))
	{
		printf("Invalid Movement (Source not in the board !)");
		return 0;
	} else if (!(c2.x>=0 && c2.x<=8 && c2.y>=0 && c2.y<=8))
	{
		printf("Invalid Movement (Destination not in the board !)");
		return 0;
	} else if ((g->map[c1.x][c1.y]) != (g->currentPlayer))
	{
		printf("Invalid Movement (Not your token !");
		return 0;
	}
	//Check if the destination is friendly
	else if((g->map[c2.x][c2.y]) == (g->currentPlayer))
	{
	printf("Invalid Movement (Destination is a friendly token)");
	return 2;
	}
	else {
	return checkMovement(g,c1,c2);
	}
	
}
