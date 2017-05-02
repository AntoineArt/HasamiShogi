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
  int mode;
  mode = menu(pWindow, police);

  switch(mode){
    case 0: newGame();break;
    case 1: continueGame();break;
    case 2: parameters(pWindow, police);break;
    case 3: rules();
    case 4: break;
  }

  // Closing everything

  TTF_CloseFont(police);
  TTF_Quit();

  SDL_DestroyWindow(pWindow);
  SDL_Quit();
}

int menu(SDL_Window* pWindow, TTF_Font* police){
  SDL_Surface* pBackgroundMenu = SDL_LoadBMP("BackgroundMenu.bmp");
  pWindow = SDL_CreateWindow("Hasami Shogi",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              DEFAULT_WIDTH,
                                              DEFAULT_HEIGTH,
                                              0.);

  updateWindow(0, 0, pWindow, pBackgroundMenu); // BackgroundMenu display

  // Menu display
    SDL_Surface *textsMenu[5];
    SDL_Color textColor = {255, 255, 255};

    for(int i = 0; i<5; i++){
      textsMenu[i] = TTF_RenderText_Blended(police, texts[i], textColor);
      updateWindow(960 - textsMenu[i]->w/2, 540 - textsMenu[i]->h/2 - (300-100*i), pWindow, textsMenu[i]);
    }

  int mode;
  if (pWindow){
    mode = eventDetectionMenu(pWindow, textsMenu);
    for(int i=0; i<4; i++){
      SDL_FreeSurface(textsMenu[i]);
    }
    return mode;
  }

  else{
    fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
  }
  return 3;
}

int eventDetectionMenu(SDL_Window* pWindow, SDL_Surface** texts){
  char cont = 1; // Determines if yes or no we continue the loop
  int n = 5;
  int x[n], y[n], w[n], h[n];
  for(int i = 0; i<n; i++){
    w[i] = texts[i]->w;
    h[i] = texts[i]->h;
    x[i] = 960 - w[i]/2;
    y[i] = 540 - h[i]/2-(300-100*i);
  }

  while(cont){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      // Event treatment
      switch(event.type){ // Which type of event is it ?
        case SDL_WINDOWEVENT: // Window event
          if (event.window.event == SDL_WINDOWEVENT_CLOSE){ // Red cross pressed
            cont = 0;
          }
          break;

        case SDL_MOUSEBUTTONUP: // Mouse event
          if (event.button.button == SDL_BUTTON_LEFT){
            int xM = event.button.x;
            int yM = event.button.y;
            printf("%d et %d\n", xM, yM);

            if(isIn(xM, yM, x[0], y[0], w[0], h[0])){return 0;}  //Check New game
            if(isIn(xM, yM, x[1], y[1], w[1], h[1])){return 1;}  //Check Continue
            if(isIn(xM, yM, x[2], y[2], w[2], h[2])){return 2;}  //Check Parameters
            if(isIn(xM, yM, x[3], y[3], w[3], h[3])){return 3;}  //Check Rules
            if(isIn(xM, yM, x[3], y[3], w[3], h[3])){return 4;}  //Check Quit
          }
      }
    }
  }
  return 4;
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

void rules(){

}

void parameters(SDL_Window* pWindow, TTF_Font* police){
  SDL_Surface* pBackgroundParameters = SDL_LoadBMP("BackgroundMenu.bmp");
  SDL_Window *pWinParam = SDL_CreateWindow("Parameters",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              DEFAULT_WIDTH,
                                              DEFAULT_HEIGTH,
                                              0.);

  // Menu display
  updateWindow(0, 0, pWinParam, pBackgroundParameters); // BackgroundMenu display
    SDL_Surface *textsParameters[6]; //0=*french, 1=*english, 2=*fullscreen, 3=*sound, 4=*texturePack, 5=previous;
    SDL_Color textColor = {255, 255, 255};

    for(int i = 0; i<6; i++){
      textsParameters[i] = TTF_RenderText_Blended(police, texts[i + 5], textColor);
      updateWindow(960 - textsParameters[i]->w/2, 540 - textsParameters[i]->h/2 - (300-100*i), pWinParam, textsParameters[i]);
    }
    SDL_Delay(2000);

}

char isIn(int xM, int yM, int x, int y, int w, int h){
  return ((xM > x && xM < x+w) && (yM > y && yM < y+h));
}
