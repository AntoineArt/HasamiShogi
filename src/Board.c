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

void releasePiece(Game *g, Coordinates *tab, int player)
{
	int i;
	for (i = 1; i<tab[0].x; i++) {
		write(g,player,tab[i]);
	}
}

int checkMove(Game *g, Coordinates c1, Coordinates c2, int player)
{
	if (!(c1.x>=0 && c1.x<=8 && c1.y>=0 && c1.y<=8))
	{
		//printf("Invalid Movement (Source not in the board !)");
		return 0;
	} else if (!(c2.x>=0 && c2.x<=8 && c2.y>=0 && c2.y<=8))
	{
		//printf("Invalid Movement (Destination not in the board !)");
		return 0;
	} else if ((g->map[c1.x][c1.y]) != (player))
	{
		//printf("Invalid Movement (Not your token !");
		return 0;
	}
	//Check if the destination is friendly
	else if((g->map[c2.x][c2.y]) == (player))
	{
	//printf("Invalid Movement (Destination is a friendly token)");
	return 2;
	}
	else {
	return checkMovement(g,c1,c2);
	}

}

Coordinates* showPossible(Game *g, Coordinates c1, int player)
{
	//We identifie the number of available case in each direction
	int i; 
	Coordinates c2;
	
	//Up
	int up = 0;   
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.y)-i >= 0 ; i++)
	{
		c2.y = (c1.y)-i;
		if (checkMove(g,c1,c2,player)==1) {
			up++;
		}
	}
	//Right
	int right = 0;
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.x)+i <= 8 ; i++)
	{
		c2.x = (c1.x)+i;
		if (checkMove(g,c1,c2,player)==1) {
			right++;
		}
	}
	//Down
	int down=0;
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.y)+i <= 8 ; i++)
	{
		c2.y = (c1.y)+i;
		if (checkMove(g,c1,c2,player)==1) {
			down++;
		}
	}
	//Left
	int left = 0;
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; (c1.x)-i >= 0 ; i++)
	{
		c2.x = (c1.x)-i;
		if (checkMove(g,c1,c2,player)==1) {
			left++;
		}
	}
	printf(" %d : %d | %d ; %d ; %d ; %d \n",c1.x, c1.y, up, right, down, left);
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