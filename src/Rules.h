#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	RULES :

	VARIANT 0 (Classic)
		- Each player begins with 9 tokens on his first line
		- The tokens can move horizontally and vertically, but can't pass by another token
		- If a player surrounds a group of alligned opponent's tokens with two of his own tokens, his opponent loose the surrounded tokens*
		- A player win the game if and only if his opponent has 1 token left
		* : Moving voluntarry a token between 2 of the opponent's tokens won't cause him to die, neither if the move complete a group of surrounded alligned tokens

	VARIANT 1 (Dai)
		- Each player begins with 18 tokens on his two first lines
		- The tokens can move horizontally and vertically
		- The tokens can "jump" over another token, if they are adjacent and if the following case is empty
		- If a player surrounds a group of alligned opponent's tokens with two of his own tokens, his opponent loose the surrounded tokens*
		- A player win the game by alligning 5 or more of his tokens vertically or diagonally outside of his starting area**
		- A player can also win if his opponent loose all of his tokens
		* : Moving voluntarry a token between 2 of the opponent's tokens won't cause him to die, neither if the move complete a group of surrounded alligned tokens
		**: It means that the tokens located in a player's first two starting lines can't be taken into account for his victory condition
*/

typedef struct{
	int x,y;
} coordinates;

/*
	Reset the board to it's basic state
*/
void resetBoard();

/*
	Return the player who won this turn (0 if none of them, 3 if both loosed)
*/
int checkVictory(int currentPlayer, coordinates c2);

/*
	Return a table of the coordinates with the size of the table in first position
	There isn't any interaction with the piece's previous position
	WARNING : Allocate memory
*/
coordinates* checkCatch(int currentPlayer, coordinates c2);

/*
	Check if a move is valid
*/
int checkMovement(coordinates c1, coordinates c2);

/*
	Check if the piece who has been moved should die at the end of a turn
*/
//bool checkSuicide(currentPlayer, coordinates c2);
