#include "./headers/App.h"

int main(void){
  // Initialization
  if(SDL_Init(SDL_INIT_VIDEO) !=0){
    fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
    return 1;
  }

  TTF_Init(); // Initializes the TTF library
  TTF_Font* police = TTF_OpenFont("./ressources/asman.ttf", 50);

  // Window creation
  SDL_Window* pWindow = NULL;
  pWindow = SDL_CreateWindow("Hasami Shogi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGTH, 0.);

  //Language choice
  Texts texts[2] = {enText, frText};
  // Launching the menu window
  int mode;
  Game *g = (Game*) malloc(sizeof(Game));
  initGame(g, GAME_MODE_DEFAULT, VARIANT_DEFAULT);

  mode = menu(pWindow, police, texts);

  Parameters param = initParameters(LANG_DEFAULT, DEFAULT_WIDTH, DEFAULT_HEIGTH);

  switch(mode){
    case 0: newGame(g, param);break;
    case 1: continueGame();break;
    case 2: parametersMenu(pWindow, police, texts, param);break;
    case 3: rules();break;
    case 4: break; //quit
    default : break;
  }

  //freeing memory
  freeGame(g);
  free(g);
  // Closing everything

  TTF_CloseFont(police);
  TTF_Quit();

  SDL_DestroyWindow(pWindow);
  SDL_Quit();
  return 0;
}

int menu(SDL_Window* pWindow, TTF_Font* police, Texts* texts){
  SDL_Surface* pBackgroundMenu = SDL_LoadBMP("./ressources/images/BackgroundMenu.bmp");
  /*pWindow = SDL_CreateWindow("Hasami Shogi",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              DEFAULT_WIDTH,
                                              DEFAULT_HEIGTH,
                                              0.);
                                              */

  updateWindow(0, 0, pWindow, pBackgroundMenu); // BackgroundMenu display

  // Menu display
    SDL_Surface *textsMenu[5];
    SDL_Color textColor ;
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;

    int i;
    for(i = 0; i<5; i++){
      textsMenu[i] = TTF_RenderText_Blended(police, texts[0].mainMenu[i], textColor);
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
  return -1;
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
            for(int i = 0; i<=4; i++){
            	if(isIn(xM, yM, x[i], y[i], w[0], h[0])){return i;}
		}
          }
        default: break; //nothing happen
      }
    }
  }
  return -1; //error case
}

void updateWindow(int x, int y, SDL_Window* pWindow, SDL_Surface* pImage){
  int *w = NULL, *h = NULL;
  SDL_GetWindowSize(pWindow, w, h); // Gets the width and the heigth of the current window

  SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);
  SDL_Rect dest = {x, y, 0, 0};
  SDL_BlitSurface(pImage, NULL, pWinSurf, &dest);
  SDL_UpdateWindowSurface(pWindow);
}

void newGame(Game *g, Parameters param){
  SDL_Window* pWinGame = SDL_CreateWindow("Hasami Shogi",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              1200,
                                              1353,
                                              0.);
  SDL_Surface* pBackgroundGame = SDL_LoadBMP("./ressources/images/ShogiBoard.bmp");
  // Menu display
  updateWindow(DECAY_PIECES, 0, pWinGame, pBackgroundGame);
  setupBoard(g, pWinGame);


  SDL_Surface* pBlackPiece = SDL_LoadBMP("./ressources/images/BlackPiece.bmp");
  SDL_Surface* pRedPiece = SDL_LoadBMP("./ressources/images/RedPiece.bmp");
  SDL_Surface* pYellow = SDL_LoadBMP("./ressources/images/Yellow.bmp");
  //victory contains the player who won this turn (0 if none of them, 3 if both loosed)
  int victory = 0;
  Coordinates* updatedCases;
  int i;
  while (victory==0){
    //ajouter IAplay

    SDL_Surface* pToken = (g->currentPlayer == 1) ? pBlackPiece : pRedPiece;

    updatedCases = inGameEvents(g);
    if (updatedCases[0].y==4) {break;} //redcross pressed == rageQuit
    else {
    for(i=1; i<updatedCases[0].x; i++) {
    	if (i==2)
    	{
    		updateWindow(DECAY_PIECES + 68 + 8 + updatedCases[i].x*(115+4), 68+8 + updatedCases[i].y*(131+4), pWinGame, pToken);
    	} else {
		updateWindow(DECAY_PIECES + 68 + 8 + updatedCases[i].x*(115+4), 68+8 + updatedCases[i].y*(131+4), pWinGame, pYellow);
    	}
    }

    victory = checkVictory(g, updatedCases[2]);
    (g->currentPlayer) = 3-(g->currentPlayer); //switch the current player 3-1=2 3-2=1
    }
    free(updatedCases); //malloc in inGameEvents
  }
  (g->currentPlayer) = 3-(g->currentPlayer); //switch the current player , I think it is needed because of the last switch of the while
  if(victory == 1){victoryDisplay(1);}
  else if (victory == 2){victoryDisplay(2);}
  else if (victory == 3){defeatDisplay();} //both loosed
  else {
  //rage quit case
  }
}

