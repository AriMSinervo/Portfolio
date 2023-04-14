#include "universe.h"

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "tsn:i:o:h"
#define DELAY   50000

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t genarg = 100, rowarg = 0, colarg = 0, lnum = 0;
    bool stog
        = false,
        ttog
        = false; //init bools to control whether ncurses is silenced and if our universe is toroidal
    FILE *infile = stdin; //init our default filenames
    FILE *outfile = stdout; //if no input our program will just print to the terminal
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        //check for each case input
        case 't': //toggles toroidal
            ttog = true;
            break;
        case 's': //toggles ncurses
            stog = true;
            break;
        case 'n': //inputs generations
            genarg = atoi(optarg);
            break;
        case 'i': //inputs infile name, opens it to read from
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                printf("Error opening %s. \n", optarg);
                return 0;
            }
            break;
        case 'o': //inputs outfile name, creates one to write to
            outfile = fopen(optarg, "w");
            break;
        case 'h': //help case, ends program
            printf("SYNOPSIS\n    Conway's Game of Life\n\nUSAGE\n    ./life "
                   "tsn:i:o:h\n\nOPTIONS\n    -t             Create your universe as a toroidal\n  "
                   "  -s             Silent - do not use animate the evolution\n    -n {number}    "
                   "Number of generations [default: 100]\n    -i {file}      Input file [default: "
                   "stdin]\n    -o {file}      Output file [default: stdout]\n");
            return 0;
        }
    }

    fscanf(infile, "%d %d", &rowarg,
        &colarg); //read the first line of infile and put the values in rowarg colarg
    struct Universe *a = uv_create(rowarg, colarg, ttog); //create universe 1
    struct Universe *b = uv_create(rowarg, colarg, ttog); // create universe 2
    struct Universe *swap = NULL; //create an empty universe to swap the two later

    if (uv_populate(a, infile) == false) { //populate a and make sure it was properly populated
        printf("Malformed input.\n");
        return 0;
    }

    if (stog == false) { //begin ncurses
        initscr();
        curs_set(FALSE);
    }

    for (uint32_t i = 0; i < genarg; i++) { //loop through generations
        if (stog == false) {
            clear();
        }
        for (uint32_t r = 0; r < uv_rows(a); r++) { //loop through rows
            for (uint32_t c = 0; c < uv_cols(a); c++) { //loop through columns
                if (stog == false) { //print grid to ncurses screen.
                    if (uv_get_cell(a, r, c) == true) {
                        mvprintw(r, c, "o");
                    }
                    if (uv_get_cell(a, r, c) == false) {
                        mvprintw(r, c, " ");
                    }
                }

                lnum = uv_census(a, r, c); //gathers the amount of adjacent cells to grid[r][c]
                //our rules for determining the next generation are as follows:
                if (lnum > 3 || lnum < 2) {
                    uv_dead_cell(
                        b, r, c); //if a cell has more than 3 or less than 2 neighbors it dies
                }
                if (lnum == 3) { //update universe b according to a
                    uv_live_cell(
                        b, r, c); //if a cell has exactly 3 neighbors it becomes/stays alive
                }
                if (lnum == 2 && uv_get_cell(a, r, c) == true) {
                    uv_live_cell(b, r, c); //if a live cell has 2 neighbors it stays alive
                }
                if (lnum == 2 && uv_get_cell(a, r, c) == false) {
                    uv_dead_cell(b, r, c); //if a dead cell has 2 neighbors it stays dead
                }
            }
        }
        swap = a; //swap the universes
        a = b;
        b = swap;

        if (stog == false) { //refresh ncurses screen.
            refresh();
            usleep(DELAY);
        }
    }
    if (stog == false) {
        endwin(); //end screen
    }

    uv_print(a, outfile); //prints universe a
    //free up all alocated memory
    uv_delete(a);
    uv_delete(b);
    //close opened files
    fclose(infile);
    fclose(outfile);
    return 0;
}
