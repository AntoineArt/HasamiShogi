#include "./headers/IA.h"

Coordinates* aiPlay(Game *g) {
	// int difficulty might control depth
	int depth = 3;
	Tree *root = malloc(sizeof(Tree));
	initNode(root);
	buildTree(g, depth, root);
	
	double ninf=-INFINITY;
        double pinf=INFINITY;
	double bestmove = alphabeta(root, depth, ninf, pinf); //find the path through victory
	Coordinates c1;
	Coordinates c2;
	int i;
	for (i=0; i<(root->nbofSons); i++) {//finding the selected move between the available one
		if ((root->sons[i])->value==bestmove) {
			c1 = ((root->sons[i])->c1);
			c2 = ((root->sons[i])->c2);
		}
	}
	freeTree(root);
	
	
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
  	//re use of i 
  	for (i=1; i<(tabCatch[0].x); i++) {
  		tab[i+2]=tabCatch[i];
  	}
  	free(tabCatch); //malloc in checkCatch
  	return tab;
}


double alphabeta(Tree *P, int depth, double a, double b) { //a<b
	if (P->nbofSons==0 || depth==0) //means P is a leave
	{ 
	return P->value; //returning value of leave
	} else {
	double best;
	best = -INFINITY;
	int i;
	for (i=0; i<(P->nbofSons); i++) {
		double val;
		val = - alphabeta(P->sons[i], depth-1,-b,-a);
		if (val > best) {
			best = val;
			if (best < a) {
				a = best;
				if (a >= b) {
					P->value=best; //saving the value
					return best; //end of the research
				}
			}
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
		for (i=1; i<tokenNb; i++) { //always at least 1 token else defeat ? TO be checked
			Coordinates c1 = friendlyTokenTab[i];
			Coordinates* moves = showPossible(g, c1); //available moves
			int j;
			for (j = 1 ; j<(moves[0].x) ; j++) {
				Tree *newSon = malloc(sizeof(Tree));
				initNode(newSon);
				newSon->value = 0 ; //is overwritten by alpha beta
				newSon->c1 = c1;
				newSon->c2 = moves[j];
				newSon->nbofSons = 0; //initialize the value
				(dad->sons[dad->nbofSons])=newSon; //add the new son as last son of dad
				dad->nbofSons++; //incremente the son number accordingly
				buildTree(g, depth-1, newSon); //create the subtree of the newson
				
			}
		}
	} else { //depth is 0 -> dad is forced as a leave
		dad->value = evaluate(g, dad->c1, dad->c2); //needs to be accurate
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
	Coordinates* tab = malloc(sizeof(Coordinates)*tokenNb);
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
	//do the play
	movePiece(g, c1, c2);
	//attribuate value
	double res;
	res = 0;
	//victory cases
	if (checkVictory(g, c2)==(g->currentPlayer)) //currentPlayer is AI player
	{ res = res + 1000; }
	else if (checkVictory(g, c2)==(3-(g->currentPlayer))) //means ennemy wins
	{ res = res - 1000; }
	else if (checkVictory(g, c2)==3) //means both loosed
	{
	int friendTokenNb = g->currentPlayer==1 ? g->countPlayer1 : g->countPlayer2 ; //nb of tokens of the currentPlayer
	int ennemyTokenNb = g->currentPlayer==1 ? g->countPlayer2 : g->countPlayer1 ; //nb of tokens of the currentPlayer
	res = res - 100* (friendTokenNb - ennemyTokenNb); //ones wants draw if ones has less token
	}
	//caugth cases
	Coordinates* tab = checkCatch(g, c2); //the tab of to-be-caught-by-this-play token
	res = res + tab[0].x * 100;
	
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
	t->sons= (Tree**) malloc(sizeof(Tree*)*1000);//might be to small ^^
	}
