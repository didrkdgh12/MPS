/*
 * Codebreaker
 * tdubey3
 * partners: hqu5, stang17
 *
 * This program is a simple game where a sequence of 4 integers between 1 and 8
 * (inclusive) is generated and the user must guess the sequence in the correct
 * order. The program reports how many perfect matches and missed (right number,
 * wrong location) matches the user had per turn. The user has 12 turns to guess
 * the value.
 *
 * The program uses methods defined in the 'prog4.h' and implemented in the
 * 'prog4.c' file to run the game. 
 *
 * The sequence of the program is as follows:
 *      - The user enters a seed for the random number generator
 *      - The seed is validated (if valid continue, else ask again)
 *      - A sequence of numbers is generated
 *      - The user must guess a sequence
 *          - If the sequence is invalid, ask again
 *          - Else, count perfect matches, missed matches, and report
 *      - End game when the user guesses the correct sequence or if 12 turns are
 *      used.
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

/*
 * Your code is included as part of this file.
 */
#include "prog4.c"

int main () {
        char buf[200];
        int32_t turn;
        int32_t peg[4];
        int32_t guess[4];

        do {
                printf ("Please enter a seed: ");
                if (NULL == fgets (buf, 200, stdin)) {
                        printf ("\nProgram terminated.\n");
                        return 3;
                }
        } while (!set_seed (buf));

        if (!start_game (&peg[0], &peg[1], &peg[2], &peg[3])) {
                printf ("\nGame start failed.\n");
                return 3;
        }

        for (turn = 1; 12 >= turn; turn++) {
                printf ("Guess %d\n", turn);
                do {
                        printf ("Enter your guess (#1 #2 #3 #4): ");
                        if (NULL == fgets (buf, 200, stdin)) {
                                printf ("\nProgram terminated.\n");
                                return 3;
                        }
                } while (!make_guess (buf, &guess[0], &guess[1], &guess[2], &guess[3]));
                if (guess[0] == peg[0] && guess[1] == peg[1] && guess[2] == peg[2] && guess[3] == peg[3]) {
                        printf ("You guessed correctly in %d guesses.\n", turn);
                        return 0;
                }
        }
        puts ("You failed to guess correctly in 12 guesses.\n");
        printf ("The solution was %d %d %d %d.\n", peg[0], peg[1], peg[2], peg[3]);

        return 0;
}

