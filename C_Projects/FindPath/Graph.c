//-------------------------------------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-------------------------------------------------------------------------------------------------------

#include "Graph.h"

// structs ----------------------------------------------------------------------------------------------

//private graph object
typedef struct GraphObj {
	int order, size, source;
	List *neighbor_arr;
	char **colour_arr;
	int *parent_arr;
	int *distance_arr;
	
} GraphObj;

// Constructors-Destructors -----------------------------------------------------------------------------

Graph newGraph(int n) { //creates and returns a new, empty, graph of order n
	int i;
	Graph g = malloc(sizeof(GraphObj));
	assert(g != NULL);
	g->source = NIL;
	g->size = 0;
	g->neighbor_arr = (List*) calloc(n+1, sizeof(List));
	for(i = 1; i <= n; i++) {g->neighbor_arr[i] = newList();}
	g->colour_arr = (char**) calloc(n+1, sizeof(char*));
	g->parent_arr = (int*) calloc(n+1, sizeof(int));
	for(i = 1; i <= n; i++) {g->parent_arr[i] = NIL;}
	g->distance_arr = (int*) calloc(n+1, sizeof(int));
	for(i = 1; i <= n; i++) {g->distance_arr[i] = INF;}
	g->order = n;
	g->size = 0;
	g->source = NIL;
	return g;
}
void freeGraph(Graph* pG) { //frees mem aloc'd to Graph and elements and sets it/them to NULL
	if(pG != NULL && *pG != NULL){
		free((*pG)->colour_arr);
		(*pG)->colour_arr = NULL;
		free((*pG)->parent_arr);
		(*pG)->parent_arr = NULL;
		free((*pG)->distance_arr);
		(*pG)->distance_arr = NULL;
		for(int i = 1; i <= getOrder(*pG); i++) {freeList(&(((*pG)->neighbor_arr[i])));}
		free((*pG)->neighbor_arr);
		(*pG)->neighbor_arr = NULL;
		free(*pG);
		*pG = NULL;
	}
	return; 
}

// Access functions -------------------------------------------------------------------------------------

int getOrder(Graph G) { //returns number of vertices in G
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	return G->order;
}

int getSize(Graph G) { //returns number of edges in G
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	return G->size;
}

int getSource(Graph G) { //returns source vertex used in G
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	return G->source;
}

int getParent(Graph G, int u) { //returns parent of vertex u
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	return G->parent_arr[u];
}

int getDist(Graph G, int u) { //returns distance from u to last used source vertex
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	return G->distance_arr[u];
}

void getPath(List L, Graph G, int u) { //returns list of path els from u to last used source vertex
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	if(u >= 1 && u <= getOrder(G)) {
		if(getDist(G, u) == INF) {clear(L); append(L, NIL); return;}
		if(getSource(G) != NIL && getDist(G, u) != INF) {
			if(u == getSource(G)) {append(L, u); return;}
			prepend(L, u);
			int p = getParent(G, u);
			while(p != getSource(G)) {
				prepend(L, p);
				p = getParent(G, p);
			}
			prepend(L, getSource(G));
		}
	}
	return;
}

// Manipulation procedures ------------------------------------------------------------------------------

void makeNull(Graph G) { //removes all edges from the graph
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	for(int i = 0; i < getOrder(G); i++) {
		clear(G->neighbor_arr[i]); 
		G->neighbor_arr[i] = NULL;
		G->size = 0;
	}
	return;
}

void addEdge(Graph G, int u, int v) { //adds an edge between u and v in the graph
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	if(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)) {
		for(int i = 1; i <= getOrder(G); i++) {
			if(length(G->neighbor_arr[v]) == 0) {
				append(G->neighbor_arr[v], u);
				break;		
			} 
			moveFront(G->neighbor_arr[v]);
			while(index(G->neighbor_arr[v]) < length(G->neighbor_arr[v])) {
				if(get(G->neighbor_arr[v]) == u) {break;}
				if(u < get(G->neighbor_arr[v])) {insertBefore(G->neighbor_arr[v], u); break;}
				moveNext(G->neighbor_arr[v]);
				if(index(G->neighbor_arr[v]) == - 1) {append(G->neighbor_arr[v], u); break;}
			}
		}
		for(int i = 1; i <= getOrder(G); i++) {
			if(length(G->neighbor_arr[u]) == 0) {
				append(G->neighbor_arr[u], v);
				break;
			}
			moveFront(G->neighbor_arr[u]);
			while(index(G->neighbor_arr[u]) < length(G->neighbor_arr[u])) {
				if(get(G->neighbor_arr[u]) == v) {break;}
				if(v < get(G->neighbor_arr[u])) {insertBefore(G->neighbor_arr[u], v); break;}
				moveNext(G->neighbor_arr[u]);
				if(index(G->neighbor_arr[u]) == - 1) {append(G->neighbor_arr[u], v); break;}
			}
		}
	}
	G->size++;
	return;
}

void addArc(Graph G, int u, int v) { //adds a directed edge from u to v in the graph
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	if(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)) {
		for(int i = 1; i <= getOrder(G); i++) {
			if(length(G->neighbor_arr[u]) == 0) {
				append(G->neighbor_arr[u], v);
				break;
			}
			moveFront(G->neighbor_arr[u]);
			while(index(G->neighbor_arr[u]) < length(G->neighbor_arr[u])) {
				if(get(G->neighbor_arr[u]) == v) {break;}
				if(v < get(G->neighbor_arr[u])) {insertBefore(G->neighbor_arr[u], v); break;}
				moveNext(G->neighbor_arr[u]);
				if(index(G->neighbor_arr[u]) == - 1) {append(G->neighbor_arr[u], v); break;}
			}
		}
	}
	G->size++;
	return;
}

void BFS(Graph G, int s) { //performs a breadth first search on the graph from a source vertex s
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	G->source = s;
	for(int i = 1; i <= getOrder(G); i++) {
		G->colour_arr[i] = "white";
		G->distance_arr[i] = INF;
		G->parent_arr[i] = NIL;
	}
	
	G->colour_arr[s] = "grey";
	G->distance_arr[s] = 0;
	List Q = newList();
	append(Q, s);
	while(length(Q) != 0) {
		int x = front(Q), y;
		deleteFront(Q);
		moveFront(G->neighbor_arr[x]);
		for(int z = 1; z <= length(G->neighbor_arr[x]); z++) {
			y = get(G->neighbor_arr[x]);
			if(strcmp(G->colour_arr[y], "white") == 0) {
				G->colour_arr[y] = "grey";
				G->distance_arr[y] = G->distance_arr[x] + 1;
				G->parent_arr[y] = x;
				append(Q, y);
			}
			moveNext(G->neighbor_arr[x]);
		}
		G->colour_arr[x] = "black";
	}
	freeList(&Q);
	Q = NULL;
	return;
}

// Other Functions --------------------------------------------------------------------------------------

void printGraph(FILE* out, Graph G) { //prints the adjacency rep of the graph to an outfile 
	if(G == NULL){
      		fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
   	}
	for(int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->neighbor_arr[i]);
		fprintf(out, "\n");
	}
	return;
}

