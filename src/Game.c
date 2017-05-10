#include "./headers/Game.h"

void initGame(game g, int gameMode, int var, int lang)
{
	g.gameMode = gameMode;
	g.var = var;
	g.b = allocateBoard(var);
	g.lang = lang;
}

void update(int currentPlayer, coordinates c1, coordinates c2) {
	updateBoard(currentPlayer, c1, c2);
}
