#include "./headers/SaveSystem.h"

/*
	Create a .txt save the name given
	The first line is reserved for the game presets
*/
void createSave(char* name, Game* g);

/*
	It will be used after each valid turn.
	At each line, it will write the following informations in this order :
	- The number of the turn
	- The current player
	- The play (a couple of coordonates)
	- The opponent's token who was catched
	
	The arguments "x" and "y" are respectively the initial and the final location of the moving token
	The argument tab correspond to a "checkCatch" call
*/
void addToSave(char* name, Game* g, Coordinates x, Coordinates y, Coordinates* tab);

/*
	It return an int who store the save
*/
int readSave(char* name);

/*
	Return a Game* ; We will create a new game using it
*/
Game* loadSave(char* name);

