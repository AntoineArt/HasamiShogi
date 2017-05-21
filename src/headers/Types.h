/*
	a simple type to describes coordinates
*/
typedef struct COORDINATES {
	int x,y;
} Coordinates;

/*
	a structure that contains the whole game
*/
typedef struct GAME {
	int gameMode; //the gameMode ie player vs player 1, player vs computer 2, computer vs player 3,  computer vs computer (watch mode) 4
	int var; // variante of Hasami shogi beeing played
	int **map;  //the game board with the pieces
	int countPlayer1; //the number of pieces owned by the first player
	int countPlayer2; //the number of pieces owned by the second player
	int currentPlayer; //the current player
} Game;


/*
	handle the different languages for texts
*/
typedef struct TEXTS {
	char* mainMenu[10];
	char* rules[20];
	char* options[10];
	char* inGame[10];
} Texts;

/*
	a structure used to store parameters for the graphical interface
*/
typedef struct PARAMETERS {
  int fullscreen;
  char soundLevel;
  int texturePack;
	int lang; //the language that should be used by the app
	int screenResX;
	int screenResY;
} Parameters;

typedef struct BOARDDATA {
	int xbegin;
	int ybegin;
	int caseWidth;
	int caseHeigth;
	int hMargin;
	int vMargin;
} BoardData;


/*
	used to implement ab algorythm by IA
	each nodes remembers the c1->c2 play that it represents
*/
typedef struct TREE {
	double value;
	Coordinates c1;
	Coordinates c2;
	int nbofSons;
	struct TREE** sons; //a tab of pointers
} Tree;
