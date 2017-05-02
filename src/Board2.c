#include "Board2.h"

board allocateBoard(int var)
{
	board b;
	b.map = (int **) malloc(sizeof(int*)*9);
	int i;
	for (i=0; i<l; i++) {
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



void write(int status, coordonnees c)

{
	b.map[c.x][c.y] = status;
}

void movePiece(c1, c2)
{
	write(b.map[c1.x][c1.y],c2);
	write(0,c1);
}

void catchPiece(int currentPlayer, coordonates c2) 
{
	coordonates *tab;
	tab = checkCatch(int currentPlayer, coordonates c2);
	int i;
	for (i = 1; i<tab[0]; i++) {
		if !((tab[i].x==-1)||(tab[i].y==-1)) {
			write(0,b.map[tab[i].x][tab[i].y]);
			if (currentPlayer==1) {
				b.countPlayer1--;
				}
			if (currenPlayer==2) {
				b.countPlayer2--;
				}
			}
		}
	free(tab);
	/*checkSuicide(currentPlayer, c2);*/
}

void updateBoard(int currentPlayer, coordonates c1, coordonates c2)
{
	if(checkMovement(c1,c2)){
		movePiece(c1, c2);
		catchPiece(currentPlayer,c2);
	}
	else{printf("Invalid Movement!")}
}

