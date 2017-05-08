#include "Game.h"

game newGame(int gameMode, int var)
{
	game g;
	g.gameMode = gameMode;
	g.var = var;
	return g;
}

void update(int currentPlayer, coordinates c1, coordinates c2) {
	updateBoard(int currentPlayer, coordinates c1, coordinates c2);
}

coordinates* showPossible(coordinates c1) {

}
