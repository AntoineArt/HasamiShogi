#include "Piece.h"



Piece initPiece(int x, int y, char c){
  Piece p;
  p.x = x;
  p.y = y;
  p.c = c;
  return p;
}

int getX(Piece *p) {
  return p->x;
  }

int getY(Piece *p) {
  return p->y;
  }

void setX(Piece *p, int x){
  p -> x = x;
}

void setY(Piece *p, int y){
  p -> y = y;
}
