#include "Rules.h"

void resetBoard() {
	switch (g.var)
	{
		int i;
		case 0:
		for(i=0;i<=9;i++){
			b.map[0][i]=2; //First player's tokens
			b.map[9][i]=1; //Second player's tokens
			int j;
			for(j=2;j<=7;j++){
				b.map[j][i]=0;
			}
		}
		break;
		case 1:
		for(i=0;i<=9;i++){
			int j;
			for(j=0;j<=1;j++){
				b.map[j][i]=1; //First player's tokens
			}
			for(j=2;j<=7;j++){
				b.map[j][i]=0;
			}
			for(j=8;j<=9;j++){
				b.map[j][i]=2; //Second player's tokens
			}
		}
		break;
		default:
		printf("Invalid var");
	}
}

int checkVictory(int currentPlayer, coordonates c2)
{
	//We check if the opponent has loose every tokens but one
	if (g.var==0)
	{
		if ((currentPlayer == 1)&&(b.countPlayer2==1))
		{
			return 1;
		}
		else if ((currentPlayer == 2)&&(b.countPlayer1==1))
		{
			return 2;
		}
		else if ((b.countPlayer1<1)||(b.countPlayer2<1))
		{
			return 3; //Both players loose ; TO BE CHECKED
		}
		else
		{
			return 0; //Game continue
		}
	}
	else if(g.var==1)
	{
		if(((currentPlayer==1)&&(c2.y <= 6)) || ((currentPlayer==2)&&(c2.y >= 2)))
		{
			int i; int number=1;
			//Check Collumn
			//Up
			i=1;
			while(
				  (((currentPlayer == 1)&&(b.map[c2.x][c2.y-i]==1)&&(c2.y-i>=0))
				  ||
				  ((currentPlayer == 2)&&(b.map[c2.x][c2.y-i]==1)&&(c2.y-i>=2))
				  )&&(number<5)
				 )
			{
				number++;
				i++;
			}
			//Down
			i=1;
			while(
				  (((currentPlayer == 1)&&(b.map[c2.x][c2.y+i]==1)&&(c2.y+i<=6))
				   ||
				   ((currentPlayer == 2)&&(b.map[c2.x][c2.y+i]==1)&&(c2.y+i<=8))
				  )&&(number<5)
				 )
			{
				number++;
				i++;
			}
			if(number>=5){return currentPlayer;} //The current player win
			else{number=1;}

			//Check Diag UpL-DownR
			//UpL
			i=1;
			while(
				  (((currentPlayer == 1)&&(b.map[c2.x-i][c2.y-i]==1)&&(c2.y-i>=0)&&(c2.x-i>=0))
				  ||
				  ((currentPlayer == 2)&&(b.map[c2.x-i][c2.y-i]==1)&&(c2.y-i>=2)&&(c2.x-i>=0))
				  )&&(number<5)
				 )
			{
				number++;
				i++;
			}
			//DownR
			i=1;
			while(
				  (((currentPlayer == 1)&&(b.map[c2.x+i][c2.y+i]==1)&&(c2.y+i<=6)&&(c2.x+i<=8))
				  ||
				  ((currentPlayer == 2)&&(b.map[c2.x+i][c2.y+i]==1)&&(c2.y+i<=8)&&(c2.x+i<=8))
				  )&&(number<5)
				 )
			{
				number++;
				i++;
			}

			if(number>=5){return currentPlayer;} //The current player win
			else{number=1;}

			//Check Diag UpR-DownL
			//UpR
			i=1;
			while(
				  (((currentPlayer == 1)&&(b.map[c2.x+i][c2.y-i]==1)&&(c2.y-i>=0)&&(c2.x+i<=8))
				  ||
				  ((currentPlayer == 2)&&(b.map[c2.x+i][c2.y-i]==1)&&(c2.y-i>=2)&&(c2.x+i<=8))
				  )&&(number<5)
				 )
			{
				number++;
				i++;
			}
			//DownL
			i=1;
			while(
				  (((currentPlayer == 1)&&(b.map[c2.x-i][c2.y+i]==1)&&(c2.y+i<=6)&&(c2.x-i>=0))
				  ||
				  ((currentPlayer == 2)&&(b.map[c2.x-i][c2.y+i]==1)&&(c2.y+i<=8)&&(c2.x-i>=0))
				  )&&(number<5)
				 )
			{
				number++;
				i++;
			}

			if(number>=5){return currentPlayer;} //The current player win
		}
		else
		{
			return 0; //No one win this turn
		}
	}
	else
	{
		return -1; //Error case
	}
}

