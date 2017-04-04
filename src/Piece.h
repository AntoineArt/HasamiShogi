#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int x, y; //the coordonate of the piece (maybe useless due to the implementation of the board)
  char c; //the color of the piece
} Piece;


Piece initPiece(int x, int y, char c);
//pour créé une nouvelle pièce de coordonée x,y

int getX(Piece *p);
//permet l'accès à la coordonnée x

int getY(Piece *p);
//permet l'accès à la coordonnée y

void setX(Piece *p, int x);
//permet de changer la coordonnée x

void setY(Piece *p, int y);
//permet de changer la coordonnée y