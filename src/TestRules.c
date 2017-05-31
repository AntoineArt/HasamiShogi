#include  <stdio.h>
#include <string.h>
#include "Rules.c"

void TestResetBoard();
void TestCheckVictory();
void TestCheckCatch();
void TestCheckMovement();

int main(void){

	TestResetBoard();
	TestCheckVictory();
	TestCheckCatch();
	TestCheckMovement();
	//The createTable is checked by checking checkCatch;

	return 0;
}

void TestResetBoard0(){

	Game *g0;
	Game *g1;
	g0->var=0;
	g1->var=1;
	int testPassed0 = 1;
	int testPassed1 = 1;
	int testPassed2 = 1;
	resetBoard(g0);
	resetBoard(g1);

	int i=0;
	int j=0;

	//Test for player's token
	//Var0
	for(i=0;i<9;i++){
		for(j=0;j<1;j++){
			if(g0->map[i][j]!=2){
				testPassed0=0;
			}
		}
	}
	for(i=0;i<9;i++){
		for(j=1;j<8;j++){
			if(g0->map[i][j]!=0){
				testPassed1=0;
			}
		}
	}
	for(i=0;i<9;i++){
		for(j=8;j<9;j++){
			if(g0->map[i][j]!=1){
				testPassed0=0;
			}
		}
	}
	printf("ResetBoard/var0 = %d",testPassed0);
	//Var1
	for(i=0;i<9;i++){
		for(j=0;j<2;j++){
			if(g0->map[i][j]!=2){
				testPassed1=0;
			}
		}
	}
	for(i=0;i<9;i++){
		for(j=2;j<7;j++){
			if(g0->map[i][j]!=0){
				testPassed1=0;
			}
		}
	}
	for(i=0;i<9;i++){
		for(j=7;j<9;j++){
			if(g0->map[i][j]!=1){
				testPassed1=0;
			}
		}
	}
	printf("ResetBoard/var1 = %d",testPassed1);
}

void TestCheckVictory();
{

	Game *g0;
	Game *g1;
	Coordinates c;
	g0->var=0;
	g1->var=1;
	int testPassed0 = 1;
	int testPassed1 = 1;
	int testPassed2 = 1;
	resetBoard(g0);
	resetBoard(g1);
	c.x=5;
	c.y=5;


	//Var0
	g0->currentPlayer=1;
	g0->countPlayer1=9;
	g0->countPlayer2=9;
	if(checkVictory(g0, c)!=10){testPassed0=0;}
	g0->countPlayer2=1;
	if(checkVictory(g0, c)!=1){testPassed0=0;}
	g0->currentPlayer=2;
	g0->countPlayer1=1;
	g0->countPlayer2=2;
	if(checkVictory(g0, c)!=2){testPassed0=0;}
	g0->countPlayer1=0;
	g0->countPlayer2=0;
	if(checkVictory(g0, c)!=3){testPassed0=0;}
	printf("CheckVictory/var0 = %d",testPassed0);



	//Var1
	g1->currentPlayer=1;
	g1->countPlayer1=18;
	g1->countPlayer2=18;
	if(checkVictory(g1, c)!=0){testPassed1=0;}
	g1->countPlayer2=0;
	if(checkVictory(g1, c)!=1){testPassed1=0;}
	g1->currentPlayer=2;
	g1->countPlayer1=0;
	g1->countPlayer2=18;
	if(checkVictory(g1, c)!=2){testPassed1=0;}

	g1->countPlayer1=18;
	g1->countPlayer2=18;

	g1->currentPlayer=1;
	g1->map[4][4]=1;
	g1->map[3][4]=1;
	g1->map[2][4]=1;
	g1->map[5][4]=1;
	g1->map[6][4]=1;
	if(checkVictory(g1, c)!=1){testPassed1=0;}
	resetBoard(g1);

	g1->map[4][4]=1;
	g1->map[3][3]=1;
	g1->map[2][2]=1;
	g1->map[5][5]=1;
	g1->map[6][36]=1;
	if(checkVictory(g1, c)!=1){testPassed1=0;}
	resetBoard(g1);

	g1->currentPlayer=2;
	g1->map[4][4]=2;
	g1->map[3][4]=2;
	g1->map[2][4]=2;
	g1->map[5][4]=2;
	g1->map[6][4]=2;
	if(checkVictory(g1, c)!=2){testPassed1=0;}
	resetBoard(g1);

	g1->map[4][4]=2;
	g1->map[3][3]=2;
	g1->map[2][2]=2;
	g1->map[5][5]=2;
	g1->map[6][6]=2;
	if(checkVictory(g1, c)!=2){testPassed1=0;}

	printf("CheckVictory/var1 = %d",testPassed1);
}

