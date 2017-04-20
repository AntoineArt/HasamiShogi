#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGTH = 480;

int main(int argc, char * argv[]);

/*
  Treats user's inputs
  pressing f sets the screen to fullscreen
*/
void eventDetection(SDL_Window* pWindow, int fullscreen);

/*
  sets the window's resolution depending on the user's will
  (will be updated when the menu will be on, for now just sets the resolution to default)
*/
void setResolution(int *res);
