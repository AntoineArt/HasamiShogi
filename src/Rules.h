#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Reset the board to it's basic state
*/
void resetBoard();

/*
	Return the player who won this turn (0 if none of them)
*/
int checkVictory(int currentPlayer, coordonates c2)

/*
	Return a table of the coordonates with the size of the table in first position
	There isn't any interaction with the piece's previous position
	WARNING : Allocate memory
*/
void checkCatch(int currentPlayer, coordonates c2);

/*
	Check if a move is valid
*/
bool checkMovement(coordonates c1, coordonates c2);

/*
	Check if a piece die at the end of a turn
*/
//bool checkSuicide(currentPlayer, coordonates c2);