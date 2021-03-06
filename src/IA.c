#include "./headers/IA.h"

Coordinates* aiPlay(Game *g) {
	// int difficulty might control depth
	int depth = 1; //warning depth 0 create infinite loop
	Tree* root = (Tree*) malloc(sizeof(Tree));
	if (root == NULL) {exit(0);} // if alloc failed, immediatly quit
    	initNode(root);
	int ninf=-1000000;
	int pinf=1000000;
	Coordinates c1;
	Coordinates c2;
	c1.x=-1;
	c1.y=-1;
	c2.x=-1;
	c2.y=-1;
	printf("building tree for %d...",g->currentPlayer);
	buildTree(g, depth, root, g->currentPlayer);
	printf("done \n");
	//printBoard(g);
	while (checkMove(g, c1, c2, g->currentPlayer) != 1) { //useless by construction but still safer
		//printf("selecting best move ...");
		int bestmove = alphabeta(g, root, depth, ninf, pinf, g->currentPlayer); //find the path through victory

		int n;
		for (n=0; n<(root->nbofSons)-1; n++) {//finding the selected move between the available one
			if (((root->sons[n])->value)==bestmove) {
				c1.x = (((root->sons)[n])->c1.x);
				c1.y = (((root->sons)[n])->c1.y);
				c2.x = (((root->sons)[n])->c2.x);
				c2.y = (((root->sons)[n])->c2.y);
				break; //not usefull to go further
			}
		}
		//printf("done \n");
		//printf("%d : %d -> %d : %d with value %d \n",c1.x,c1.y,c2.x,c2.y,bestmove);
	}
	Coordinates *tab;
	movePiece(g, c1, c2); //the move is safe by construction
	Coordinates *tabCatch;
	tabCatch = checkCatch(g, c2); //the tab of to be caught token
	//printTab(tabCatch,tabCatch[0].x);
	catchPiece(g,tabCatch);
	//here comes the save

	//creating the returned tab for graphical update
	tab = (Coordinates*) malloc(sizeof(Coordinates)*(tabCatch[0].x+2)); //adding 2 for c1 and c2
	if (tab == NULL) {exit(0);} // if alloc failed, immediatly quit
	tab[0].x = tabCatch[0].x+2;
	tab[0].y = 0;
	tab[1] = c1;
	tab[2] = c2;
	int i;
	for (i=1; i<(tabCatch[0].x); i++) {
		tab[i+2]=tabCatch[i];
	}
	free(tabCatch); //malloc in checkCatch
	freeTree(root); //free the rest of the tree
	return tab;
}


int alphabeta(Game *g, Tree *P, int depth, int a, int b, int player) { //a<b
	//printf("param depth %d, a %lf, b %lf \n",depth,a,b);
	if ((depth<=0) || (P->nbofSons<=0)) //means P is a leave or is forced to be one by depth
	{
		//printf("leaf value %lf \n",P->value);
		return P->value; //returning value of leave
	} else if (g->currentPlayer==player) {//ai play (max)
		int max = -1000000;
		int i;
		for (i=0; i<(P->nbofSons); i++) {
			int val;
			//printf("depth %d",depth);
			val = alphabeta(g, P->sons[i], (depth-1), -b, -a, 3-player);
			//printf(" depth %d \n",depth);
			max = (max < val) ? val : max; //max= max(val, max)
			a = (a < val) ? val : a ; //α = max(α, v)
			//printf("max %lf, val %lf, a %lf, b %lf \n",max,val,a,b);
			if (b <= a) {
				break; // β cut-off
			}
		}
		P->value=max; //saving the value
		/*
		for (i=0; i<(16*18); i++) {
			freeTree((P->sons)[i]);
		}
		P->nbofSons=0;
		*/
		return max; //continuing the recursive search
	} else { //opponant play (min)
		int min = 1000000;
		int i;
		for (i=0; i<(P->nbofSons); i++) {
			int val;
			//printf("depth %d",depth);
			val = alphabeta(g, P->sons[i], depth-1,-b,-a, 3-player);
			//printf(" depth %d \n",depth);
			min = (min > val) ? val : min; //min = min(min,val)
			b = (b > val) ? val : b ; //β := min(β, v)
			//printf("min %lf, val %lf, a %lf, b %lf \n",min,val,a,b);
			if (b <= a) {
				break; // α cut-off
			}
		}

		P->value=min; //saving the value
		/*
		for (i=0; i<(16*18); i++) {
			freeTree((P->sons)[i]);
		}
		P->nbofSons=0;
		*/
		return min; //continuing the recursive search
	}
}

