#include "sudoku.h"

/*
 *  SUDOKU SOLVER
 *  PARTNERS: stang17, hq5
 *
 * This program solves a sudoku puzzle using recursive backtracking.
 * The point of sudoku is to fill a 9x9 grid with the numbers 1-9 with the
 * following rules:
 *  - A number can only be in a column once
 *  - A number can only be in a row once
 *  - A number can only be in a 3x3 grid once
 *
 * This program uses one main function, called solve_sudoku that recursively
 * finds the answer to the puzzle.
 *
 * There are helper functions to figure out if a value can be inserted into a
 * specific spot in the sudoku. These are:
 *  - is_val_in_row
 *  - is_val_in_col
 *  - is_val_in_3x3
 *  - is_val
 *
 *  These functions return true or false based on whether the given value can be
 *  inserted into the given location.
 *
 *  The recursive backtracking work by putting in the first valid number into a
 *  free location and then moving to the next free location. If a location
 *  cannot be filled with any values, then the algorithm will "backtrack" to the
 *  previously filled location and changes the value to the next valid term.
 *  This continues until the whole sudoku has been solved.
 */

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
        int i, j;
        for(i=0; i<9; i++) {
                for(j=0; j<9; j++) {
                        printf("%2d", sudoku[i][j]);
                }
                printf("\n");
        }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
        FILE *reader = fopen(fpath, "r");
        assert(reader != NULL);
        int i, j;
        for(i=0; i<9; i++) {
                for(j=0; j<9; j++) {
                        fscanf(reader, "%d", &sudoku[i][j]);
                }
        }
        fclose(reader);
}

//-------------------------------------------------------------------------------------------------
// Start coding your MP here.
// ------------------------------------------------------------------------------------------------

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
        //Check if input is valid
        assert(i>=0 && i<9);

        //declare return variable and counter
        bool exists = false;
        int j;

        //move through the whole row checking if the value exists
        for(j = 0; j < 9; j++) {
                if(val == sudoku[i][j]) {
                        exists = true;
                }
        }

        //return if it exists or not
        return exists;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
        //Check if input is valid
        assert(j>=0 && j<9);

        //declare return variable and counter
        bool exists = false;
        int i;

        //move through the whole column checking if the value exists
        for(i = 0; i < 9; i++) {
                if(val == sudoku[i][j]) {
                        exists = true;
                }
        }

        //return if it exists or not
        return exists;

}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
// Sections are labed as such:
//
//  1 2 3
//  4 5 6
//  7 8 9
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

        assert(i>=0 && i<9);
        assert(j>=0 && j<9);
        bool exists = false;
        int x;
        int y;
        //There are 8 copies of this statement, they all do the same thing, but
        //with different bounds

        //Check where the current coords are located
        if((i < 3 && i >=0) && (j < 3 && j >=0)) {
                //Section 1

                //traverse the whole 3x3 square
                for(x = 0; x < 3; x++){
                        for(y = 0; y < 3; y++){
                                //check if value exists
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 6 && i >=3) && (j < 3 && j >=0)) {
                //Section 2
                for(x = 3; x < 6; x++){
                        for(y = 0; y < 3; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 9 && i >=6) && (j < 3 && j >=0)) {
                //Section 3
                for(x = 6; x < 9; x++){
                        for(y = 0; y < 3; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 3 && i >=0) && (j < 6 && j >=3)) {
                //Section 4
                for(x = 0; x < 3; x++){
                        for(y = 3; y < 6; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 6 && i >=3) && (j < 6 && j >=3)) {
                //Section 5
                for(x = 3; x < 6; x++){
                        for(y = 3; y < 6; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 9 && i >=6) && (j < 6 && j >=3)) {
                //Section 6
                for(x = 6; x < 9; x++){
                        for(y = 3; y < 6; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 3 && i >=0) && (j < 9 && j >=6)) {
                //Section 7
                for(x = 0; x < 3; x++){
                        for(y = 6; y < 9; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 6 && i >=3) && (j < 9 && j >=6)) {
                //Section 8
                for(x = 3; x < 6; x++){
                        for(y = 6; y < 9; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        } else if((i < 9 && i >=6) && (j < 9 && j >=6)) {
                //Section 9
                for(x = 6; x < 9; x++){
                        for(y = 6; y < 9; y++){
                                if(val == sudoku[x][y]) {
                                        exists = true;
                                }
                        }
                }
        }
        return exists;
}

// Function: is_val_in_diag
// Return true if the val alraedy exists in the diagionals of the sudoku square
int is_val_in_diag(const int val, const int i, const int j, const int sudoku[9][9]) {

        //create return variable
        bool exists = false;

        //check asserts
        assert(i>=0 && i<9);
        assert(j>=0 && j<9);

        //initalize more vars
        int x, y;
        x = 0;
        y = 0;

        //check top-left diagional to bottom
        if(i == j){
                for(x = 0; x < 9; x++){
                        if(sudoku[x][y] == val){
                                exists = true;
                        }
                        y++;
                }
        }
        //reset variable and do top-right diagional to bottom
        x = 8;
        if(i + j == 8){
                for(y = 0; y < 9; y++){
                        if(sudoku[x][y] == val) {
                                exists = true;
                        }
                        x--;
                }
        }

        //return if a value was fround
        return exists;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
        //if(i+j == 8 || i == j){
        //        return !is_val_in_row(val, i, sudoku) && !is_val_in_col(val, j, sudoku) && !is_val_in_3x3_zone(val, i, j, sudoku) && is_val_in_diag(val, i, j, sudoku);
        //}
        //
        //One line return to check if a value can be placed in a specific
        //square.
        return !is_val_in_row(val, i, sudoku) && !is_val_in_col(val, j, sudoku) && !is_val_in_3x3_zone(val, i, j, sudoku) && !is_val_in_diag(val, i, j, sudoku);
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

        //declare variables
        int i, j;
        bool spaceLeft = false;
        int xSpace, ySpace;
        int num;

        //double for loop for moving through each square in the sudoku array
        for(i = 0; i < 9; i++) {
                for(j = 0; j < 9; j++) {
                        //Check if current square is 0, if it is then it needs
                        //to be filled
                        if(sudoku[i][j] == 0){
                                //Mark the coordinates and mark that there is
                                //space to be filled
                                spaceLeft = true;
                                xSpace = i;
                                ySpace = j;
                        }
                }
        }
        //If there is no more space left, return true and finish
        if(!spaceLeft){
                return true;
        }

        //Pick a number starting at 1 and going to 9
        for(num = 1; num <= 9; num++) {
                //Check if the value can be placed in the current square
                if(is_val_valid(num, xSpace, ySpace, sudoku)) {
                        //If it can, place it and move to the next branch of
                        //sudoku recursively
                        sudoku[xSpace][ySpace] = num;
                        if(solve_sudoku(sudoku)) {
                                return true;
                        }
                        //If it can't be filled, set to zero
                        sudoku[xSpace][ySpace] = 0;
                }
        }
        //Returned when space can't be filled
        return false;
}
