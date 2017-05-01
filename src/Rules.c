#include Rules.h

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

int checkVictory()
{
	if ()
}

void checkCatch()
{

}

bool checkMovement(coordonates c1, coordonates c2)
{
	bool boo = true;
	//Check si case différente
	//Check déplacement ligne ou colonne
	//Check si quelqu'un sur le chemim
		//Si var=1, check si c'est un saut
	return boo
}

