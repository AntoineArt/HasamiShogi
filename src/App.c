#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include <SDL2.2.0.5/include/SDL.h>


int main(int argc,char* argv[]){
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); //Démarage SDL 
  SDL_SetVideoMode(640,480,8,SDL_DOUBLEBUF);
  
  
  SDL_Quit(); //Arrêt Propre de l'affichage
  return 0;
}