void continueGame(){

}

void rules(){

}

void parametersMenu(SDL_Window* pWindow, TTF_Font* police, Texts* texts, Parameters p){
  SDL_Surface* pBackgroundParameters = SDL_LoadBMP("./ressources/images/BackgroundMenu.bmp");
  SDL_Window *pWinParam = SDL_CreateWindow("Parameters",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              DEFAULT_WIDTH,
                                              DEFAULT_HEIGTH,
                                              0.);

    // Menu display
    updateWindow(0, 0, pWinParam, pBackgroundParameters); // BackgroundMenu display
    SDL_Surface *textsParameters[6]; //0=*french, 1=*english, 2=*fullscreen, 3=*sound, 4=*texturePack, 5=previous;
    SDL_Color textColor ;
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;

    for(int i = 0; i<6; i++){
      textsParameters[i] = TTF_RenderText_Blended(police, texts[p.lang].options[i + 5], textColor);
      updateWindow(960 - textsParameters[i]->w/2, 540 - textsParameters[i]->h/2 - (300-100*i), pWinParam, textsParameters[i]);
    }
    SDL_Delay(2000);
    SDL_FreeSurface(pBackgroundParameters);
    SDL_DestroyWindow(pWinParam);
}

char isIn(int xM, int yM, int x, int y, int w, int h){
  return ((xM > x && xM < x+w) && (yM > y && yM < y+h));
}

void setupBoard(Game *g, SDL_Window* pWindow){
  SDL_Surface* pBlackPiece = SDL_LoadBMP("./ressources/images/BlackPiece.bmp");
  SDL_Surface* pRedPiece = SDL_LoadBMP("./ressources/images/RedPiece.bmp");

  SDL_Surface* p1st = (g->gameMode == 2) ? pBlackPiece : pRedPiece;
  SDL_Surface* p2nd = (g->gameMode == 2) ? pRedPiece : pBlackPiece;

  for(int i = 0; i<9; i++){
    for(int j = 0; j<(g->var)+1; j++){
      updateWindow(DECAY_PIECES + 68 + 8 + i*(115+4), 68+8 + j*(131+4), pWindow, p1st);  //Positioning red token
      updateWindow(DECAY_PIECES + 68 + 8 + i*(115+4), 68+8 + 8 * (131+4) - j*(131+4), pWindow, p2nd);  //Positioning black token
    }
  }
}

void defeatDisplay(){//when both loosed
	SDL_Surface* pBackground = SDL_LoadBMP("./ressources/images/Defeat.bmp");
  	SDL_Window* pWinGame = SDL_CreateWindow("Defeat !",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              600,
                                              600,
                                              0.);

  	// Menu display
  	updateWindow(DECAY_PIECES, 0, pWinGame, pBackground);
  	SDL_Delay(3000); //waiting for a click ? add button ?
}

