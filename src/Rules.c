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

int checkVictory(int currentPlayer, coordinates c2)
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

coordinates* checkCatch(int currentPlayer, coordinates c2)
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
	//If the opposing token isn't a current player's one, no token can be catch
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

	//We create the table who will contain the coordonates of the near-to-be caught tokens
	return createTable(c2, up, right, down, left, 1);
}

coordinates* createTable(coordinates c, int up, int right, int down, int left, int catch){
	
	int i = up + right + down + left;
	coordinates *tab;
	tab = (coordinates*) malloc(sizeof(coordinates)*(i+1));
	coordinates ct;
	ct.x = i+1;
	tab[0] = ct;

	//Up
	if ( (catch==0)&&(up==1)&&(b.map[c.x][c.y-1]!=0) )
	{
		tab[i].x = c.x;
		tab[i].y = c.y-2;
	}
	else{
		for(i=1;i<=up;i++)
		{
			tab[i].x = c.x;
			tab[i].y = c.y-i;
		}
	}

	//Right
	if ( (catch==0)&&(right==1)&&(b.map[c.x+1][c.y]!=0) )
	{
		tab[i].x = c.x+2;
		tab[i].y = c.y;
	}
	else
	{
		for(i=1;i<=right;i++)
		{
		tab[i+up].x = c.x+i;
		tab[i+up].y = c.y;
		}
	}

	//Down
	if ( (catch==0)&&(down==1)&&(b.map[c.x][c.y+1]!=0) )
	{
		tab[i].x = c.x;
		tab[i].y = c.y+2;
	}
	else
	{
		for(i=1;i<=down;i++)
		{
		tab[i+up+right].x = c.x;
		tab[i+up+right].y = c.y+i;
		}
	}

	//Left
	if ( (catch==0)&&(left==1)&&(b.map[c.x-1][c.y]!=0) )
	{
		tab[i].x = c.x-2;
		tab[i].y = c.y;
	}
	else
	{
		for(i=1;i<=left;i++)
		{
		tab[i+up+right+down].x = c.x-i;
		tab[i+up+right+down].y = c.y;
		}
	}
	
	return tab;
}

int checkMovement(coordinates c1, coordinates c2) {

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

coordinates* showPossible(coordinates c1)
{
	//We identifie the number of cases
	int i=0; int up=0; int right=0; int down=0; int left=0;
	coordinates c2;

	//Up
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; c1.y-i >= 0 ; i++)
	{
		c2.y = c1.y-i;
		if (checkMovement(c1,c2)==1) {
			up++;
		}
	}

	//Right
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; c1.x+i <= 8 ; i++)
	{
		c2.x = c1.x+i;
		if (checkMovement(c1,c2)==1) {
			right++;
		}
	}

	//Down
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; c1.y+i <= 8 ; i++)
	{
		c2.y = c1.y+i;
		if (checkMovement(c1,c2)==1) {
			down++;
		}
	}

	//Left
	c2.x = c1.x;
	c2.y = c1.y;
	for(i=1 ; c1.x-i >= 0 ; i++)
	{
		c2.x = c1.x-i;
		if (checkMovement(c1,c2)==1) {
			left++;
		}
	}
	
	return createTable(c1, up, right, down, left, 0);
}




















