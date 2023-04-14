# Life

This program is a recreation of John Horton Conway's game of life. Unlike Conway's original version this version is finite, with the scale of our game feild being deteremined by the first two values in an infile(which is required for our program to run). The program uses the files universe.c/.h to define a struct universe which is used by the file life.c to "play" the game, iterating through generations and determining live/dead cells based on a set of rules laid out by Conway's game. life.c also has the ability to print to an output file it's results. 

## directory

-universe.h: A headerfile which specifies the interface to universe.c.\
-universe.c: The file that defines the many functions and parameters for our universe.\
-life.c: The file that contains main() runs our game and calls universe.\
-Makefile: Creates an executable file of life.c and objects of all other files.\
-README: Standard README formatted using markdown syntax.\
-DESIGN.pdf: Design document specifying use, assignment instructions, and the psuedo later used to create our final program.\
-WRITEUP.pdf: Documentation of results from running sorting, along with an analysis of said results. 

## Installation

This executable does not require outside programs to operate

## Usage

To build the program simply type 'make' into the command line

To format files simply type 'make format' into the command line

Command line options for sorting are as follows:
-t: Specifies that the game should be played on a toriodal universe
-s: Silences ncurses, removes ui element
-n <generations>:Specifies the number of generations the universe goes through, default is 100.
-i <input>: Specifies input file to be read, default is "stdin"
-o <output>: Specifies output file to be written to, default is "stdout"
-h: prints out programs usage

Example:
```bash
./life -t -n 10 -i lists/101.txt -o data.txt
```

To clean the directory simply type 'make clean' into the command line

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.


