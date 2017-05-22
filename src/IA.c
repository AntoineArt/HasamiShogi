#include "./headers/IA.h"

Coordinates* aiPlay(Game *g) {
	// int difficulty might control depth
	int depth = 1; //warning depth 0 create infinite loop
	Tree *root = (Tree*)malloc(sizeof(Tree));
	initNode(root);
	double ninf=-INFINITY;
        double pinf=INFINITY;
	Coordinates c1;
	Coordinates c2;
	c1.x=-1;
	c1.y=-1;
	c2.x=-1;
	c2.y=-1;
	while (checkMove(g, c1, c2) != 1) { //useless by construction but still safer
		buildTree(g, depth, root);
		double bestmove = alphabeta(g, root, depth, ninf, pinf); //find the path through victory
		c1.x=-1;
		c1.y=-1;
		c2.x=-1;
		c2.y=-1;
		int i;
		for (i=0; i<(root->nbofSons); i++) {//finding the selected move between the available one
			if (((root->sons[i])->value)==bestmove) {
				c1 = (((root->sons)[i])->c1);
				c2 = (((root->sons)[i])->c2);
				break; //not usefull to go further
			}
		}
		printf("  %d : %d -> %d : %d with value %lf \n",c1.x,c1.y,c2.x,c2.y, bestmove);
	}
	movePiece(g, c1, c2); //the move is safe by construction

  	Coordinates *tabCatch;
  	tabCatch = checkCatch(g, c2); //the tab of to be caught token
  	catchPiece(g,tabCatch);
  	//creating the returned tab for graphical update
  	Coordinates *tab;
  	tab = (Coordinates*) malloc(sizeof(Coordinates)*(tabCatch[0].x+2)); //adding 2 for c1 and c2
  	tab[0].x = tabCatch[0].x+2;
  	tab[0].y = 0;
  	tab[1] = c1;
  	tab[2] = c2;
  	int i;
  	for (i=1; i<(tabCatch[0].x); i++) {
  		tab[i+2]=tabCatch[i];
  	}
  	free(tabCatch); //malloc in checkCatch
  	freeTree(root);
  	return tab;
}


double alphabeta(Game *g, Tree *P, int depth, double a, double b) { //a<b
	if (P->nbofSons==0 || depth==0) //means P is a leave
	{
	return P->value; //returning value of leave
	} else if (g->currentPlayer==2) {//is ia
	double best = -INFINITY;
	int i;
	for (i=0; i<(P->nbofSons); i++) {
		double val;
		val = alphabeta(g, P->sons[i], depth-1,-b,-a);
		best = (best < val) ? val : best;
		a = (a < val) ? val : a ; //α := max(α, v)
		if (b <= a) {
			break; // β cut-off
		}
	}
	P->value=best; //saving the value
	return best; //continuing the recursive search
	} else {
	double best = +INFINITY;
	int i;
	for (i=0; i<(P->nbofSons); i++) {
		double val;
		val = alphabeta(g, P->sons[i], depth-1,-b,-a);
		best = (best > val) ? val : best;
		a = (a > val) ? val : a ; //α := max(α, v)
		if (b <= a) {
			break; // α cut-off
		}
	}
	P->value=best; //saving the value
	return best; //continuing the recursive search
	}
}

void buildTree(Game* g, int depth, Tree *dad) {
	if (depth > 0) {
		int tokenNb = g->currentPlayer==1 ? g->countPlayer1 : g->countPlayer2;
		Coordinates* friendlyTokenTab = friendlyToken(g);
		int i;
		for (i=0; i<tokenNb; i++) { //always at least 1 token else defeat ? TO be checked?
			Coordinates c1 = friendlyTokenTab[i];
			Coordinates* moves = showPossible(g, c1); //available moves
			int j;
			for (j = 1 ; j<(moves[0].x) ; j++) {
				Tree *newSon = (Tree*)malloc(sizeof(Tree));
				initNode(newSon);
				newSon->value = 0 ; //is overwritten by alpha beta
				newSon->c1 = c1;
				newSon->c2 = moves[j];
				newSon->nbofSons = 0; //initialize the value
				(dad->sons[dad->nbofSons])=newSon; //add the new son as last son of dad
				dad->nbofSons++; //incremente the son number accordingly
				buildTree(g, depth-1, newSon); //create the subtree of the new son

			}
		}
	} else { //depth is 0 -> dad is forced as a leave
		dad->value = evaluate(g, (dad->c1), (dad->c2)); //needs to be accurate
		dad->nbofSons = 0;
		dad->sons = NULL; //be carefull
	}
}

