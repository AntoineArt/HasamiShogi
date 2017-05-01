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

void write(int status, coordonnees c)
{
	m.board[c.x][c.y]=status;
}

void movePiece(c1, c2)
{
	write(m.board[c.x][c.y],c2);
	write(0,c1);
}

void furtherUpdate(int joueur, coordonnees c2)
{
	
}

bool mouvementValide(int joueur, coordonnees c1, coordonnees c2)
{
	bool boo = true;
	return boo
}

void updateBoard(int joueur, coordonnees c1, coordonnees c2)
{
	if(mouvementValide(c1,c2)){
		movePiece(c1, c2);
		furtherUpdate(joueur,c2);
	}
	else{printf("Invalid Movement!")}
}

