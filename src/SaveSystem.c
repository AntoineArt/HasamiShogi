#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "./headers/SaveSystem.h"

void createSave(char* name, Game* g){
	//Declaration zone
	FILE *save;
	save = fopen(name, "w"); //If the file exists, overwrite it, else creates it
	if(save){
		//File printing zone
			//We display on first line :
			//int gameMode
			//int var

		fprintf(save, "%d/%d\n", g->gameMode, g->var);

		/*for(int i = 0; i<9; i++){
			for(int j = 0; j<9; j++){
				currentState = g->map[i][j];
				sprintf(str, "%d/", currentState);
				fputs(str, save);
				if(j==8){
					fputs("\n", save);
				}
			}
		}*/  //Uncomment the loops to save the board, useful to see some things
	}
	fclose(save);
}

void addToSave(char* name, Coordinates c1, Coordinates c2, Coordinates* takenPiecesTab, int turn){
	FILE *save;
	save = fopen(name, "a"); //"a" for "append"
	if(save){
		fprintf(save, "%d/%d/%d/%d/%d", turn, c1.x, c1.y, c2.x, c2.y);

		for(int i=1 ; i<takenPiecesTab[0].x ; i++) //tab[0].x is the total size of the array
		{
			fprintf(save,"%d/",takenPiecesTab[i].x);
			fprintf(save,"%d/",takenPiecesTab[i].y);
		}
		fprintf(save, "stop\n");
	}
	fclose(save);
}

void loadSave(Game* g, char* name){

  FILE* save = fopen(name, "r"); //"r" for "read"
	if(save){
		//Declaration zone
		const char del = "/";
		int lineSize = 100;
		char line[lineSize];
		char* charElt = NULL;
		int* gvars = malloc(sizeof(int)*lineSize);
		if (gvars==NULL) {exit(0);}
		int i;
		//First line get
		if (fgets(line, lineSize, save)!=NULL) { //this lineSize might be shorter or longer tha others because it is the first and has different purpose
			i=1;
			while((charElt = strtok(line, &del)) != NULL){ //not completly sure about the pointer and addresses we're giving, but strsep is not C99 but gnu99 which is affecting the portability
        			gvars[i] = strToInt(charElt);
        			i++;
    			}
    			gvars[0]=i;
			g->gameMode = gvars[1];
			g->var = gvars[2];
		}
		free(gvars);
		
		//Movements get
		int player;
		Coordinates c1;
		Coordinates c2;
		Coordinates *tabCatch;
		int* elt = malloc(sizeof(int)*lineSize);
		if (elt==NULL) {exit(0);}
 		while(fgets(line, lineSize, save)!=NULL){
			i=1;
			while((charElt = strtok(line, &del)) != NULL){
        			elt[i] = strToInt(charElt);
        			i++;
    			}
    			elt[0]=i;
    			player = elt[1];
    			c1.x = elt[2];
    			c1.y = elt[3];
    			c2.x = elt[4];
    			c2.y = elt[5];
    			tabCatch = (Coordinates*) malloc(sizeof(Coordinates)*(elt[0]-6)/2); 
			if (tabCatch == NULL) {exit(0);} // if alloc failed, immediatly quit
			int j = 0;
    			for (i=0; i<elt[0]-6; i=i+2) {
    				tabCatch[j].x = elt[i+6];
    				tabCatch[j].y = elt[i+1+6];
    				j++;
    			}
    			movePiece(g, c1, c2);
    			catchPiece(g, tabCatch);
    			free(tabCatch);
		}
		free(elt);
	}

  fclose(save);
}

/*
int playPlayed(char* name, int n){
	char* string = readSave(name, n);
	return analysePlay(string);
}

Coordinates* analysePlay(char* input){

	int count=0; // used to count the number of "/"
	int count2=0; // used to fill the Coordinates datas
	Coordinates *tab;
	tab = (Coordinates*) malloc(sizeof(Coordinates)*(???)); // DETERMINER TAILLE POUR LE PLAY PLUS LES PIECES PRISES
	//why not use updatedCases from App.c:182 for writing
	//and writing the size of the tab somewhere at the beginning of each line
	for(i=0;i<strlen(input);i++){
		if input[i]="/";{
			count++;
		}
		else if(count==0){}
		else if(count==1){}
		else if(count==2)
		{
			tab[count].x = input[i]
			tab[count].y = input[i+1]
			i++; // disgusting, but functional
			count2++;
		}
		else //count == 3
		{
			tab[count].x = input[i]
			tab[count].y = input[i+1]
			i++; // still disgusting, though
			count2++;
		}
	}

	return tab;

}

Game* loadSave(char* name){

	Game* game;

	FILE* fichier = NULL;
    	char chaine[1000] = "";
    	fichier = fopen(name, "r");

	fgets(chaine, TAILLE_MAX, fichier); // Is used for the first lign

	//S'EN SERVIR POUR LES OPTIONS :
	//game->gameMode
	//game->var
	//game->countPlayer1
	//game->countPlayer2
	//game->currentPlayer

	resetBoard(game); // it initialise the board
	int i = 0;
	while (

	//FOR I IN RANGE LE RESTE DES PLAYS
		//RECUPERER LE PLAY A L'AIDE DES FONCTIONS PRECEDENTES
		//UTILISER LA FONCTION WRITE DE RULES POUR ECRIRE DIRECTEMENT SUR LE BOARD (PAS LA PEINE DE VERIFIER)

	Game->turn = i; // i is the number of turn played

	return game;

}*/

int strToInt(char a[]) {
  int c, sign, offset, n;

  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }

  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }

  n = 0;

  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }

  if (sign == -1) {
    n = -n;
  }

  return n;
}
