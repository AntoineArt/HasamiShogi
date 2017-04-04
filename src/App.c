#include "App.h"

int main(int argc,char* argv[]){
  //Initialisation simple
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
    return -1;
  }

  //Création de la fenêtre
  SDL_Window* pWindow = NULL;
  pWindow = SDL_CreateWindow("Test Fenêtre",SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            640,
                                            480,
                                            SDL_WINDOW_SHOWN);

  //Test d'affichage
  if (pWindow){
    SDL_Delay(3000); //On attend 3s que l'utilisateur voie la fenêtre
    SDL_DestroyWindow(pWindow);
  }
  else{
    fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError() );
  }

  SDL_Quit(); //Arrêt Propre
}
