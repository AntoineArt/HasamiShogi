#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include "Game.c"

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGTH = 1080;

const char texts[11][20] = {"Nouvelle partie", "Continuer", "Parametres", "Regles", "Quitter", "Francais", "Anglais", "Plein ecran", "Son", "Pack de textures", "Precedent"};
const char texts2[11][20] = {"New game", "Continue", "Parameters", "Rules", "Quit", "French", "English", "Fullscreen", "Sound", "Texture pack", "Previous"};
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

void newGame();

void continueGame();

void parameters(SDL_Window* pWindow, TTF_Font* police);

void rules();

/*
  Checks if (xM, yM) is in the box defined by x, y, w and h
  returns 1 if true, 0 if false
*/
char isIn(int xM, int yM, int x, int y, int w, int h);

/*
  Resizes a SDL_Surface
  Copied from http://www.sdltutorials.com/sdl-scale-surface
*/
SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);

/*
  Reads the pixels from a surface
  Adapted from http://sdl.beuc.net/sdl.wiki/Pixel_Access
*/
Uint32 ReadPixel(SDL_Surface *surface, Sint16 x, Sint16 y);

/*
  Draws the pixels on a surface
  Adapted from http://sdl.beuc.net/sdl.wiki/Pixel_Access
*/
void DrawPixel(SDL_Surface *surface, Sint16 x, Sint16 y, Uint16 pixel);
