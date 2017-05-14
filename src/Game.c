#include "./headers/Game.h"

void initGame(game *g, int gameMode, int var, int lang)
{
	g->lang = lang;
	g->gameMode = gameMode;
	g->var = var;
	g->map = (int **) malloc(sizeof(int*)*9);
	int i;
	for (i=0; i<9; i++) {
		g->map[i] = (int *) malloc(sizeof(int)*9);
		}
	
	int j;
	for (i=0; i<9; i++) { //init of the standart board
		for (j=0; j<9; j++) {
			if (i==0 || i==var) { //I think it does what we expect
				g->map[i][j]=2;
			} else if (i==8 || i==(8-var)) {
				g->map[i][j]=1;
			} else {
				g->map[i][j]=0;
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
	printf("%d",g->lang);
}

void freeGame(game *g)
{
	int i;
	for (i=0; i<9; i++) {
		free(g->map[i]);
		}
	free(g->map);
}