void buildTree(Game* g, int depth, Tree *dad, int player) {
	int tokenNb = (player==1) ? g->countPlayer1 : g->countPlayer2; //depict the friendly token nb to player currently playing in simulation
	//printf("depth %d ; tokenNb %d \n",depth, tokenNb);
	if ((depth > 0) && (tokenNb>0)) {
		//printf("if");
		//printf("player %d ",player);
		Coordinates* friendlyTokenTab = friendlyToken(g, player);
		dad->sons = (Tree**) malloc(sizeof(Tree*)*16*friendlyTokenTab[0].x);//should handle every possible move (tab of pointer toward Trees) 16*friendlyTokenTab[0].x possible plays
		if (dad->sons == NULL) {exit(0);} // if alloc failed, immediatly quit
		//printf("plop");
		//printf("tknb %d \n",tokenNb);
		int i;
		//printf("i : %d -> %d",i,friendlyTokenTab[0].x);
		for (i=1; i<friendlyTokenTab[0].x; i++) {
			//printf("plip");
			Coordinates c1;
			c1.x = friendlyTokenTab[i].x;
			c1.y = friendlyTokenTab[i].y;
			//printf("friendlytoken");
			//printf("\n c1 %d :%d \n",c1.x,c1.y);
			Coordinates* moves = showPossible(g, c1, player); //available moves

			int j;
			for (j = 1 ; j<(moves[0].x) ; j++) {
				dad->sons[dad->nbofSons] = (Tree*) malloc(sizeof(Tree));
				if (dad->sons[dad->nbofSons] == NULL) {exit(0);} // if alloc failed, immediatly quit
				initNode(dad->sons[dad->nbofSons]);
				(dad->sons[dad->nbofSons])->value = 0 ; //is overwritten by alpha beta
				(dad->sons[dad->nbofSons])->c1 = c1;
				(dad->sons[dad->nbofSons])->c2 = moves[j];

				//doing the play
				//printf(" c1 %d : %d -> c2 %d : %d \n",c1.x,c1.y,moves[j].x,moves[j].y);
				movePiece(g, c1, moves[j]);
				Coordinates *tabCatch;
				tabCatch = checkCatch(g, moves[j]); //the tab of to be caught token
				//printTab(tabCatch,tabCatch[0].x);
				catchPiece(g,tabCatch);

				(dad->sons[dad->nbofSons])->nbofSons = 0; //initialize the value
				//recursive call
				//printf("--> %d ",depth);
				buildTree(g, depth-1, (dad->sons[dad->nbofSons]), (3-player)); //creates the subtree of the new son
				//printf("<-- %d \n",depth);
				(dad->nbofSons)++; //incremente the son number accordingly

				//reverting the play
				releasePiece(g, tabCatch, 3-player);
				movePiece(g, moves[j], c1);
				free(tabCatch);

			}
			free(moves);
		}
		free(friendlyTokenTab);
	} else { //depth is 0 -> dad is forced as a leave
		dad->value = evaluate(g, player); //needs to be accurate
		dad->nbofSons = 0; //means is a leave
		dad->sons = NULL; //be carefull

		//free(tabCatch);
	}
}

void freeTree(Tree *t) {
	int i;
	for (i=0; i<(t->nbofSons); i++) {
		freeTree((t->sons)[i]);
	}
	free(t->sons);
	free(t);
}