void TestCheckCatch(){

	Game* g;
	Coordinates c;
	int up; int right; int down; int left;
	int catching;
	testPassed = 1;



	printf("CheckCatch = %d",testPassed1);
}

void TestCheckMovement(){

	Game* g;
	Coordinates c1;
	Coordinates c2;
	int TestPassed = 1;
	int up; int right; int down; int left;
	int i = 0;

	g->var=1;
	resetBoard(g);

	c1.x = 0;
	c1.y = 0;
	c2.x = 0;
	c2.y = 1;

	//Test init
	if (checkMovement(g, c1, c2)!=0){TestPassed=0;}
	c2.y = 2;
	g->map[0][0]=0;
	if (checkMovement(g, c1, c2)!=0){TestPassed=0;}

	g->map[0][0]=2;
	c2.x = 3;
	c2.y = 3;
	if (checkMovement(g, c1, c2)!=0){TestPassed=0;}

	//Token at the center of the board tested
	resetBoard(g);
	g->map[4][4]=1;
	c1.x = 4;
	c1.y = 4;
	c2.x = 4;
	c2.y = 4;

	for(i=5;i<9;i++){
		c2.x = i;
		if (checkMovement(g, c1, c2)!=1){TestPassed=0;}
	}
	for(i=0;i<4;i++){
		c2.x = i;
		if (checkMovement(g, c1, c2)!=1){TestPassed=0;}
	}

	c2.x = 4;
	for(i=2;i<4;i++){
		c2.y = i;
		if (checkMovement(g, c1, c2)!=1){TestPassed=0;}
	}
	for(i=5;i<7;i++){
		c2.y = i;
		if (checkMovement(g, c1, c2)!=1){TestPassed=0;}
	}
	c2.y = 4;

	//Token at the center with obstacles
	resetBoard(g);
	g->map[4][4]=1;
	c1.x = 4;
	c1.y = 4;
	c2.x = 4;
	c2.y = 4;
	g->map[4][5]=2;
	g->map[4][3]=2;
	g->map[5][4]=2;
	g->map[3][4]=2;

	for(i=5;i<9;i++){
		c2.x = i;
		if (checkMovement(g, c1, c2)!=0){TestPassed=0;}
	}
	for(i=0;i<4;i++){
		c2.x = i;
		if (checkMovement(g, c1, c2)!=0){TestPassed=0;}
	}

	c2.x = 4;
	for(i=2;i<4;i++){
		c2.y = i;
		if (checkMovement(g, c1, c2)!=0){TestPassed=0;}
	}
	for(i=5;i<7;i++){
		c2.y = i;
		if (checkMovement(g, c1, c2)!=0){TestPassed=0;}
	}
	c2.y = 4;

	//Test Jump
	//Var 1
	resetBoard(g);
	g->map[4][4]=1;
	g->map[3][4]=1;
	g->map[5][4]=2;
	c1.x = 4;
	c1.y = 4;
	c2.x = 2;
	c2.y = 4;
	if (checkMovement(g, c1, c2)!=1){TestPassed=0;}
	c2.x = 6;
	c2.y = 4;
	if (checkMovement(g, c1, c2)!=1){TestPassed=0;}

	//Var 0
	g->var=0;

	c2.x = 2;
	c2.y = 4;
	if (checkMovement(g, c1, c2)!=0){TestPassed=0;}
	c2.x = 6;
	c2.y = 4;
	if (checkMovement(g, c1, c2)!=0){TestPassed=0;}

	printf("CheckMovement = %d",TestPassed);

}























