#include "Board2.h"

board allocateBoard(int var)
{
	board b;
	b.map = (int **) malloc(sizeof(int*)*9);
	int i;
	for (i=0; i<9; i++) {
		b.map[i] = (int *) malloc(sizeof(int)*9);
		}
	switch (var)
	{
		case 0: //classical ashami shogi
			b.countPlayer1 = 9;
			b.countPlayer2 = 9;
			break;
		case 1: //dai ashami shogi
			b.countPlayer1 = 18;
			b.countPlayer2 = 18;
			break;
		default:
			printf("invalid var");
	}
	return b;
}

void freeBoard(board b)
{
	int i;
	for (i=0; i<9; i++) {
		free(b.map[i]);
		}
	free(b.map);
	b.countPlayer1 = 0;
	b.countPlayer2 = 0;
}

void write(int status, coordinates c)
{
	g.b.map[c.x][c.y] = status;
}

void movePiece(coordinates c1, coordinates c2)
{
	write(g.b.map[c1.x][c1.y],c2);
	write(0,c1);
}

void catchPiece(int currentPlayer, coordinates c2)
{
	coordinates *tab;
	tab = checkCatch(currentPlayer, c2);
	int i;
	for (i = 1; i<tab[0].x; i++) {
		//if ( !((tab[i].x==-1)||(tab[i].y==-1)) ) { TODO Check if necessary or artifact of previous codes
			write(0,tab[i]);
			if (currentPlayer==1) {
				g.b.countPlayer2--; //the opponant lose pieces
				}
			if (currentPlayer==2) {
				g.b.countPlayer1--; //the opponant lose pieces
				}
			//}
		}
	free(tab);
}

int updateBoard(int currentPlayer, coordinates c1, coordinates c2)
{
	if (g.b.map[c1.x][c1.y]!=currentPlayer)
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
