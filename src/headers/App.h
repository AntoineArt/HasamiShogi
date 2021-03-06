#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Game.c"
#include "../resources/lang.c"

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGHT = 1080;
const int BOARD_WIDTH = 1200;
const int BOARD_HEIGHT = 1353;

const int VICTORY_WIDTH = 600;
const int VICTORY_HEIGHT = 600;
const int DEFEAT_WIDTH = 894;
const int DEFEAT_HEIGHT = 762;
const int RULES_WIDTH = 600;
const int RULES_HEIGHT = 800;

const int ORANGE_BUTTON_WIDTH = 2400/8;
const int ORANGE_BUTTON_HEIGHT = 821/8;

const int DECAY_PIECES = 68;
const int OUTBORDER = 8;
const int INBORDER = 4;

const int CASE_WIDTH=115;
const int CASE_HEIGHT=131;

const int PIECE_WIDTH = 98;
const int PIECE_HEIGHT = 120;

const double SCALE_FACTOR = 1;

const int GAME_MODE_DEFAULT = 1; // 0 : JcJ, 1: JvC, 2 : CvJ, 3 : CvC (watch mode)
const int VARIANT_DEFAULT = 1; // 0 : 9 pieces, 1 : 18 pieces
const int LANG_DEFAULT = 0; // 0 means english , 1 means french

Parameters initParameters(int lang, int resX, int resY);

/*
  Initializes SDL2
  has yet no need of int argc, char * argv[]
*/
int main(void);

/*
  Displays the BackgroundMenu and calls menu(...) for user's input
*/
int menu(SDL_Window* pWindow, TTF_Font* police, Texts* texts, SDL_Color textColor);

/*
  Waits for user's input
  Return : int
*/
int eventDetectionMenu(SDL_Window* pWindow, SDL_Surface **textsMenu);

/*
  Sets the window's resolution depending on the user's will
  (will be updated when the menu will be on, for now just sets the resolution to default)
*/
void selectResolution(int *res);

/*
  Displays the surface on the screen according to position x and y
*/
void updateWindow(int x, int y, SDL_Window* pWindow, SDL_Surface* pImage);

/*
  Launches a new game
*/
void launchGame(Game *g, Parameters param, TTF_Font* police, Texts* texts, SDL_Color textColor, int newOrSave);

/*
  Loads an ancient game and launches it
*/
void setupSavedBoard(Game* g, SDL_Window* pWindow);

/*
  Displays the parameters menu
*/
void parametersMenu(SDL_Window* pWindow, TTF_Font* police, Texts* texts, Parameters p);

/*
	Wait for user's input
	return : int
*/
int eventDetectionParameters(SDL_Window* pWindow, SDL_Surface** texts);

/*
  Sets up the display for a new game
*/
void setupNewBoard(Game *g, SDL_Window *pWindow);

/*
  Displays the defeat screen
*/
void defeatDisplay();

/*
  Displays the victory screen for the winner (player)
  might be adapted for computer ^^
*/
void victoryDisplay(int winner);

/*
  Fonction that handle the turn of currentPlayer from the beggining thil the end returning a tab who contains the move c1->c2 and the eventualy caught token. length of the tab in first coordinate x.
*/
Coordinates* inGameEvents(Game *g, SDL_Window* pWindow, int buttonX, int buttonY, int buttonW, int buttonH);
/*
	Displays green cases on cases in coord when a piece is selected
*/
void displayPossibilities(Game* g, SDL_Window* pWindow, Coordinates* coord);

/*
	Hides the green cases (set yellow cases on cases in coord)
*/
void hidePossibilities(Game* g, SDL_Window* pWindow, Coordinates* coord);


/*
  Fonction who display the rules in a separate window
*/
void rules(Game* g, char* name, Texts* texts, SDL_Color textColor, Parameters param);

/*
  Checks if (xM, yM) is in the box defined by x, y, w and h
  returns 1 if true, 0 if false
*/
char isIn(int xM, int yM, int x, int y, int w, int h);
