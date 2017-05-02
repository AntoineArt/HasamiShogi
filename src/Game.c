#include "Game.h"

game newGame(int gameMode, int var) 
{
	game g;
	g.gameMode = gameMode;
	g.var = var;
	return g;
}

void update(int currentPlayer, coordonates c1, coordonates c2) {
	updateBoard(int currentPlayer, coordonates c1, coordonates c2);
	
	
}

coordonates* showPossible(coordonates c1) {
	
}