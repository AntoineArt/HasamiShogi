#include "./headers/App.h"

int main(void){
	// Initialization
	if(SDL_Init(SDL_INIT_VIDEO) !=0){
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return 1;
	}

	TTF_Init(); // Initializes the TTF library
	TTF_Font* police = TTF_OpenFont("./resources/asman.ttf", 50*SCALE_FACTOR);

	// Window creation
	SDL_Window* pWindow = NULL;
	pWindow = SDL_CreateWindow("Hasami Shogi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH*SCALE_FACTOR, DEFAULT_HEIGHT*SCALE_FACTOR, 0.);
	//Language choice
	Texts* texts;
	texts = (Texts*) malloc(sizeof(Texts));
	if (texts == NULL) {exit(0);} // if alloc failed, immediatly quit
	*texts = frText;
	// Launching the menu window
	int mode;
	Game *g = (Game*) malloc(sizeof(Game));
	if (g == NULL) {exit(0);} // if alloc failed, immediatly quit
	initGame(g, GAME_MODE_DEFAULT, VARIANT_DEFAULT);

	SDL_Color textColor ;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	mode = menu(pWindow, police, texts, textColor);

	Parameters param = initParameters(LANG_DEFAULT, DEFAULT_WIDTH, DEFAULT_HEIGHT);

	switch(mode){
		case 0: SDL_DestroyWindow(pWindow); newGame(g, param, police, texts, textColor); break;
		case 1: SDL_DestroyWindow(pWindow); continueGame(); break;
		case 2: parametersMenu(pWindow, police, texts, param); break;
		case 3: //SDL_DestroyWindow(pWindow); 
		rules(g, "./resources/Rules.txt",texts, textColor, param); break;
		case 4: SDL_DestroyWindow(pWindow); break; //quit
		default : SDL_DestroyWindow(pWindow); break;
	}
	//freeing memory
	free(texts);
	freeGame(g);
	free(g);
	// Closing everything
	TTF_CloseFont(police);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

int menu(SDL_Window* pWindow, TTF_Font* police, Texts* texts, SDL_Color textColor){
	SDL_Surface* src = SDL_LoadBMP("./resources/images/BackgroundMenu.bmp");
	SDL_Surface* pBackgroundMenu = SDL_CreateRGBSurface(0, DEFAULT_WIDTH*SCALE_FACTOR, DEFAULT_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pBackgroundMenu, NULL, SDL_MapRGB(pBackgroundMenu->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pBackgroundMenu, NULL);
	SDL_FreeSurface(src);
	updateWindow(0, 0, pWindow, pBackgroundMenu); // BackgroundMenu display

	// Menu display
	SDL_Surface *textsMenu[5];

	for(int i = 0; i<5; i++){
		textsMenu[i] = TTF_RenderText_Blended(police, texts[0].mainMenu[i], textColor);
		updateWindow(DEFAULT_WIDTH*SCALE_FACTOR/2 - textsMenu[i]->w/2,
			 					 DEFAULT_HEIGHT*SCALE_FACTOR/2 - textsMenu[i]->h/2 - (300-100*i)*SCALE_FACTOR,
								 pWindow, textsMenu[i]);
	}

	int mode;
	if (pWindow){
		mode = eventDetectionMenu(pWindow, textsMenu);
		for(int i=0; i<5; i++){
			SDL_FreeSurface(textsMenu[i]);
		}
		SDL_FreeSurface(pBackgroundMenu);
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
		x[i] = DEFAULT_WIDTH*SCALE_FACTOR/2 - w[i]/2;
		y[i] = DEFAULT_HEIGHT*SCALE_FACTOR/2 - h[i]/2-(300-100*i)*SCALE_FACTOR;
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
	SDL_FreeSurface(pWinSurf);
}

void newGame(Game *g, Parameters param, TTF_Font* police, Texts* texts, SDL_Color textColor){
	SDL_Window* pWinGame = SDL_CreateWindow("Hasami Shogi",  SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	(BOARD_WIDTH + ORANGE_BUTTON_WIDTH)*SCALE_FACTOR,
	BOARD_HEIGHT*SCALE_FACTOR,
	0.);

	SDL_Surface* src = SDL_LoadBMP("./resources/images/ShogiBoard.bmp");
	SDL_Surface* pBackgroundGame = SDL_CreateRGBSurface(0, BOARD_WIDTH*SCALE_FACTOR, BOARD_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pBackgroundGame, NULL, SDL_MapRGB(pBackgroundGame->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pBackgroundGame, NULL);
	SDL_FreeSurface(src);
	// Menu display
	updateWindow(0, 0, pWinGame, pBackgroundGame);
	setupBoard(g, pWinGame);

	src = SDL_LoadBMP("./resources/images/orangeButton.bmp");
	SDL_Surface* pButton = SDL_CreateRGBSurface(0, ORANGE_BUTTON_WIDTH*SCALE_FACTOR, ORANGE_BUTTON_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pButton, NULL, SDL_MapRGB(pButton->format, 0, 0, 0));
	SDL_BlitScaled(src, NULL, pButton, NULL);
	updateWindow(BOARD_WIDTH*SCALE_FACTOR, SCALE_FACTOR*BOARD_HEIGHT/2 - ORANGE_BUTTON_HEIGHT, pWinGame, pButton); //Positioning the button
	updateWindow(BOARD_WIDTH*SCALE_FACTOR, SCALE_FACTOR*BOARD_HEIGHT/2 + ORANGE_BUTTON_HEIGHT, pWinGame, pButton); //Positioning the button

	SDL_Surface* buttonText = TTF_RenderText_Blended(police, texts[param.lang].inGame[1], textColor);
	int buttonX = SCALE_FACTOR*(BOARD_WIDTH+(pButton->w-buttonText->w)/2);
	int buttonY = SCALE_FACTOR*BOARD_HEIGHT/2 - ORANGE_BUTTON_HEIGHT + buttonText->h/2;

	updateWindow(buttonX,	buttonY, pWinGame, buttonText); //Centering the text in the middle of the button

	buttonX = SCALE_FACTOR*(BOARD_WIDTH+(pButton->w-buttonText->w)/2);
	buttonY = SCALE_FACTOR*BOARD_HEIGHT/2 - ORANGE_BUTTON_HEIGHT + buttonText->h/2;

	SDL_FreeSurface(buttonText);
	buttonText = TTF_RenderText_Blended(police, texts[param.lang].inGame[0], textColor);
	updateWindow(buttonX,	buttonY+2*ORANGE_BUTTON_HEIGHT, pWinGame, buttonText); //Centering the text in the middle of the button

	SDL_FreeSurface(src);
	src = SDL_LoadBMP("./resources/images/BlackPiece.bmp");
	SDL_Surface* pBlackPiece = SDL_CreateRGBSurface(0, PIECE_WIDTH*SCALE_FACTOR, PIECE_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pBlackPiece, NULL, SDL_MapRGB(pBlackPiece->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pBlackPiece, NULL);

	SDL_FreeSurface(src);

	src = SDL_LoadBMP("./resources/images/RedPiece.bmp");
	SDL_Surface* pRedPiece = SDL_CreateRGBSurface(0, PIECE_WIDTH*SCALE_FACTOR, PIECE_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pRedPiece, NULL, SDL_MapRGB(pRedPiece->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pRedPiece, NULL);

	SDL_FreeSurface(src);

	src = SDL_LoadBMP("./resources/images/Yellow.bmp");
	SDL_Surface* pYellow = SDL_CreateRGBSurface(0, PIECE_WIDTH*SCALE_FACTOR, PIECE_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pYellow, NULL, SDL_MapRGB(pYellow->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pYellow, NULL);
	SDL_FreeSurface(src);

	createSave("sauvegarde", g);


	//victory contains the player who won this turn (0 if none of them, 3 if both loosed)
	int victory = 0;
	Coordinates* updatedCases;
	int i;
	while (victory==0){
		printBoard(g);
		if ( (g->gameMode==0)
		|| ((g->gameMode==1)&&(g->currentPlayer==1))
		|| ((g->gameMode==2)&&(g->currentPlayer==2)) )
		{ //human plays
			printf("human play \n");
			updatedCases = inGameEvents(g, pWinGame, buttonX, buttonY, buttonText->w, buttonText->h);
		} else { //AI plays
			printf("AI play \n");
			updatedCases = aiPlay(g);
		}
		//graphical stuff
		SDL_Surface* pToken = (g->currentPlayer == 1) ? pBlackPiece : pRedPiece;

		if (updatedCases[0].y==4) {exit(0);} //redcross pressed == rageQuit
		else {
			for(i=1; i<updatedCases[0].x; i++) {
				if (i==2)
				{
					updateWindow((DECAY_PIECES + OUTBORDER + updatedCases[i].x*(CASE_WIDTH + INBORDER))*SCALE_FACTOR, (DECAY_PIECES + OUTBORDER + updatedCases[i].y*(CASE_HEIGHT + INBORDER))*SCALE_FACTOR, pWinGame, pToken);
				} else {
					updateWindow((DECAY_PIECES + OUTBORDER + updatedCases[i].x*(CASE_WIDTH + INBORDER))*SCALE_FACTOR, (DECAY_PIECES + OUTBORDER + updatedCases[i].y*(CASE_HEIGHT + INBORDER))*SCALE_FACTOR, pWinGame, pYellow);
				}
			}
			victory = checkVictory(g, updatedCases[2]);
			(g->currentPlayer) = 3-(g->currentPlayer); //switch the current player 3-1=2 3-2=1
		}
		free(updatedCases); //malloc in inGameEvents or in aiPlay
	}
	(g->currentPlayer) = 3-(g->currentPlayer); //switch the current player , it is needed because of the last switch of the while

	if(victory == 1){victoryDisplay(1);}
	else if (victory == 2){victoryDisplay(2);}
	else if (victory == 3){defeatDisplay();} //both loosed
	else {
		//rage quit case
	}
	SDL_FreeSurface(pBlackPiece);
	SDL_FreeSurface(pRedPiece);
	SDL_FreeSurface(pYellow);
	SDL_FreeSurface(pBackgroundGame);
	SDL_FreeSurface(pButton);
	SDL_FreeSurface(buttonText);
	SDL_DestroyWindow(pWinGame);
}

void continueGame(){}

void rules(Game* g, char* name, Texts* texts, SDL_Color textColor, Parameters param){
	FILE* rules = fopen(name, "r"); //"r" for "read"
	//background
	SDL_Surface* src = SDL_LoadBMP("./resources/images/BackgroundMenu.bmp");
	SDL_Surface* pRules = SDL_CreateRGBSurface(0, RULES_WIDTH*SCALE_FACTOR, RULES_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pRules, NULL, SDL_MapRGB(pRules->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pRules, NULL);
	SDL_FreeSurface(src);

	SDL_Window* pWinRules = SDL_CreateWindow("Rules",  SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	VICTORY_WIDTH*SCALE_FACTOR,
	VICTORY_HEIGHT*SCALE_FACTOR,
	0.);
	updateWindow(0, 0, pWinRules, pRules);
	//return button
	src = SDL_LoadBMP("./resources/images/orangeButton.bmp");
	SDL_Surface* pButton = SDL_CreateRGBSurface(0, ORANGE_BUTTON_WIDTH*SCALE_FACTOR, ORANGE_BUTTON_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pButton, NULL, SDL_MapRGB(pButton->format, 0, 0, 0));
	SDL_BlitScaled(src, NULL, pButton, NULL);
	updateWindow(RULES_WIDTH*SCALE_FACTOR, SCALE_FACTOR*RULES_HEIGHT/2 - ORANGE_BUTTON_HEIGHT, pWinRules, pButton); //Positioning the button
	
	TTF_Font* police = TTF_OpenFont("./resources/asman.ttf", 15*SCALE_FACTOR);
	
	SDL_Surface* buttonText = TTF_RenderText_Blended(police, texts[param.lang].inGame[1], textColor);
	int buttonX = SCALE_FACTOR*(RULES_WIDTH+(pButton->w-buttonText->w)/2);
	int buttonY = SCALE_FACTOR*RULES_HEIGHT/2 - ORANGE_BUTTON_HEIGHT + buttonText->h/2;
	updateWindow(buttonX,	buttonY, pWinRules, buttonText); //Centering the text in the middle of the button
	//fullfill with text from file
	int lineSize = 200;
	char line[lineSize];
	while(fgets(line, lineSize, rules)!=NULL){
		
	}
	//events
	while(1){
	SDL_Event event;
	while (SDL_PollEvent(&event)) {// Event treatment
		switch(event.type){
			case SDL_WINDOWEVENT: // Window event
				if (event.window.event == SDL_WINDOWEVENT_CLOSE){ // Red cross pressed
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP: // Mouse event
				if (event.button.button == SDL_BUTTON_LEFT){
					int xM = event.button.x;
					int yM = event.button.y;
					if(isIn(xM, yM, buttonX, buttonY, pButton->w, pButton->h)){ 
						break;
					}
				}
		}
	
	}
	}
	//never used but safer
	TTF_CloseFont(police);
	SDL_FreeSurface(pRules);
	SDL_FreeSurface(pButton);
	SDL_FreeSurface(buttonText);
	SDL_DestroyWindow(pWinRules);
	fclose(rules);
}

void parametersMenu(SDL_Window* pWindow, TTF_Font* police, Texts* texts, Parameters p){
	SDL_Surface* src = SDL_LoadBMP("./resources/images/BackgroundMenu.bmp");
	SDL_Window *pWinParam = SDL_CreateWindow("Parameters",  SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	DEFAULT_WIDTH*SCALE_FACTOR,
	DEFAULT_HEIGHT*SCALE_FACTOR,
	0.);
	SDL_Surface* pBackgroundParameters = SDL_CreateRGBSurface(0, DEFAULT_WIDTH*SCALE_FACTOR, DEFAULT_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pBackgroundParameters, NULL, SDL_MapRGB(pBackgroundParameters->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pBackgroundParameters, NULL);
	SDL_FreeSurface(src);

	// Menu display
	updateWindow(0, 0, pWinParam, pBackgroundParameters); // BackgroundMenu display
	SDL_Surface *textsParameters[6]; //0=*french, 1=*english, 2=*fullscreen, 3=*sound, 4=*texturePack, 5=ORANGE;
	SDL_Color textColor ;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	for(int i = 0; i<6; i++){
		textsParameters[i] = TTF_RenderText_Blended(police, texts[p.lang].options[i], textColor);
		updateWindow(DEFAULT_WIDTH*SCALE_FACTOR/2 - (textsParameters[i]->w)/2,
								DEFAULT_HEIGHT*SCALE_FACTOR/2 - (textsParameters[i]->h)/2 - (300-100*i)*SCALE_FACTOR,
								pWinParam, textsParameters[i]);
	}

	int mode = -1;
	if(pWindow){
		while(mode!=5){
			mode = eventDetectionParameters(pWindow, textsParameters);
			switch(mode){
				case 0: p.lang = 0; printf("0\n"); break;
				case 1: p.lang = 1; printf("1\n"); break;
				case 2: p.fullscreen = !p.fullscreen; printf("2\n"); break;
				default: break;
			}
		}

		for(int i = 0; i<6; i++){
			SDL_FreeSurface(textsParameters[i]);
		}
	}

	else{
		fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
	}
	SDL_FreeSurface(pBackgroundParameters);
	SDL_DestroyWindow(pWinParam);
}

int eventDetectionParameters(SDL_Window* pWindow, SDL_Surface** texts){
	int n = 5;
	int x[n], y[n], w[n], h[n];
	for(int i = 0; i<n; i++){
		w[i] = texts[i]->w;
		h[i] = texts[i]->h;
		x[i] = DEFAULT_WIDTH*SCALE_FACTOR/2 - w[i]/2;
		y[i] = DEFAULT_HEIGHT*SCALE_FACTOR/2 - h[i]/2-(300-100*i)*SCALE_FACTOR;
	}

	while(1){
		SDL_Event event;
		while(SDL_PollEvent(&event)){

			// Event treatment
			switch(event.type){ // Which type of event is it ?
				case SDL_WINDOWEVENT: // Window event
				if (event.window.event == SDL_WINDOWEVENT_CLOSE){ // Red cross pressed
					return 5;
				}
				break;

				case SDL_MOUSEBUTTONUP: // Mouse event
				if (event.button.button == SDL_BUTTON_LEFT){
					int xM = event.button.x;
					int yM = event.button.y;
					for(int i = 0; i<6; i++){
						if(isIn(xM, yM, x[i], y[i], w[0], h[0])){return i;}
					}
				}
				default: break; //nothing happens
			}
		}
	}
	return -1; //error case
}

char isIn(int xM, int yM, int x, int y, int w, int h){
	return ((xM > x && xM < x+w) && (yM > y && yM < y+h));
}

void setupBoard(Game *g, SDL_Window* pWindow){
	SDL_Surface* src = SDL_LoadBMP("./resources/images/BlackPiece.bmp");
	SDL_Surface* pBlackPiece = SDL_CreateRGBSurface(0, PIECE_WIDTH*SCALE_FACTOR, PIECE_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pBlackPiece, NULL, SDL_MapRGB(pBlackPiece->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pBlackPiece, NULL);
	SDL_FreeSurface(src);

	src = SDL_LoadBMP("./resources/images/RedPiece.bmp");
	SDL_Surface* pRedPiece = SDL_CreateRGBSurface(0, PIECE_WIDTH*SCALE_FACTOR, PIECE_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pRedPiece, NULL, SDL_MapRGB(pRedPiece->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pRedPiece, NULL);
	SDL_FreeSurface(src);

	SDL_Surface* p1st = (g->gameMode == 2) ? pBlackPiece : pRedPiece;
	SDL_Surface* p2nd = (g->gameMode == 2) ? pRedPiece : pBlackPiece;

	for(int i = 0; i<9; i++){
		for(int j = 0; j<(g->var)+1; j++){
			updateWindow((DECAY_PIECES + OUTBORDER + i*(CASE_WIDTH + INBORDER ))*SCALE_FACTOR,
									(DECAY_PIECES + OUTBORDER + j*(CASE_HEIGHT + INBORDER))*SCALE_FACTOR,
									pWindow, p1st);  //Positioning red token
			updateWindow((DECAY_PIECES + OUTBORDER + i*(CASE_WIDTH + INBORDER))*SCALE_FACTOR,
									(DECAY_PIECES + OUTBORDER + 8 * (CASE_HEIGHT + INBORDER) - j*(CASE_HEIGHT + INBORDER))*SCALE_FACTOR,
									pWindow, p2nd);  //Positioning black token
		}
	}

	SDL_FreeSurface(p1st);
	SDL_FreeSurface(p2nd);
	//SDL_FreeSurface(pBlackPiece);
	//SDL_FreeSurface(pRedPiece);
}

void defeatDisplay(){//when both loosed
	SDL_Surface* src = SDL_LoadBMP("./resources/images/Defeat.bmp");
	SDL_Surface* pDefeat = SDL_CreateRGBSurface(0, DEFEAT_WIDTH*SCALE_FACTOR, DEFEAT_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pDefeat, NULL, SDL_MapRGB(pDefeat->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pDefeat, NULL);
	free(src);
	SDL_Window* pWinGame = SDL_CreateWindow("Defeat !",  SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	DEFEAT_WIDTH*SCALE_FACTOR,
	DEFEAT_HEIGHT*SCALE_FACTOR,
	0.);

	// Menu display
	updateWindow(DECAY_PIECES, 0, pWinGame, pDefeat);
	SDL_Delay(3000); //waiting for a click ? add button ?
	SDL_FreeSurface(pDefeat);
}

void victoryDisplay(int winner){
	SDL_Surface* src;
	if (winner==1) {
		src = SDL_LoadBMP("./resources/images/BlackVictory.bmp");
	} else {
		src = SDL_LoadBMP("./resources/images/RedVictory.bmp");
	}
	SDL_Surface* pVictory = SDL_CreateRGBSurface(0, VICTORY_WIDTH*SCALE_FACTOR, VICTORY_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
	SDL_FillRect(pVictory, NULL, SDL_MapRGB(pVictory->format, 255, 0, 0));
	SDL_BlitScaled(src, NULL, pVictory, NULL);
	SDL_FreeSurface(src);

	SDL_Window* pWinGame = SDL_CreateWindow("Victory !",  SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	VICTORY_WIDTH*SCALE_FACTOR,
	VICTORY_HEIGHT*SCALE_FACTOR,
	0.);
	updateWindow(0, 0, pWinGame, pVictory);
	SDL_Delay(2000);//waiting for a click ? add button ?
	SDL_FreeSurface(pVictory);
	SDL_DestroyWindow(pWinGame);
}

Coordinates* inGameEvents(Game *g, SDL_Window* pWindow, int buttonX, int buttonY, int buttonW, int buttonH){
	int depth;
	Coordinates c;
	Coordinates c1;
	Coordinates c2;
	Coordinates* tmpArray;
	int moveRight = 0;
	while (moveRight!=1) {// no valid move has been done 1 : true 0 : false 2 : another friendly token
		c.x=-1; c.y=-1; //initialisation made so that a invalid move can be overwritten
		if (moveRight==0) {
			c1.x=-1; c1.y=-1;
			c2.x=-1; c2.y=-1;
			depth = 0;
		}
		while (depth<2) { // 2 Clic necessary to continue
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				// Event treatment
				switch(event.type){ // Which type of event is it ?
					case SDL_WINDOWEVENT: // Window event
					if (event.window.event == SDL_WINDOWEVENT_CLOSE){ // Red cross pressed
					/*
						Coordinates *tab;
						tab = (Coordinates*) malloc(sizeof(Coordinates)*(1));
						if (tab == NULL) {exit(0);} // if alloc failed, immediatly quit
						tab[0].y=4;
						return tab;
					}*/
					exit(0);}
					break;

					case SDL_MOUSEBUTTONUP: // Mouse event
					if (event.button.button == SDL_BUTTON_LEFT){
						int xM = event.button.x;
						int yM = event.button.y;
						if(isIn(xM, yM, buttonX, buttonY, buttonW, buttonH)){
							c1.x = 100; c1.y = 100; c2.x = 100; c2.y = 100;				//todo : Réussir à court-circuiter l'analyse de clic pour lancer le ORANGE
						}
						/*
						//things like this could work more efficiently
						c.x = (xM-Marjx)/width
						c.y = (xM-Marjy)/heigth
						*/
						else{
							for(int i=0; i<9; i++){
								for(int j=0; j<9; j++){
									if(isIn(xM, yM, (DECAY_PIECES + OUTBORDER + i*(CASE_WIDTH + INBORDER))*SCALE_FACTOR, (DECAY_PIECES + OUTBORDER + j*(CASE_HEIGHT + INBORDER))*SCALE_FACTOR, PIECE_WIDTH, PIECE_HEIGHT)){
										c.x = i ; c.y = j;
									}
								}
							}
						}
					}
				}
			}
			if (c.x != -1 && c.y != -1) {//assure we clicked on the board
				if ((depth==1)&&(c.x==c1.x)&&(c.y==c1.y)) { //player clicked twice on the same token
					c1.x=-1; c1.y=-1;
					depth=0;
					hidePossibilities(g, pWindow, tmpArray);
					printf("reset");
				}else if ((depth==1)&&(g->map[c.x][c.y]==g->currentPlayer)) { //player clicked on another friendly token
					hidePossibilities(g, pWindow, tmpArray); //tmpArray is defined because of depth==1
					c1.x=c.x; c1.y=c.y;
					tmpArray = showPossible(g, c1, g->currentPlayer);
					displayPossibilities(g, pWindow, tmpArray);
					printf("new first clic %d : %d \n",c1.x,c1.y);
					
				}else if (depth==1){
					c2.x = c.x ; c2.y = c.y ; depth=2;
					printf("second clic %d : %d \n",c2.x, c2.y);
				} else if ((depth==0) && (g->map[c.x][c.y]==g->currentPlayer)) {
					c1.x = c.x ; c1.y = c.y ; depth=1;
					tmpArray = showPossible(g, c1, g->currentPlayer);
					displayPossibilities(g, pWindow, tmpArray);
					printf("first clic %d : %d \n",c1.x, c1.y);
				}
			}
			c.x=-1; c.y=-1;
		}
		if (tmpArray != NULL) {	hidePossibilities(g, pWindow, tmpArray); }
		//printf("final move %d : %d | %d -> %d : %d | %d \n", c1.x, c1.y, g->map[c1.x][c1.y], c2.x, c2.y, g->map[c2.x][c2.y]);
		moveRight = checkMove(g, c1, c2, g->currentPlayer);
	}
	printf("moving\n");
	movePiece(g,c1, c2); //the move has been checked so it is safe

	Coordinates *tabCatch;
	tabCatch = checkCatch(g, c2); //the tab of to be caught token
	catchPiece(g,tabCatch);
	
	//here comes the save

	//creating the returned tab for graphical
	Coordinates *tab;
	tab = (Coordinates*) malloc(sizeof(Coordinates)*(tabCatch[0].x+2)); //adding 2 for c1 and c2
	if (tab == NULL) {exit(0);} // if alloc failed, immediatly quit
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

void displayPossibilities(Game* g, SDL_Window* pWindow, Coordinates* coord){
	int n = coord[0].x;
	for(int i = 1; i<n; i++){
		SDL_Surface* src = SDL_LoadBMP("./resources/images/Green.bmp");
		SDL_Surface* pGreenCase = SDL_CreateRGBSurface(0, CASE_WIDTH*SCALE_FACTOR, CASE_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
		SDL_FillRect(pGreenCase, NULL, SDL_MapRGB(pGreenCase->format, 255, 0, 0));
		SDL_BlitScaled(src, NULL, pGreenCase, NULL);
		SDL_FreeSurface(src);
		updateWindow((DECAY_PIECES  + coord[i].x*(CASE_WIDTH + INBORDER))*SCALE_FACTOR,(DECAY_PIECES + INBORDER + coord[i].y*(CASE_HEIGHT + INBORDER))*SCALE_FACTOR, pWindow, pGreenCase);
	}
}

void hidePossibilities(Game* g, SDL_Window* pWindow, Coordinates* coord){
	int n = coord[0].x;
	for(int i = 1; i<n; i++){
		SDL_Surface* src = SDL_LoadBMP("./resources/images/Yellow.bmp");
		SDL_Surface* pYellowCase = SDL_CreateRGBSurface(0, CASE_WIDTH*SCALE_FACTOR, CASE_HEIGHT*SCALE_FACTOR, 32, 0, 0, 0, 0);
		SDL_FillRect(pYellowCase, NULL, SDL_MapRGB(pYellowCase->format, 255, 0, 0));
		SDL_BlitScaled(src, NULL, pYellowCase, NULL);
		SDL_FreeSurface(src);
		updateWindow((DECAY_PIECES + coord[i].x*(CASE_WIDTH + INBORDER))*SCALE_FACTOR,(DECAY_PIECES  + INBORDER + coord[i].y*(CASE_HEIGHT + INBORDER))*SCALE_FACTOR, pWindow, pYellowCase);
	}
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
