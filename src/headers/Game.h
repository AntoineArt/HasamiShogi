#include "../IA.c"

//GLOBAL VAR
extern game *g; //global variable (initialized in App.c)

/*
	function used to initialize a new game
	referenced as g by the rest of the program
	
	Create a 9x9 matrix and all the related vars from struct game depending on the variante of ashami shogi being played
	
	warning allocate memory !
*/
void initGame(game *g, int gameMode, int var, int lang);

/*
	Free the memory used by the game
*/
void freeGame(game *g);
