#include "App.h"

int main(int argc, char* argv[]){
  // Initialization
  if(SDL_Init(SDL_INIT_VIDEO)){
    fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
    return -1;
  }

  TTF_Init(); // Initializes the TTF library
  TTF_Font* police = TTF_OpenFont("asman.ttf", 50);

  // Window creation
  SDL_Window* pWindow = NULL;

  // Launching the menu window
  menu(pWindow, police);

  // Closing everything

  TTF_CloseFont(police);
  TTF_Quit();

  SDL_DestroyWindow(pWindow);
  SDL_Quit();
}

void menu(SDL_Window* pWindow, TTF_Font* police){
  SDL_Surface* pBackgroundMenu = SDL_LoadBMP("BackgroundMenu.bmp");
  pWindow = SDL_CreateWindow("Hasami Shogi",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              DEFAULT_WIDTH,
                                              DEFAULT_HEIGTH,
                                              0.);

  updateWindow(0, 0, pWindow, pBackgroundMenu); // BackgroundMenu display

  // Menu display
    SDL_Surface *textsMenu[4];
    SDL_Color textColor = {255, 255, 255};

    for(int i = 0; i<4; i++){
      textsMenu[i] = TTF_RenderText_Blended(police, texts[i], textColor);
    }

    updateWindow(960 - textsMenu[0]->w/2, 540 - textsMenu[0]->h/2 - 300, pWindow, textsMenu[0]);
    updateWindow(960 - textsMenu[1]->w/2, 540 - textsMenu[1]->h/2 - 200, pWindow, textsMenu[1]);
    updateWindow(960 - textsMenu[2]->w/2, 540 - textsMenu[2]->h/2 - 100, pWindow, textsMenu[2]);
    updateWindow(960 - textsMenu[3]->w/2, 540 - textsMenu[3]->h/2, pWindow, textsMenu[3]);


  int mode;
  if (pWindow){
    mode = eventDetectionMenu(pWindow, textsMenu);
    for(int i=0; i<4; i++){
      SDL_FreeSurface(textsMenu[i]);
    }

    /*switch(mode){
      case 0: newGame(); break;
      case 1: continueGame(); break;
      case 2: parameters(pWindow, police); break;
      case 3: return; break;
    }*/

    if(mode==3){return;}
    else if(mode == 2){parameters(pWindow, police);}
  }

  else{
    fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
  }
}

int eventDetectionMenu(SDL_Window* pWindow, SDL_Surface** texts){
  char cont = 1; // Determines if yes or no we continue the loop
  int n = sizeof(texts)/sizeof(texts[0]);
  int x[n], y[n], w[n], h[n];
  for(int i = 0; i<n; i++){
    w[i] = texts[i]->w;
    h[i] = texts[i]->h;
    x[i] = 960 - w[i]/2;
    y[i] = 540 - h[i]/2;
  }

  while(cont){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      // Event treatment
      switch(event.type){ // Which type of event is it ?
        case SDL_WINDOWEVENT: // Window event
          if (event.window.event == SDL_WINDOWEVENT_CLOSE){ // Red cross pressed
            return 3;
          }
          break;

        case SDL_MOUSEBUTTONUP: // Mouse event
          if (event.button.button == SDL_BUTTON_LEFT){
            int xM = event.button.x;
            int yM = event.button.y;

            if(isIn(xM, yM, x[0], y[0], w[0], h[0]))     {return 0;}       //Check New game
            else if(isIn(xM, yM, x[1], y[1], w[1], h[1])){return 1;}  //Check Continue
            else if(isIn(xM, yM, x[2], y[2], w[2], h[2])){return 2;}  //Check Parameters
            else if(isIn(xM, yM, x[3], y[3], w[3], h[3])){return 3;}  //Check Quit
          }
      }
    }
  }
  return 3;
}

void updateWindow(int x, int y, SDL_Window* pWindow, SDL_Surface* pImage){
  int *w = NULL, *h = NULL;
  SDL_GetWindowSize(pWindow, w, h); // Gets the width and the heigth of the current window

  SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);
  SDL_Rect dest = {x, y, 0, 0};
  SDL_BlitSurface(pImage, NULL, pWinSurf, &dest);
  SDL_UpdateWindowSurface(pWindow);
}

void newGame(){

}

void continueGame(){

}

void parameters(SDL_Window* pWindow, TTF_Font* police){
  SDL_Surface* pBackgroundBoard = SDL_LoadBMP("ShogiBoard.bmp");
  // Menu display
  updateWindow(0, 0, pWindow, pBackgroundBoard); // BackgroundMenu display

    SDL_Surface *textsParameters[6]; //0=*french, 1=*english, 2=*fullscreen, 3=*sound, 4=*texturePack, 5=previous;
    SDL_Color textColor = {255, 255, 255};

    for(int i = 0; i<6; i++){
      textsParameters[i] = TTF_RenderText_Blended(police, texts[i + 4], textColor);
    }

    //updateWindow(960 - textNewGame->w/2, 540 - textNewGame->h/2 - 300, pWindow, textNewGame);
    //updateWindow(960 - textContinue->w/2, 540 - textContinue->h/2 - 200, pWindow, textContinue);
    //updateWindow(960 - textParameters->w/2, 540 - textParameters->h/2 - 100, pWindow, textParameters);
    //updateWindow(960 - textQuitGame->w/2, 540 - textQuitGame->h/2, pWindow, textQuitGame);
}

char isIn(int xM, int yM, int x, int y, int w, int h){
  return ((xM > x && xM < x+w) && (yM > y && yM < y+h));
}
