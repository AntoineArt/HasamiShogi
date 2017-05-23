#include "../Board.c"
#include <math.h> //needed for infinite value

/*
	handle the whole play of AI
*/
Coordinates* aiPlay(Game *g);

/*
	function for searching the Tree P of possible moves returning the best according to values of P nodes
*/
double alphabeta(Game *g, Tree *P, int depth, double a, double b);

/*
	function that assumes the charge of building the tree of possible moves until depth to save resources
	depth could be used to strengthenth the AI
	allocate memory
*/
void buildTree(Game* g, int depth, Tree *dad);

/*
	function used to free an entire Tree
*/
void freeTree(Tree *t);

/*
	function that gives back at tab of coordinates of the friendly token for currentPlayer, note that there are exactly g->countPlayer* of this token
	Allocate memory
*/
Coordinates* friendlyToken(Game* g);


/*
	function that give a value to a move
*/
double evaluate(Game *g, Coordinates c1, Coordinates c2);

/*
	initialize all fields of a Node
*/
void initNode(Tree* t);

/*
	nb of close friends
*/
int nbofFriends(Game *g, Coordinates c);
/*
	nb of close ennemy
*/
int nbofEnnemy(Game *g, Coordinates c);
