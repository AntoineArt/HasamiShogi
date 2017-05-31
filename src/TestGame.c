#include  <stdio.h>
#include <string.h>
#include "Game.c"

void TestInitGame();

int main(void){

	TestInitGame();
	return 0;
}

void TestInitGame(){

	Game* g;
	int TestPassed0 = 1;
	int TestPassed1 = 1;
	int i = 0;
	int j = 0;

	//Var 0
	initGame(g, 0, 0);
	for(i=0;i<9;i++){
		for(j=0;j<1;j++){
			if(g->map[i][j]!=2){TestPassed0=0;}
		}
	}
	for(i=0;i<9;i++){
		for(j=1;j<8;j++){
			if(g->map[i][j]!=0){TestPassed0=0;}
		}
	}
	for(i=0;i<9;i++){
		for(j=8;j<9;j++){
			if(g->map[i][j]!=1){TestPassed0=0;}
		}
	}
	if(g->gameMode!=0){TestPassed0=0;}
	if(g->countPlayer1!=9){TestPassed0=0;}
	if(g->countPlayer2!=9){TestPassed0=0;}
	if(g->currentPlayer!=1){TestPassed0=0;}

	printf("initGame/var0 = %d",TestPassed0);
	free(g);

	//Var 1
	initGame(g, 0, 1);
	for(i=0;i<9;i++){
		for(j=0;j<2;j++){
			if(g->map[i][j]!=2){TestPassed1=0;}
		}
	}
	for(i=0;i<9;i++){
		for(j=2;j<7;j++){
			if(g->map[i][j]!=0){TestPassed1=0;}
		}
	}
	for(i=0;i<9;i++){
		for(j=7;j<9;j++){
			if(g->map[i][j]!=1){TestPassed1=0;}
		}
	}
	if(g->gameMode!=1){TestPassed1=0;}
	if(g->countPlayer1!=18){TestPassed1=0;}
	if(g->countPlayer2!=18){TestPassed1=0;}
	if(g->currentPlayer!=1){TestPassed1=0;}

	printf("initGame/var0 = %d",TestPassed1);
	free(g);

}