#include "./headers/Board.h"

void write(int status, coordinates c)
{
	g->map[c.x][c.y] = status;
}

void movePiece(coordinates c1, coordinates c2)
{
	write(g->map[c1.x][c1.y],c2);
	write(0,c1);
}

void catchPiece(int currentPlayer, coordinates c2)
{
	coordinates *tab;
	tab = checkCatch(currentPlayer, c2);
	int i;
	for (i = 1; i<tab[0].x; i++) {
			write(0,tab[i]);
			if (currentPlayer==1) {
				g->countPlayer2--; //the opponant lose pieces
				}
			if (currentPlayer==2) {
				g->countPlayer1--; //the opponant lose pieces
				}

		}
	free(tab);
}

int updateBoard(int currentPlayer, coordinates c1, coordinates c2)
{
	if (!(c1.x>=0 && c1.x<=8 && c1.y>=0 && c1.y<=8))
	{
		printf("Invalid Movement (Source not in the board !)");
		return 0;
	} else if (!(c2.x>=0 && c2.x<=8 && c2.y>=0 && c2.y<=8))
	{
		printf("Invalid Movement (Destination not in the board !)");
		return 0;
	} else if ((g->map[c1.x][c1.y]) != currentPlayer)
	{
		printf("Invalid Movement (Not your token !)");
		return 0;
	}
	else if(checkMovement(c1,c2)){
		movePiece(c1, c2);
		catchPiece(currentPlayer,c2);
		return 1;
	}
	else
	{
		printf("Invalid Movement (Not in the rules !");
		return 0;
	}
}
