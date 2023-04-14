# FindPath

This program creates a graph from a specially formatted infile, and returns the graph's adjacency list representation and the shortest path between specified vertices in the graph. Both these fields are printed to an outfile, specified upon running the program.

## directory

-FindPath.c: the file containing main, prints adjacency representation of a graph and the shortest path between specified vertices of the graph to an outfile, draws data from a specially formatted infile.\
-List.c: an implementation of the list ADT used by Lex.c.\
-List.h: a header file which specifies the interface to List.c.\
-Graph.c: an implementation of the Graph ADT used by FindPath.c\
-Graph.h: a header file which specifies the interface to Graph.c.\
-GraphTest.c: a set of tests for out Graph ADT.\
-Makefile: creates an executable file of FindPath.c and objects of all other files, compiles with gcc.\
-README: standard README formatted using markdown syntax.\

## Installation

This executable does not require outside programs to operate

## Usage

To build the program, simply type 'make' into the command line

To build test structure, simply type 'make GraphTest' into the command line

To run program, simply type './FindPath "infile" "outfile"' into the command line

To clean the directory, simply type 'make clean' into the command line

## Infile Formatting 

The infile should be properly formatted for the program to run, the first line should specify the order of the desired graph, then a series of lines specifying the edges connecting vertices, these must be written as "a b" where a is the first vertex and b the second, this section is then closed with the line "0 0". The final section specifies the paths we wish to explore in the graph, once again these are written as "a b" with a being used as the source, and b the destination. Like the last section, this one must close with a "0 0".\

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