coordonates* checkCatch(int currentPlayer, coordonates c2)
{
	//We identifie the number of tokens we will catch in the named direction
	int up=0; int right=0; int down=0; int left=0;
	int opponent = 3-currentPlayer;
	int i;

	//Up
	i=1;
	while((c2.y-i >= 0) && (b.map[c2.x][c2.y-i] == opponent))
	{
		up++;
		i++;
	}
	if ((c2.y-i == -1) || (b.map[c2.x][c2.y-i] != currentPlayer)){up = 0;}

	//Right
	i=1;
	while((c2.x+i <= 8) && (b.map[c2.x+i][c2.y] == opponent))
	{
		right++;
		i++;
	}
	if ((c2.x+i == 9) || (b.map[c2.x+i][c2.y] != currentPlayer)){right = 0;}

	//Down
	i=1;
	while((c2.y+i <= 8) && (b.map[c2.x][c2.y+i] == opponent))
	{
		down++;
		i++;
	}
	if ((c2.y+i == 9) || (b.map[c2.x][c2.y+i] != currentPlayer)){down = 0;}

	//Left
	i=1;
	while((c2.x-i >= 0) && (b.map[c2.x-i][c2.y] == opponent))
	{
		left++;
		i++;
	}
	if ((c2.x+i == -1) || (b.map[c2.x-i][c2.y] != currentPlayer)){left = 0;}

	i = up + right + down + left;

	//We create the table who will contain the coordonates of the near-to-be caught tokens
	coordonates *tab;
	tab = (coordonates*) malloc(sizeof(coordonates)*(i+1));
	coordonates c1;
	c1.x = i+1;
	tab[0] = c1;

	for(i=1;i<=up;i++)
	{
		tab[i].x = c2.x;
		tab[i].y = c2.y-i;
	}
	for(i=1;i<=right;i++)
	{
		tab[i+up].x = c2.x+i;
		tab[i+up].y = c2.y;
	}
	for(i=1;i<=down;i++)
	{
		tab[i+up+right].x = c2.x;
		tab[i+up+right].y = c2.y+i;
	}
	for(i=1;i<=left;i++)
	{
		tab[i+up+right+down].x = c2.x-i;
		tab[i+up+right+down].y = c2.y;
	}

	return tab;
}

int checkMovement(coordonates c1, coordonates c2) {

	//Check if the start isn't empty
	if(b.map[c1.x][c1.y]==0){return 0;}

	//Check if the destination is empty
	if(b.map[c2.x][c2.y]!=0){return 0;}

	//Check déplacement ligne ou colonne
	if((c1.x!=c2.x)&&(c1.y!=c2.y)){return 0;}
	else
	{
		//1:Up, 2:Right, 3:Down, 4:Left
		int typeMovement = 0;
		if (c1.x>c2.x) {typeMovement=4;}
		else if (c1.x<c2.x) {typeMovement=2;}
		else if (c1.y>c2.y) {typeMovement=1;}
		else if (c1.y<c2.y) {typeMovement=3;}

		//Check if there is a token on the way
		//If Var=1, check if it's a jump
		switch (typeMovement)
		{
			case 1:
				if((g.var==1)&&(c1.y-c2.y==2)&&(b.map[c1.x][c1.y-1]!=0)){return 1;}
				else
				{
					int i;
					for(i=0 ; i<(c1.y-c2.y) ; i++)
					{
						if(b.map[c1.x][c1.y-i]!=0){return 0;}
					}
				}
			case 2:
				if((g.var==1)&&(c1.x-c2.x==-2)&&(b.map[c1.x+1][c1.y]!=0)){return 1;}
				else
				{
					int i;
					for(i=0 ; i<(c2.x-c1.x) ; i++)
					{
						if(b.map[c1.x+i][c1.y]!=0){return 0;}
					}
				}
			case 3:
				if((g.var==1)&&(c1.y-c2.y==-2)&&(b.map[c1.x][c1.y+1]!=0)){return 1;}
				else
				{
					int i;
					for(i=0 ; i<(c2.y-c1.y) ; i++)
					{
						if(b.map[c1.x][c1.y+i]!=0){return 0;}
					}
				}
			case 4:
				if((g.var==1)&&(c1.x-c2.x==2)&&(b.map[c1.x-1][c1.y]!=0)){return 1;}
				else
				{
					int i;
					for(i=0 ; i<(c1.x-c2.x) ; i++)
					{
						if(b.map[c1.x-i][c1.y]!=0){return 0;}
					}
				}
		}
		//Default case
		return 1;
	}
	//Never used
	return 0;
}

<<<<<<< HEAD
/*bool checkSuicide(currentPlayer, coordonates c2);
{
=======
/*int checkSuicide(currentPlayer, coordonates c2);
{	
>>>>>>> 5495c791045b11331dde501c39ff69116213cd16
	if(g.var==1)
	{
		opponent = 3-currentPlayer;
		if()
	}
	else
	{
		return 0;
	}
<<<<<<< HEAD

}*/
=======
	
}*/
>>>>>>> 5495c791045b11331dde501c39ff69116213cd16
