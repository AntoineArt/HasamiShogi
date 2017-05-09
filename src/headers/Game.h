#include "../IA.c"

//GLOBAL VAR
extern game g; //global variable (initialized in App.c)

/*
	function used to initialize a new game
	referenced as g by the rest of the program
*/
void initGame(game g, int gameMode, int var);



/*
	function which update the game after a play
	! is lauchned by user input !
*/
void update(int currentPlayer, coordinates c1, coordinates c2);
