#include  <stdio.h>
#include <string.h>
#include <stddef.h>
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

  FILE* save = fopen(name, "r");
	if(save){
		//Declaration zone
		int lineSize = 100;
		char line[lineSize];
		char* eltsArray[30];


		//First line get
		fgets(line, lineSize, save);
		strsep(eltsArray, "/");
		g->gameMode = strToInt(eltsArray[0]);
		g->var = strToInt(eltsArray[1]);

		//Movements get
		char element[10];
		int i = 0;
		while(fgets(line, lineSize, save)){
			char *eltsArray[30]; //reinitializing eltsArray
			strsep(eltsArray, "/");
			while(strcmp(eltsArray[i], "stop") != 1){ //we check the assignation worked


			}
		}
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
