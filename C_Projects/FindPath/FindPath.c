//-------------------------------------------------------------------------------------------------------
// FindPath.c
// Program which prints the adj-list rep of a graph and a series of shortest paths in said graph to an outfile
//-------------------------------------------------------------------------------------------------------

#include "Graph.h"

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LEN 300

int main(int argc, char * argv[]) {
	FILE *in, *out;
	char line[MAX_LEN];
	char* tok;
	
	if(argc != 3){ //check if we have three arguments
      		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}
   	
   	in = fopen(argv[1], "r"); // open file for reading  
      	if(in == NULL){
      		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   	}

  	out = fopen(argv[2], "w"); // open file for writing
   	if(out == NULL){
     		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   	}
   	fgets(line, MAX_LEN, in); //get order of graph from first file line
   	Graph g = newGraph(atoi(line)); //create graph with this info
   	
   	while(strcmp(fgets(line, MAX_LEN, in), "0 0\n") != 0) { //loop through graph edges
   		int a, b;
   		tok = strtok(line, " ");
   		a = atoi(tok);
   		tok = strtok(NULL, " ");
   		b = atoi(tok);
   		addEdge(g, a, b);
   	}
   	
   	tok = NULL; 
   	
   	printGraph(out, g); //print out adjacency rep of graph
   	
   	List l = newList(); //make list for path
   	
   	while(strcmp(fgets(line, MAX_LEN, in), "0 0\n") != 0) {
   		int ud, vd, dis;
   		tok = strtok(line, " ");
   		ud = atoi(tok);
   		tok = strtok(NULL, " ");
   		vd = atoi(tok);
   		BFS(g, ud);
   		dis = getDist(g, vd);
   		getPath(l, g, vd);
   		if(dis != -1) {
   			fprintf(out, "\nThe distance from %d to %d is %d\n", ud, vd, dis);
   			fprintf(out, "A shortest %d-%d path is: ", ud, vd);
   			printList(out, l);
   		} else {
   			fprintf(out, "\nThe distance from %d to %d is infinity\n", ud, vd);
   			fprintf(out, "No %d-%d path exists", ud, vd);
   		}
   		fprintf(out, "\n");
   		clear(l);
   	}
   	
   	tok = NULL;
   	
   	//free alloc'd mem
   	freeGraph(&g);
   	freeList(&l);
   	//close files
   	fclose(in);
   	fclose(out);
	return 0;
}
