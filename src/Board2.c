#include Board2.h

matrice allocateBoard()
{
	matrice m;
}

void resetBoard(matrice m){
	for(i=0;i<=9;i++){
		for(j=0;j<=1;j++){
			m.board[j][i]=1; //Pieces du J1
		}
		for(j=2;j<=7;j++){
			m.board[j][i]=0;
		}
		for(j=8;j<=9;j++){
			m.board[j][i]=2; //Pieces du J2
		}
	}
}

void updateBoard(coordonnees c1, coordonnees c2)
{

}

void furtherUpdate()
{

}

bool mouvementValide(int joueur, coordonnees c1, coordonnees c2)
{
	bool boo = true;
	return boo
}