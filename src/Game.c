#include "./headers/Game.h"

void initGame(game g, int gameMode, int var)
{
	g.gameMode = gameMode;
	g.var = var;
	g.b = allocateBoard(var);
}

void update(int currentPlayer, coordinates c1, coordinates c2) {
	updateBoard(currentPlayer, c1, c2);
}
