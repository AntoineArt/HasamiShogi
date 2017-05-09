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
  initGame(g, GAME_MODE_DEFAULT, VARIANT_DEFAULT);
  mode = menu(pWindow, police);
  parameters param = initParameters();


  switch(mode){
    case 0: newGame(g, param);break;
    case 1: continueGame();break;
    case 2: parametersMenu(pWindow, police, param);break;
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
  int n = 5;
  int x[n], y[n], w[n], h[n];
  for(int i = 0; i<n; i++){
    w[i] = texts[i]->w;
    h[i] = texts[i]->h;
    x[i] = 960 - w[i]/2;
    y[i] = 540 - h[i]/2-(300-100*i);
  }

  while(1){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      // Event treatment
      switch(event.type){ // Which type of event is it ?
        case SDL_WINDOWEVENT: // Window event
          if (event.window.event == SDL_WINDOWEVENT_CLOSE){ // Red cross pressed
            return 4;
          }
          break;

        case SDL_MOUSEBUTTONUP: // Mouse event
          if (event.button.button == SDL_BUTTON_LEFT){
            int xM = event.button.x;
            int yM = event.button.y;

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

void newGame(game g, parameters param){
  SDL_Surface* pBackgroundGame = SDL_LoadBMP("ShogiBoard.bmp");
  SDL_Window* pWinGame = SDL_CreateWindow("Hasami Shogi",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              1500,
                                              1353,
                                              0.);

  // Menu display
  updateWindow(DECAY_PIECES, 0, pWinGame, pBackgroundGame);
  setupBoard(g, pWinGame);
  //board b = allocateBoard(g.var);
  //resetBoard(b);
  int currentPlayer = 1; //initialize the currentPlayer

  //victory contains the player who won this turn (0 if none of them, 3 if both loosed)
  int victory = 0;
  while (victory==0){
    //ajouter IAplay
    victory = inGameEvents(currentPlayer);
    currentPlayer = 3-currentPlayer; //switch the player
  }

  if(victory == 1){victoryDisplay(1);}
  else if (victory == 2){victoryDisplay(2);}
  else{defeatDisplay();} //both loosed
}

void continueGame(){

}

void rules(){

}

void parametersMenu(SDL_Window* pWindow, TTF_Font* police, parameters p){
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
    SDL_FreeSurface(pBackgroundParameters);
    SDL_DestroyWindow(pWinParam);
}

char isIn(int xM, int yM, int x, int y, int w, int h){
  return ((xM > x && xM < x+w) && (yM > y && yM < y+h));
}

void setupBoard(game g, SDL_Window* pWindow){
  SDL_Surface* pBlackPiece = SDL_LoadBMP("BlackPiece.bmp");
  SDL_Surface* pRedPiece = SDL_LoadBMP("RedPiece.bmp");

  SDL_Surface* p1st = (g.gameMode == 2) ? pBlackPiece : pRedPiece;
  SDL_Surface* p2nd = (g.gameMode == 2) ? pRedPiece : pBlackPiece;

  for(int i = 0; i<9; i++){
    for(int j=0; j<g.var+1; j++){
      updateWindow(DECAY_PIECES + 67 + i*(115+5), 68+8 + j*131, pWindow, p1st);  //Positioning 1st player
      updateWindow(DECAY_PIECES + 67 + i*(115+5), 68+8 + 8 * (131+4) - j*131, pWindow, p2nd);  //Positioning 2nd player
    }
  }
}

void defeatDisplay(){

}
void victoryDisplay(int winner){

}

int inGameEvents(int currentPlayer){
  int depth = 0;
  coordinates c1;
  c1.x=-1; c1.y=-1;
  coordinates c2;
  c2.x=-1; c2.y=-1;

  coordinates c;
  int moveRight = 0;
  while (!moveRight) {

    while(depth<2){ //Clic detection
      SDL_Event event;
      while(SDL_PollEvent(&event)){
        // Event treatment
        switch(event.type){ // Which type of event is it ?
          case SDL_MOUSEBUTTONUP: // Mouse event
            if (event.button.button == SDL_BUTTON_LEFT){
              int xM = event.button.x;
              int yM = event.button.y;
              for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                  if(isIn(xM, yM, DECAY_PIECES + 67 + i*(115+5), 68+8 + j*131, 98, 120)){
                    c.x = i ; c.y = j;
                  }
                }
              }
            }
          }
      }
      if(depth==0){
        c1.x=c.x ; c1.y = c.y; depth++;
      }
      else if(depth==1){
      //display available mouvement and catchs
        if(c.x==c1.x && c.y==c1.y){
          depth--;
        }
        else{
          c2.x = c.x ; c2.y = c.y; depth++;
        }
      }
    }
    moveRight = updateBoard(currentPlayer,c1,c2);
  }
  return checkVictory(1, c2);
}





parameters initParameters(){
  parameters p;
  p.fullscreen = 0;
  p.soundLevel = 255;
  p.texturePack = 0;
  return p;
}
