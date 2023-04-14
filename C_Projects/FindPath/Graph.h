//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#pragma once

#include "List.h"
#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

// Defs -----------------------------------------------------------------------

#define INF -1
#define NIL 0

// structs --------------------------------------------------------------------

typedef struct GraphObj* Graph; //public graph type

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n); //creates and returns and empty graph of order n
void freeGraph(Graph* pG); //frees all heap mem aloc'd to a graph and sets pG to NULL
 
// Access functions -----------------------------------------------------------
int getOrder(Graph G); //returns number of vertices in G
int getSize(Graph G); //returns number of edges in G
int getSource(Graph G); //returns most recent source vertex for BFS
int getParent(Graph G, int u); //returns the parent of vertex i in G
int getDist(Graph G, int u); //returns the distance of vertex i to source vertex
void getPath(List L, Graph G, int u); //returns list of vertex along the shortest path from u to source

// Manipulation procedures ----------------------------------------------------
void makeNull(Graph G); //removes all edges present in the graph
void addEdge(Graph G, int u, int v); //adds an edge between u and v, the edges are added to the adj list in sorted order
void addArc(Graph G, int u, int v); //adds a directed edge from u to v, the edges are added to the adj list in sorted order
void BFS(Graph G, int s); //performs a breadth first search on G starting from vertex s

// Other operations -----------------------------------------------------------
void printGraph(FILE* out, Graph G); //prints adjacency list representation of g