void victoryDisplay(int winner){
	SDL_Window* pWinGame = SDL_CreateWindow("Victory !",  SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              600,
                                              600,
                                              0.);
  	SDL_Surface* pBackground = SDL_LoadBMP("./ressources/images/victory.bmp");
  	updateWindow(0, 0, pWinGame, pBackground);
  	SDL_Surface* pName;
  	if (winner==1) {
  		pName = SDL_LoadBMP("./ressources/images/J1.bmp");
  	} else {
  		pName = SDL_LoadBMP("./ressources/images/J2.bmp");
  	}
  	updateWindow(0, 0, pWinGame, pName); //todo should be aligned
  	SDL_Delay(3000);//waiting for a click ? add button ?
}

Coordinates* inGameEvents(Game *g){
  int depth;
  Coordinates c;
  Coordinates c1;
  Coordinates c2;

  int moveRight = 0;
  while (moveRight!=1) {// no valid move has been done 1 : true 0 : false 2 : another friendly token
  c.x=-1; c.y=-1; //initialisation made so that a invalid move can be overwritten
  if (moveRight==0) {
  	c1.x=-1; c1.y=-1;
  	c2.x=-1; c2.y=-1;
  	depth = 0;
  } else { //means moveRight==2
  	c1.x=c2.x; c1.y=c2.y;
  	c2.x=-1; c2.y=-1;
  	depth = 1;
  }
   while (depth<2) { // 2 Clic necessary to continue

      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        // Event treatment
        switch(event.type){ // Which type of event is it ?
          case SDL_WINDOWEVENT: // Window event
            if (event.window.event == SDL_WINDOWEVENT_CLOSE){ // Red cross pressed
              Coordinates *tab;
  	      tab = (Coordinates*) malloc(sizeof(Coordinates)*(1));
  	      tab[0].y=4;
              return tab;
            }
            break;

          case SDL_MOUSEBUTTONUP: // Mouse event
            if (event.button.button == SDL_BUTTON_LEFT){
              int xM = event.button.x;
              int yM = event.button.y;
              /*
              //things like this could work more efficiently
              c.x = (xM-Marjx)/width
              c.y = (xM-Marjy)/heigth
              */
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
      if (c.x != -1 && c.y != -1) {//assure we clicked on the board
        if(c.x==c1.x && c.y==c1.y){ //player clicked twice on the same token
          c1.x=-1; c1.y=-1;
          depth=0;
        }
        if ((depth==1) && (g->map[c.x][c.y]==0) ){//means destination is empty
          c2.x = c.x ; c2.y = c.y ; depth=2;
          printf("second clic %d : %d \n",c2.x, c2.y);
        }

        if ((depth==0) && (g->map[c.x][c.y]==g->currentPlayer)) {
          c1.x = c.x ; c1.y = c.y ; depth=1;
          //display available mouvement and catchs
          printf("first clic %d : %d \n",c1.x, c1.y);
        }
      }
      c.x=-1; c.y=-1;
    }
    printf("final move %d : %d | %d -> %d : %d | %d \n", c1.x, c1.y, g->map[c1.x][c1.y], c2.x, c2.y, g->map[c2.x][c2.y]);
    moveRight = checkMove(g, c1, c2);
  }
  movePiece(g,c1, c2); //the move has been checked so it is safe

  Coordinates *tabCatch;
  tabCatch = checkCatch(g, c2); //the tab of to be caught token
  catchPiece(g,tabCatch);

  //creating the returned tab for graphical
  Coordinates *tab;
  tab = (Coordinates*) malloc(sizeof(Coordinates)*(tabCatch[0].x+2)); //adding 2 for c1 and c2
  tab[0].x = tabCatch[0].x+2;
  tab[0].y = 0;
  tab[1] = c1;
  tab[2] = c2;
  int i;
  for (i=1; i<(tabCatch[0].x); i++) {
  	tab[i+2]=tabCatch[i];
  }
  free(tabCatch); //malloc in checkCatch
  return tab;
}





Parameters initParameters(int lang, int resX, int resY){
  Parameters p;
  p.fullscreen = 0;
  p.soundLevel = 255;
  p.texturePack = 0;
  p.lang = lang;
  p.screenResX = resX;
  p.screenResY = resY;
  return p;
}
