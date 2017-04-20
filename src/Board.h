#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <SDL/SDL.h>
#include "Piece.h"

typedef struct {
  int l,c;
  Piece **Data;
} matrice;

/*
  create a l*c matrice of Pieces
  warning : allocate memory
*/
matrice allocateBoard(int l, int c);


/*
  destroy a matrice m
  warning : free memory
*/
void freeBoard(matrice m);


/*
  access the m(i,j) element which is a pointer to a Piece
*/
Piece* accessPiece(matrice m, int i, int j);

/*
  return the number of line of the matrice m
*/
int lineNb(matrice m);


/*
  return the number of colone of the matrice m
*/
int colNb(matrice m);


/*
  display the board using SDL2.0
  pieces are displayed over background
*/
void displayBoard();

/*
  shut the display properly
  warning : do not destroy the matrice of pieces
*/
void shutdownBoard();


/*
  update the Board display while checking for Piece took over and victory
*/
void updateBoard();
