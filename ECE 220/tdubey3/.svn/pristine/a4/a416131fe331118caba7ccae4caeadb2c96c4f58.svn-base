/*
 *
 * prog4.c - source file originally from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * here to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog4.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the number.
 */

static int32_t turn_number;
static int32_t peg1;
static int32_t peg2;
static int32_t peg3;
static int32_t peg4;


/*
 * set_seed -- uses sscanf to find the random seed value from the string seed_str,
 *	       then initializes the random number generator by calling srand with the seed
 * INPUTS: seed_str -- a string entered by the user for the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (contains something
 *               other than a single integer), or 1 on success
 * SIDE EFFECTS: initializes pseudo-random number generation using srand
 */
int32_t set_seed (const char* seed_str) {
    int seed;
    char post[2];
    int numberScanned = sscanf (seed_str, "%d%1s", &seed, post); //Get number of successful conversions

    if(numberScanned == 1){ //If number of conversions is 1 (one int) set seed
        srand(seed);
        return 1;
    }
    printf("set_seed: invalid seed\n"); //else print error and return
    return 0;
}


/*
 * start_game -- creates the solution combination using the approach
 *               described in the assignment specification (using rand)
 * INPUTS: none
 * OUTPUTS: *one -- the first color value in the code (between 1 and 8)
 *          *two -- the second color value in the code (between 1 and 8)
 *          *three -- the third color value in the code (between 1 and 8)
 *          *four -- the fourth color value in the code (between 1 and 8)
 * RETURN VALUE: 1 on success, or 0 on failure (should never fail, though)
 * SIDE EFFECTS: records the solution code for use by make_guess, set turn_number,
 * save values to peg variables
 */
int32_t start_game (int32_t* one, int32_t* two, int32_t* three, int32_t* four) {
    *one = (rand()%8) + 1; //set random seed by finding modulo of 8 and adding 1 (make it above 0)
    *two = (rand()%8) + 1;
    *three = (rand()%8) + 1;
    *four = (rand()%8) + 1;

    peg1 = *one; //Assign random values to each peg
    peg2 = *two;
    peg3 = *three;
    peg4 = *four;

    turn_number = 1; //set Turn number
    //printf("Solution is %d %d %d %d\n", peg1, peg2, peg3, peg4); //This line
    //is used for debugging and testing if the code ran, it printed the
    //solutions to the game
    return 1;
}

/*
 * make_guess -- calculates the number of perfect and misplaced matches
 *               for a given guess, relative to the solution code recorded
 *               earlier by start_game
 * INPUTS: guess_str -- a string consisting of four numbers for the guess
 * OUTPUTS: the following are only valid if the function returns 1
 *          *one -- the first color value in the guessed code (between 1 and 8)
 *          *two -- the second color value in the guessed code (between 1 and 8)
 *          *three -- the third color value in the guessed code
 *                    (between 1 and 8)
 *          *four -- the fourth color value in the guessed code
 *                    (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (represents exactly four
 *               numbers between 1 and 8), or if it is not
 * SIDE EFFECTS: prints the number of matches found using printf
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int32_t make_guess (const char* guess_str, int32_t* one, int32_t* two, int32_t* three, int32_t* four) {
    char post[2];
    int w = 0,x = 0,y = 0,z = 0; //innitalize all values
    int numsRet = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post); //get number of successful conversions

    if((w > 0 && w < 9) && (x > 0 && x < 9) && (y > 0 && y < 9) && (z > 0 && z < 9) && numsRet == 4) { //validate the inputs
        int pMatch = 0; //perfect match counter
        int nMatch = 0; //missed match counter
        if(w == peg1) { //check if peg is perfect match, and if so, increment perfect counter
            pMatch++;
        }
        if(x == peg2) {
            pMatch++;
        }
        if(y == peg3) {
            pMatch++;
        }
        if(z == peg4) {
            pMatch++;
        }
        if(w == peg1 || w == peg2 || w == peg3 || w == peg4) { //check if the input matches one of the 4 pegs
            nMatch++;
        }
        if(x == peg1 || x == peg2 || x == peg3 || x == peg4) {
            nMatch++;
        }
        if(y == peg1 || y == peg2 || y == peg3 || y == peg4) {
            nMatch++;
        }
        if(z == peg1 || z == peg2 || z == peg3 || z == peg4) {
            nMatch++;
        }
        if (pMatch == 4) { //if there are 4 perfect matches, set values and return
            *one = w;
            *two = x;
            *three = y;
            *four = z;
            return 1;
        }
        printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", turn_number, pMatch, nMatch-pMatch); //print perfect matches and missed matches
        turn_number++; //increment turn count
        return 1;
    } else {
        printf("make_guess: invalid guess\n"); //if not valid, tell it is so
        return 0;
    }
}
