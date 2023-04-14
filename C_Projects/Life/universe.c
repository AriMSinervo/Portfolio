#include "universe.h"

#include <stdlib.h>

struct Universe { //defines the values for our universe struct
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols,
    bool toroidal) { //creates a universe and assigns values and also memory to it
    struct Universe *uni = malloc(sizeof(*uni)); //assign memory to uni
    uni->toroidal = toroidal;
    uni->rows = rows;
    uni->cols = cols;
    bool **grid = (bool **) calloc(rows, sizeof(bool *)); //assigns memory to our grid
    for (uint32_t r = 0; r < rows; r += 1) {
        grid[r] = (bool *) calloc(cols, sizeof(bool)); //assigns memory to our rows
    }
    uni->grid = grid; //updates uni's grid with our newly generated one
    return uni;
}

void uv_delete(Universe *u) { //unalocates memory
    for (uint32_t r = 0; r < u->rows; r++) {
        free(u->grid[r]); //frees row memory
        u->grid[r] = NULL;
    }
    free(u->grid); //frees grid memory
    u->grid = NULL;
    free(u); //frees uni's memory
    u = NULL;
    return;
}

uint32_t uv_rows(Universe *u) { //returns row count for our universe
    return u->rows;
}

uint32_t uv_cols(Universe *u) { //returns col count for our universe
    return u->cols;
}

void uv_live_cell(
    Universe *u, uint32_t r, uint32_t c) { //assigns a live cell to specific grid location
    u->grid[r][c] = true;
}

void uv_dead_cell(
    Universe *u, uint32_t r, uint32_t c) { //assigns a dead cell to specific grid location
    u->grid[r][c] = false;
}

bool uv_get_cell(Universe *u, uint32_t r,
    uint32_t c) { //tells us if a specific grid location (cell) is alive or dead
    //checks for if our grid values are actually in our desired range
    if (r > (u->rows - 1)) {
        return false;
    }
    if (c > (u->cols - 1)) {
        return false;
    }
    if (r < 0) {
        return false;
    }
    if (c < 0) {
        return false;
    } else {
        return u->grid[r][c]; //returns grid location (cell) value
    }
}

bool uv_populate(Universe *u,
    FILE *infile) { //assigns all cells in grid to be either alive or dead from an infile's data
    uint32_t store_1 = 0;
    uint32_t store_2 = 0;
    while (fscanf(infile, "%d %d", &store_1, &store_2)
           != EOF) { //if a cell appears in an infile, make it alive
        if (store_1
            > u->rows) { //checks to make sure the cell specified in infile is actually on the grid
            return false; //returns false telling the program that uv_populate failed to populate u.
        }
        if (store_2 > u->cols) {
            return false;
        }
        if (store_1 < 0) {
            return false;
        }
        if (store_2 < 0) {
            return false;
        }
        u->grid[store_1][store_2] = true; //assigns life to a cell
    }
    return true; //returns false telling the program that uv_populate successfully populated u.
}

uint32_t uv_census(
    Universe *u, uint32_t r, uint32_t c) { //returns how many live neighbors a cell has
    uint32_t livecount = 0;
    //check directly adjacent cells
    if (uv_get_cell(u, r, (c - 1)) == true) {
        livecount += 1;
    }
    if (uv_get_cell(u, r, (c + 1)) == true) {
        livecount += 1;
    }
    if (uv_get_cell(u, (r - 1), c) == true) {
        livecount += 1;
    }
    if (uv_get_cell(u, (r + 1), c) == true) {
        livecount += 1;
    }
    //diagonals now
    if (uv_get_cell(u, (r + 1), (c + 1)) == true) {
        livecount += 1;
    }
    if (uv_get_cell(u, (r + 1), (c - 1)) == true) {
        livecount += 1;
    }
    if (uv_get_cell(u, (r - 1), (c + 1)) == true) {
        livecount += 1;
    }
    if (uv_get_cell(u, (r - 1), (c - 1)) == true) {
        livecount += 1;
    }
    if (u->toroidal
        == true) { //if the universe is toroidal we need to check if the cells are on the sides of the grid
        if (r == 0) { //if so we go through a series of checks (checking the other side of the grid)
            if (uv_get_cell(u, (u->rows - 1), c) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, (u->rows - 1), (c + 1)) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, (u->rows - 1), (c - 1)) == true) {
                livecount += 1;
            }
            if (c == 0) { //check case if the cell is in a corner
                if (uv_get_cell(u, (u->rows - 1), (u->cols - 1)) == true) {
                    livecount += 1;
                }
            }
            if (c == (u->cols - 1)) { //check case if the cell is in a corner
                if (uv_get_cell(u, (u->rows - 1), 0) == true) {
                    livecount += 1;
                }
            }
        }
        if (r == (u->rows - 1)) {
            if (uv_get_cell(u, 0, c) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, 0, (c + 1)) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, 0, (c - 1)) == true) {
                livecount += 1;
            }
            if (c == 0) { //check case if the cell is in a corner
                if (uv_get_cell(u, 0, (u->cols - 1)) == true) {
                    livecount += 1;
                }
            }
            if (c == (u->cols - 1)) { //check case if the cell is in a corner
                if (uv_get_cell(u, 0, 0) == true) {
                    livecount += 1;
                }
            }
        }
        if (c == 0) {
            if (uv_get_cell(u, r, (u->cols - 1)) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, (r + 1), (u->cols - 1)) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, (r - 1), (u->cols - 1)) == true) {
                livecount += 1;
            }
            if (r == 0) { //check case if the cell is in a corner
                if (uv_get_cell(u, (u->rows - 1), (u->cols - 1))) {
                    livecount += 1;
                }
            }
            if (r == (u->rows - 1)) { //check case if the cell is in a corner
                if (uv_get_cell(u, 0, (u->cols - 1))) {
                    livecount += 1;
                }
            }
        }
        if (c == (u->cols - 1)) {
            if (uv_get_cell(u, r, 0) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, (r + 1), 0) == true) {
                livecount += 1;
            }
            if (uv_get_cell(u, (r - 1), 0) == true) {
                livecount += 1;
            }
            if (r == 0) { //check case if the cell is in a corner
                if (uv_get_cell(u, (u->rows - 1), 0)) {
                    livecount += 1;
                }
            }
            if (r == (u->rows - 1)) { //check case if the cell is in a corner
                if (uv_get_cell(u, 0, 0) == true) {
                    livecount += 1;
                }
            }
        }
    }
    return livecount;
}

void uv_print(Universe *u, FILE *outfile) { //prints u's grid contents to a specified outfile
    for (uint32_t r = 0; r < uv_rows(u); r++) { //loops through rows
        for (uint32_t c = 0; c < uv_cols(u); c++) { //loops through columns
            if (uv_get_cell(u, r, c) == true) { //if cell is alive print "o"
                fprintf(outfile, "o");
            }
            if (uv_get_cell(u, r, c) == false) { //if cell is dead print "."
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n"); //at the end of a row print newline
    }
}
