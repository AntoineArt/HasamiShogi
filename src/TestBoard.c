#include  <stdio.h>
#include <string.h>
#include "Board.c"

void TestWrite();
void TestMovePiece();
void TestCatchPiece();
void TestCheckMove();

int main(void){

	TestWrite();
	TestMovePiece();
	return 0;
}

void TestWrite();{

	Game* g;
	Coordinates* c;
	int TestPassed = 1;
	c1->x=4;
	c1->y=4;

	write(g, 0, c);
	if(g->map[4][4]!=0){TestPassed = 0;}
	write(g, 1, c);
	if(g->map[4][4]!=1){TestPassed = 0;}
	write(g, 2, c);
	if(g->map[4][4]!=2){TestPassed = 0;}

	printf("write = %d",TestPassed);
}

void TestMovePiece(){

	Game* g;
	Coordinates c1;
	Coordinates c2;
	int TestPassed = 1;
	c1->x=4;
	c1->y=4;
	c2->x=5
	c2->y=4;
	g->map[4][4]=1

	movePiece(g, c1, c2);
	if(g->map[4][4]!=0){TestPassed = 0;}
	if(g->map[5][4]!=1){TestPassed = 0;}

	printf("movePiece = %d",TestPassed);
}

void TestCatchPiece(){
	//This function execute the catch of a token
	//It erase the token from the board, and decrease the countPlayer counter
}


void TestCheckMove(){
	//This function just give the checkMovement one more security
}





