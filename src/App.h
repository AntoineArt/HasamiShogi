#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGTH = 1080;

int main(int argc, char * argv[]);

/*
  Treats user's inputs
  pressing f sets the screen to fullscreen
*/
void eventDetection(SDL_Window* pWindow);

/*
  Sets the window's resolution depending on the user's will
  (will be updated when the menu will be on, for now just sets the resolution to default)
*/
void selectResolution(int *res);

/*
  Updates the image on the screen to match with memory state
*/
void updateWindow(SDL_Window* pWindow, SDL_Surface* pImage);

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
