#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Piece.h"

int main(int argc, char *argv[]){return 0;}

typedef struct{
  int x, y;
}Piece;

void initPiece(int x, int y){
  Piece p;
  p.x = x;
  p.y = y;
}

void setX(Piece *p, int x){
  p -> x = x;
}

void setY(Piece *p, int y){
  p -> y = y;
}