Coordinates* friendlyToken(Game* g, int player) {
	int i;
	int j;
	Coordinates* tab = (Coordinates*) malloc(sizeof(Coordinates)*36);//there are at utter most 18 friendly tokens
	if (tab == NULL) {exit(0);} // if alloc failed, immediatly quit
	int k;
	k = 1; //cursor of tab
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			if (g->map[i][j]==player) {
				tab[k].x = i;
				tab[k].y = j;
				k++;
				//printf("%d",kkk);
			}
		}
	}
	tab[0].x=k;
	return tab;
}

double evaluate(Game *g, int player) {
	double res;
	res = 0;
	//attribuate value

	//having more tokens
	int friendTokenNb = g->currentPlayer==1 ? g->countPlayer1 : g->countPlayer2 ; //nb of tokens of the currentPlayer
	int ennemyTokenNb = g->currentPlayer==1 ? g->countPlayer2 : g->countPlayer1 ; //nb of tokens of the currentPlayer
	res = res + (100 * (friendTokenNb - ennemyTokenNb)); //ones wants to have more token

	//having aligned tokens including victory condition
	res = res + 30 * nbofLigns(g, player);
	res = res - 30 * nbofLigns(g, 3-player);

	//return the value
	return res;
}

int nbofLigns(Game* g, int player) {
	int begin = 0;
	int end = 9;
	if (player==1) { begin = 2; } else { end = 7; }
	int mem = 0; //memory for returning
	int nb;
	int last;
	int i;
	int j;
	for (i=begin ; i<end ; i++) { //for each lign
		nb=0; //checking colomn
		last=1; //boolean last was a friendly token
		for (j=0 ; j<9 ; j++) { //for each colomn
			if (g->map[8-j][i]==player) {
				if (last) {nb++;}
				else { nb=1;}
			} else { //means end of an alignment
				if (nb==3)
				{ mem++; }
				else if (nb==4)
				{ mem = mem + 10; }
				else if (nb>=5)
				{ mem = mem + 100; }
			}
		}
	}
	int decay = (player==1) ? 0 : 2;
	//checking Left diags
	for (i=4; i<15 ;i++) { //diag sum
		nb=0; //checking Left diag
		last=1; //boolean last was a friendly token
		int max = i>8 ? 8 : i;
		int min = i<10 ? 2 : i-8;
		for (j=max; j>=min ;j--) { //case ordonate
			//printf("%d,%d -> %d,%d \n",i,j ,j,i-j);
			if (g->map[8-(j-decay)][i-j]==player) {
				if (last) {nb++;}
				else { nb=1;}
			} else { //means end of an alignment
				if (nb==3)
				{ mem++; }
				else if (nb==4)
				{ mem = mem + 10; }
				else if (nb>=5)
				{ mem = mem + 100; }
			}
		}
	}
	//checking Right diags
	for (i=4; i<15 ;i++) { //diag sum
		nb=0; //checking Right diag
		last=1; //boolean last was a friendly token
		int max = i>8 ? 8 : i;
		int min = i<10 ? 2 : i-8;
		for (j=max; j>=min ;j--) { //case ordonate
			//printf("%d,%d -> %d,%d \n",i,j,j,8-(i-j));
			if (g->map[8-(j-decay)][8-(i-j)]==player) {
				if (last) {nb++;}
				else { nb=1;}
			} else { //means end of an alignment
				if (nb==3)
				{ mem++; }
				else if (nb==4)
				{ mem = mem + 10; }
				else if (nb>=5)
				{ mem = mem + 100; }
			}
		}
	}
	return mem;
}

void initNode(Tree* t) {
	Coordinates c;
	c.x = -1;
	c.y = -1;
	t->value = (double) 0;
	t->c1 = c;
	t->c2 = c;
	t->nbofSons = 0;
	t->sons=NULL;
}
