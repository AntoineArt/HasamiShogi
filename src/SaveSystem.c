#include  <stdio.h>
#include <string.h>
#include <math.h>
#include "./headers/Types.h"

void createSave(char* name, Game* g){

	FILE *save;
	save = fopen(name, "w");
	//If the file already exist, it is erased
	fclose(save);

}

void addToSave(char* name, Game* g, Coordinates x, Coordinates y, Coordinates* tab){

	int i=0;

	FILE *save;
	save = fopen(name, "a"); //"a" for "append"
	fprintf(save,"\n");

	fprintf(save,"%c",g->turn);
	fprintf(save,",");

	fprintf(save,"%c",g->currentPlayer);
	fprintf(save,",");

	fprintf(save,"%c",x.x);
	fprintf(save,"%c",x.y);
	fprintf(save,"%c",y.x);
	fprintf(save,"%c",y.y);
	fprintf(save,",");

	for(i=1 ; i<tab[0].x ; i++) //tab[0].x is the total size of the array
	{
		fprintf(save,"%c",tab[i].x);
		fprintf(save,"%c",tab[i].y);
	}

	fclose(save);
}

int readSave(char* name){

	int c;
	FILE *save;
	save = fopen(name, "r");

	if (save) {
	    while ((c = getc(save)) != EOF)
	        putchar(c);
	    fclose(save);
	}

	return c;

}
/*
Game* loadSave(char* name){

   FILE *save;
   int c;
  
   save = fopen("file.txt","r");
   while(1)
   {
      c = fgetc(fp);
      if( feof(fp) )
      { 
         break;
      }
      printf("%c", c);
   }
   fclose(fp);
   
   return(0);
}
*/