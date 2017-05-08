/*
	structure that describe the board status
	contains the map of pieces
	contains the piece counter of both player
	knows the gameMode
	knows the variante that is currently being played
*/
typedef struct {
  int **map;  //the game board with the pieces
  int countPlayer1; //the number of pieces owned by the first player
  int countPlayer2; //the number of pieces owned by the second player
} board;


/*
	a simple type to describes coordinates
*/
typedef struct{
	int x,y;
} coordinates;

/*
	a structure that contains the whole game
*/
typedef struct {
	int gameMode; //the gameMode ie player vs player 1, player vs computer 2, computer vs player 3,  computer vs computer (watch mode) 4
	int var; // variante of ashami shogi beeing played
	board b; // board of the game
} game;

/*
	a structure used to store parameters for the graphical interface
*/
typedef struct {
  int fullscreen;
  char soundLevel;
  int texturePack;
}parameters;