void freeTree(Tree *t) {
	if (t->nbofSons==0) {
		free(t);
	} else {
		int i;
		for (i=0; i<(t->nbofSons); i++) {
			freeTree(t->sons[i]);
		}
		free(t);
	}
}



Coordinates* friendlyToken(Game* g) {
	int tokenNb = g->currentPlayer==1 ? g->countPlayer1 : g->countPlayer2; //nb of tokens of the currentPlayer
	int i;
	int j;
	Coordinates c;
	Coordinates* tab = (Coordinates*)malloc(sizeof(Coordinates)*tokenNb);
	int k = 0; //cursor of tab
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			if (g->map[i][j]==g->currentPlayer) {
				c.x = i ; c.y = j;
				tab[k] = c;
				k++;
				c.x = -1 ; c.y = -1;
			}
		}
	}
	return tab;
}

double evaluate(Game *g, Coordinates c1, Coordinates c2) {
	double res;
	res = 0;
	if (checkMove(g, c1, c2)!=1) {return res;} //means incorrect move
	//else
	//do the play
	movePiece(g, c1, c2);
	//attribuate value
	//victory cases
	if (checkVictory(g, c2)==(g->currentPlayer)) //currentPlayer is AI player
	{ res = res + 1000; }
	else if (checkVictory(g, c2)==(3-(g->currentPlayer))) //means ennemy wins
	{ res = res - 1000; }
	else if (checkVictory(g, c2)==3) //means both loosed
	{
	int friendTokenNb = g->currentPlayer==1 ? g->countPlayer1 : g->countPlayer2 ; //nb of tokens of the currentPlayer
	int ennemyTokenNb = g->currentPlayer==1 ? g->countPlayer2 : g->countPlayer1 ; //nb of tokens of the currentPlayer
	res = res - (100 * (friendTokenNb - ennemyTokenNb)); //ones wants draw if ones has less token
	}
	//caugth cases
	Coordinates* tab = checkCatch(g, c2); //the tab of to-be-caught-by-this-play token

	res = res + (tab[0].x-1) * 100; //-1 because of the false first coordonates

	//be close to ennemy
	res = res + (3 * nbofEnnemy(g, c2));
	//but also close to friends
	//res = res + 2 * nbofFriends(g, c2);

	//if protect friends then good
	//I don't fucking know how to implement this


	//reverse the play
	movePiece(g, c2, c1); //a ashami shogi play can always be reversed
	//return value

	return res;

}

void initNode(Tree* t) {
	Coordinates c;
	c.x = -1;
	c.y = -1;
	t->value=0;
	t->c1=c;
	t->c2=c;
	t->nbofSons=0;
	t->sons= (Tree**) malloc(sizeof(Tree*)*8*8);//should handle every possible move
	}

int nbofFriends(Game *g, Coordinates c) {
	int n = 0;
	int i;
	int j;
	for (i=-1; i<=1; i++){
		for (j=-1; j<=1 ;j++) {
			if (0<=c.x+i && c.x+i<=8 && 0<=c.y+j && c.y+j<=8) { //in the board
				if (g->map[c.x+i][c.y+j]==g->map[c.x][c.y]) {
				n++;
				}
			}
		}
	}
	return n-1; //because this stupid machine is counting himself
}

int nbofEnnemy(Game *g, Coordinates c) {
	int n = 0;
	int i;
	int j;
	for (i=-1; i<=1; i++){
		for (j=-1; j<=1 ;j++) {
			//printf(" %d ; %d \n",c.x+i,c.y+j);
			if (0<=c.x+i && c.x+i<=8 && 0<=c.y+j && c.y+j<=8) { //in the board
				if (g->map[c.x+i][c.y+j]==(3-(g->map[c.x][c.y]))) {
					n++;
				}
			}
		}
	}
	//printf(" %d :%d Ennemy  %d \n",c.x,c.y, n);
	return n;
}
