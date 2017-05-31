#include "../SaveSystem.c"
#include <math.h> //needed for infinite value

/*
	handle the whole play of AI
*/
Coordinates* aiPlay(Game *g);

/*
	function for searching the Tree P of possible moves returning the best according to values of P nodes
*/
int alphabeta(Game *g, Tree *P, int depth, int a, int b, int player);

/*
	function that assumes the charge of building the tree of possible moves until depth to save resources
	depth could be used to strengthenth the AI
	allocate memory
*/
void buildTree(Game* g, int depth, Tree *dad, int player);

/*
	function used to free an entire Tree
*/
void freeTree(Tree *t);

/*
	function that gives back at tab of coordinates of the friendly token for player, note that there are exactly g->countPlayer* of this token
	Allocate memory
*/
Coordinates* friendlyToken(Game* g, int player);


/*
	function that give a value to a move
*/
double evaluate(Game *g, int player);
//double evaluate(Game *g, Coordinates c1, Coordinates c2);

/*
	nb of alignement of friendly-to-player tokens of size 3, 4 *10 and 5 *100
*/
int nbofLigns(Game* g, int player);

/*
	initialize all fields of a Node
*/
void initNode(Tree* t);
