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
	int **map;  //the game board with the pieces
	int countPlayer1; //the number of pieces owned by the first player
	int countPlayer2; //the number of pieces owned by the second player
	int currentPlayer; //the current player
} game;


/*
	handle the different languages for texts
*/
typedef struct{
	char* mainMenu[10];
	char* rules[20];
	char* options[10];
	char* inGame[10];
	} textsStruct;

/*
	a structure used to store parameters for the graphical interface
*/
typedef struct {
  int fullscreen;
  char soundLevel;
  int texturePack;
	int lang; //the language that should be used by the app
	int screenResX;
	int screenResY;
} parameters;

typedef struct{
	int xbegin;
	int ybegin;
	int caseWidth;
	int caseHeigth;
	int hMargin;
	int vMargin;
} BoardData;
