#include "./headers/Game.h"

void initGame(Game *g, int gameMode, int var)
{
	g->gameMode = gameMode;
	g->var = var;
	g->currentPlayer=1; //means black first
	g->map = (int **) malloc(sizeof(int*)*9);
	if (g->map == NULL) {exit(0);} // if alloc failed, immediatly quit
	int i;
	for (i=0; i<9; i++) {
		g->map[i] = (int *) malloc(sizeof(int)*9);
		if (g->map[i] == NULL) {exit(0);} // if alloc failed, immediatly quit
		}

	int j;
	for (i=0; i<9; i++) { //init of the standart board
		for (j=0; j<9; j++) {
			if (j==0 || j==var) { //I think it does what we expect 1 row in var 0 and 2 in var 1
				g->map[i][j]=2; //player two ie red token
			} else if (j==8 || j==(8-var)) {
				g->map[i][j]=1; //players one ie black token
			} else {
				g->map[i][j]=0; //empty cases
			}
		}
	}

	switch (g->var)
	{
		case 0: //classical ashami shogi
			g->countPlayer1 = 9;
			g->countPlayer2 = 9;
			break;
		case 1: //dai ashami shogi
			g->countPlayer1 = 18;
			g->countPlayer2 = 18;
			break;
		default:
			printf("invalid var");
	}
}

void freeGame(Game *g)
{
	int i;
	for (i=0; i<9; i++) {
		free(g->map[i]);
		}
	free(g->map);
}

