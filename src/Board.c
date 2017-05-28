#include "./headers/Board.h"

void write(Game *g, int status, Coordinates c)
{
	g->map[c.x][c.y] = status;
}

void movePiece(Game *g, Coordinates c1, Coordinates c2)
{
	write(g,g->map[c1.x][c1.y],c2);
	write(g,0,c1);
}

void catchPiece(Game *g, Coordinates *tab)
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

int checkMove(Game *g, Coordinates c1, Coordinates c2)
{
	if (!(c1.x>=0 && c1.x<=8 && c1.y>=0 && c1.y<=8))
	{
		//printf("Invalid Movement (Source not in the board !)");
		return 0;
	} else if (!(c2.x>=0 && c2.x<=8 && c2.y>=0 && c2.y<=8))
	{
		//printf("Invalid Movement (Destination not in the board !)");
		return 0;
	} else if ((g->map[c1.x][c1.y]) != (g->currentPlayer))
	{
		//printf("Invalid Movement (Not your token !");
		return 0;
	}
	//Check if the destination is friendly
	else if((g->map[c2.x][c2.y]) == (g->currentPlayer))
	{
	//printf("Invalid Movement (Destination is a friendly token)");
	return 2;
	}
	else {
	return checkMovement(g,c1,c2);
	}

}

Coordinates* showPossible(Game *g, Coordinates c1)
{
	//We identifie the number of available case in each direction
	int i=0; int up=0; int right=0; int down=0; int left=0;
	Coordinates c2;

	//Up
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.y)-i >= 0 ; i++)
	{
		c2.y = (c1.y)-i;
		if (checkMove(g,c1,c2)==1) {
			up++;
		} else {break;}
	}

	//Right
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.x)+i <= 8 ; i++)
	{
		c2.x = (c1.x)+i;
		if (checkMove(g,c1,c2)==1) {
			right++;
		} else {break;}
	}

	//Down
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.y)+i <= 8 ; i++)
	{
		c2.y = (c1.y)+i;
		if (checkMove(g,c1,c2)==1) {
			down++;
		} else {break;}
	}

	//Left
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.x)-i >= 0 ; i++)
	{
		c2.x = (c1.x)-i;
		if (checkMove(g,c1,c2)==1) {
			left++;
		} else {break;}
	}

	return createTable(g, c1, up, right, down, left, 0);
}

void printBoard(Game *g) 
{
	int i;
	for (i=0; i<9; i++) {
		int j;
		for (j=0; j<9 ; j++) {
			printf("| %d |",g->map[i][j]);
		}
		printf(" \n");
	}
	printf(" \n");
	printf(" \n");
	printf(" \n");
}