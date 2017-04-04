#include "Board.h"

matrice allocateBoard(int l, int c)
{
  matrice m;
  m.Data = (Piece **) malloc(sizeof(Piece*)*l);
  int i;
  for (i=0; i<l; i++) {
    m.Data[i] = (Piece *) malloc(sizeof(Piece)*c);
    }
  m.l = l;
  m.c = c;
  return m;
}

void freeBoard(matrice m) 
{
  int i;
  for (i=0; i<m.l; i++) {
    free(m.Data[i]);
  }
  free(m.Data);
  m.c = 0;
  m.l = 0;
}

Piece* accessPiece(matrice m, int i, int j) 
{
  return *(m.Data+i)+j;
}

int lineNb(matrice m) 
{
  return m.l;
}

int colNb(matrice m)
{
  return m.c;
}

void displayBoard() {
}

void shutdownBoard() {
}

void updateBoard() {
}