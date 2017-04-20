#include "App.h"

int main(int argc,char* argv[]){
  // Simple Initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
    return -1;
  }

  // Window creation
  SDL_Window* pWindow = NULL;
  int windowRes[2];
  setResolution(windowRes);

  pWindow = SDL_CreateWindow("Hasami Shogi",SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            windowRes[0],
                                            windowRes[1],
                                            SDL_WINDOW_RESIZABLE);

  if(pWindow){
    while(1){eventDetection(pWindow, 0);}
  }


  else{
    fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError() );
  }

  atexit(SDL_Quit);
}



void eventDetection(SDL_Window* pWindow,int fullscreen){
    // Interaction section
    int quit = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) // Getting user's inputs
    {
      switch(event.type)
      {
          case SDL_QUIT: // Clic on the cross
              quit=1;
              break;
          case SDL_KEYUP: // Relâchement d'une touche
              if ( event.key.keysym.sym == SDLK_f ) // Touche f
              {
                  // Alterne du mode plein écran au mode fenêtré
                  if ( fullscreen == 0 )
                  {
                      fullscreen = 1;
                      SDL_SetWindowFullscreen(pWindow,SDL_WINDOW_FULLSCREEN);
                  }
                  else if ( fullscreen == 1 )
                  {
                      fullscreen = 0;
                      SDL_SetWindowFullscreen(pWindow,0);
                  }
              }
              break;
      }

      if(quit == 1){
        SDL_DestroyWindow(pWindow);
      }

    }
  }

void setResolution(int *res){
  res[0] = DEFAULT_WIDTH;
  res[1] = DEFAULT_HEIGTH;
}
