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

void catchPiece(game *g, coordinates c2)
{
	coordinates *tab;
	tab = checkCatch(g, c2);
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
	free(tab);
}

int updateBoard(game *g, coordinates c1, coordinates c2)
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
		printf("Invalid Movement (Not your token !) %d",g->currentPlayer);
		return 0;
	}
	else if(checkMovement(g,c1,c2)==1){
		movePiece(g,c1, c2);
		catchPiece(g,c2);
		return 1;
	}
	else if(checkMovement(g,c1,c2)==2){
		printf("New move from a friendly token");
		return 2;
	}
	else
	{
		printf("Invalid Movement (Not in the rules !");
		return 0;
	}
}
