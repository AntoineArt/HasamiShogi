#include "Board.c"
#include "IA.c"

typedef struct {
	int gameMode; //the gameMode ie player vs player 1, player vs computer 2, computer vs player 3,  computer vs computer (watch mode) 4
  	int var; // variante of ashami shogi beeing played 
  	} game;
  	
  	
/*
	function used to initialize a new game 
	referenced as g by the rest of the program
*/
game newGame(int, gameMode, int var);
  
	
/*
	function which update the game after a play
	! is lauchned by user input !
*/
void update(int currentPlayer, coordonates c1, coordonates c2);

/*
	function that show off the possible play after selection of a token
*/
coordonates* showPossible(coordonates c1);