#include "../Board.c"
#include <string.h>

/*
	Create a .txt save the name given
	The first line is reserved for the game presets gameMode and var (variant of the game)
*/
void createSave(char* name, Game* g);

/*
	It will be used after each valid turn.
	At each line, it will write the following informations in this order :
	- The number of the turn
	- The play piece c1 goes to c2
	- An array with coordinates of caught token during the turn
*/
void addToSave(char* name, Coordinates c1, Coordinates c2, Coordinates* takenPiecesTab, int turn);

/*
	It return an char* who store the line number n of the file
*/
int loadSafe(Game* g, char* name);

/*
	return the play number n
	WARNING : allocate memory
*/
//int playPlayed(char* name, int n);

/*
	Return the play of the input (only works if the string is a play)
*/
//Coordinates* analysePlay(char* input);

/*
	Return a Game* ; We will create a new game using it
*/
//Game* loadSave(char* name);

/*
	return int corresponding to a[] value
	copied from http://www.programmingsimplified.com/c/source-code/c-program-convert-string-to-integer-without-using-atoi-function
*/
int strToInt(char a[]);
