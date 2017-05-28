#include  <stdio.h>
#include <string.h>
#include <math.h>
#include "./headers/Types.h"

void createSave(char* name, Game* g){

	FILE *save;
	save = fopen(name, "w");
	//If the file already exist, it is erased
	fclose(save);

	//SE SERVIR DE LA PREMIERE LIGNE POUR METTRE LES OPTIONS :
	//int gameMode
	//int var
	//int countPlayer1
	//int countPlayer2
	//int currentPlayer

}

void addToSave(char* name, Game* g, Coordinates c1, Coordinates c2, Coordinates* tab){

	int i=0;

	FILE *save;
	save = fopen(name, "a"); //"a" for "append"
	fprintf(save,"\n");

	fprintf(save,"%c",g->turn);
	fprintf(save,"/");

	fprintf(save,"%c /",g->currentPlayer);

	fprintf(save,"%c",c1.x);
	fprintf(save,"%c",c1.y);
	fprintf(save,"%c",c2.x);
	fprintf(save,"%c",c2.y);
	fprintf(save,"/");

	for(i=1 ; i<tab[0].x ; i++) //tab[0].x is the total size of the array
	{
		fprintf(save,"%c",tab[i].x);
		fprintf(save,"%c",tab[i].y);
		fprintf(save,",");
	}

	fclose(save);
}

int readSave(char* name, int n){

    FILE* fichier = NULL;
    char chaine[1000] = "";
 
    fichier = fopen("destination.txt", "r");
    int i = 0;
 
    if (fichier != NULL)
    {
        while ((fgets(chaine, TAILLE_MAX, fichier) != NULL)&&(i<n)) // The file is read while fgets doesn't return an error (NULL)
        {
            i++;
        }
 
        fclose(fichier);
    }

    return chaine;
}

int playPlayed(char* name, int n){
	char* string = readSave(name, n);
	return analysePlay(string);
}

coordinates* analysePlay(char* input){

	int count=0; // used to count the number of "/"
	int count2=0; // used to fill the coordinates datas
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

}
