#include "./headers/IA.h"

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
					return best; //end of the research
				}
			}
		}
	}
	return best; //continuing the recursive search
	}
}

/* to call it
	double ninf=-INFINITY;
        double pinf=INFINITY;
        depth is the depth we actually wants to explore
        root is the begining of the exploration tree;
	bestmove = alphabeta(root, depth, ninf, pinf);
*/

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
				Tree *son = malloc(sizeof(Tree));
				son->value = 0 ; //is not used by alpha beta ?
				son->c1 = c1;
				son->c2 = moves[j];
				son->nbofSons = 0; //initialize the value
				dad->nbofSons++;
				dad->sons[i+j]=son; //add son as a son of dad
				buildTree(g, depth-1, son); //create the subtree of son
				
			}
		}
	} else { //depth is 0 -> dad is forced as a leave
		dad->value = evaluate(dad->c1, dad->c2); //needs to be accurate
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
			}
		}
	}
	return tab;
}

double evaluate(Coordinates c1, Coordinates c2) {
	double res = (double) 1;
	return res;

}

