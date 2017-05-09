#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Game.c"


//GLOBAL VAR
game g; //global variable (initialized in main)

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGTH = 1080;
const int GAME_MODE_DEFAULT = 0; // 0 : JcJ, 1: JvC, 2 : CvJ, 3 : CvC (watch mode)
const int VARIANT_DEFAULT = 1; // 0 : 9 pieces, 1 : 18 pieces
const int DECAY_PIECES = 150;

const char texts[11][20] = {"Nouvelle partie", "Continuer", "Parametres", "Regles", "Quitter", "Francais", "Anglais", "Plein ecran", "Son", "Pack de textures", "Precedent"};
const char texts2[11][20] = {"New game", "Continue", "Parameters", "Rules", "Quit", "French", "English", "Fullscreen", "Sound", "Texture pack", "Previous"};


parameters initParameters();

//###########################//

/*
  Initializes SDL2
*/
int main(int argc, char * argv[]);

/*
  Displays the BackgroundMenu and calls menu(...) for user's input
*/
int menu(SDL_Window* pWindow, TTF_Font* police);

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
void newGame(game g, parameters param);

/*
  Loads an ancient game and launches it
*/
void continueGame();

/*
  Displays the parameters menu
*/
void parametersMenu(SDL_Window* pWindow, TTF_Font* police, parameters p);

/*
  Sets up the display for a new game
*/
void setupBoard(game g, SDL_Window *pWindow);

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

*/
int inGameEvents(int currentPlayer);

void rules();

/*
  Checks if (xM, yM) is in the box defined by x, y, w and h
  returns 1 if true, 0 if false
*/
char isIn(int xM, int yM, int x, int y, int w, int h);
