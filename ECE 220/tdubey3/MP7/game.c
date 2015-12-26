/*
 * Name: Tanishq Dubey
 * NetId: tdubey3
 *
 * INTRO PARAGRAPH
 *
 *
 * This program is the game 2048. It creates a board and begins generating
 * random tiles after you shift all the tiles to one side or the other.
 * When two tiles of the same value are shifted together, they merge.
 *
 * The goal of the game is to get 2048 or higher by combining tiles of the same value.
 * This creates various powers of 2 that can be further combined to make higher value tiles
 * The player wins when they get a tile that is valued at 2048
 *
 *
 *
 *
 *
 */

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //inits game
    game *g = malloc(sizeof(g));	
    g->rows = rows;
    g->cols = cols;
    g->score = 0;  

    g->cells = malloc(sizeof(cell)*rows*cols);
    for(int i = 0; i < rows*cols; i++){
            g->cells[i] = -1;
    }

    return g;
}



void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. */
{
        free(cur_game->cells);
	free(cur_game);
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{   
	//find cell, else return null 
       if(row >=0 && row< cur_game->rows && col >=0 && col< cur_game->cols){  
                cell * ret = cur_game->cells;
                return &ret[row*cur_game->cols + col];
        }
        return NULL;
}

int move_w(game * cur_game)
        /*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
          one above it, the tiles are merged by adding their values together. When
          tiles merge, increase the score by the value of the new tile. A tile can 
          not merge twice in one turn. If sliding the tiles up does not cause any 
          cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
          */
{
        int rows = cur_game->rows;
        int cols = cur_game->cols;
        int numShifts = 0, k = 1;
        bool done = false;
        int found = 0;
	//slide up
        for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                        cell * curr = get_cell(cur_game, i, j);
                        done = false;
                 	//if there is a value
		        if(*curr!=-1){
                                found++;
                                k=1;
				//slide everything in the array 
                                while(!done){
                                        
                                        if(i == 0 || i-k < 0){
                                                done = true;
                                                break;
                                        }
                                        int index1 = (i-k)*cols+j;
                                        int index2 = (i-k+1)*cols+j;
      					//if can't combine			 
					if(index1 < rows*cols && index2 < rows*cols && index1 >=0 && index2>=0){
					if(cur_game->cells[index1] != -1 && cur_game->cells[index1] != cur_game->cells[index2]){
						break;
					}
					//if can move
	                                if(*get_cell(cur_game,i-k,j) == -1){
                                                cur_game->cells[index1] = cur_game->cells[index2];
                                                cur_game->cells[index2] = -1;
                                                numShifts++;
                                        }
					//if can combine
                                        if(cur_game->cells[index1] != -1 && cur_game->cells[index1] == cur_game->cells[index2]){
                                                cur_game->cells[index1] += cur_game->cells[index1];
                                                cur_game->score += cur_game->cells[index1];
                                                cur_game->cells[index2]= -1;
                                                numShifts++;
						done = true;
                                                break;
                                        }
                                       } 
                                        k++;
                                }
                        }
                }
        }
	//if nothing changed, return 0
        if(numShifts == 0) return 0;
        return 1;
};

int move_s(game * cur_game) //slide down
{
	//slide down
        int rows = cur_game->rows;
        int cols = cur_game->cols;
        int numShifts = 0, k = 1;
        bool done = false;
        int found = 0;

        for(int i = rows-1; i >= 0; i--){
                for(int j = cols - 1; j >= 0; j--){
                        cell * curr = get_cell(cur_game, i, j);
                        done = false;
 			//if has value
                        if(*curr!=-1){
                                found++;
                                k=1;
                                while(!done){
                                        if(i == rows || i+k > rows){
                                                done = true;
                                                break;
                                        }

                                        int index1 = (i+k)*cols+j;
                                        int index2 = (i+k-1)*cols+j;					
					if(index1 < rows*cols && index2 < rows*cols && index1 >=0 && index2 >=0){
					//if can't combine					
					if(cur_game->cells[index1] != -1 && cur_game->cells[index1] != cur_game->cells[index2]){
						break;
					}
					//if can move
			                if(cur_game->cells[index1] == -1){
                                                cur_game->cells[index1] = cur_game->cells[index2];
                                                cur_game->cells[index2] = -1;
                                                numShifts++;
                                        }
					

					//if can combine
					if(cur_game->cells[index1] != -1 && cur_game->cells[index1] == cur_game->cells[index2]){
                                               	 
                        			printf("%d vs %d\n", cur_game->cells[index1], cur_game->cells[index2]);
						cur_game->cells[index1] += cur_game->cells[index1];               
                                                cur_game->score += cur_game->cells[index1];
                                                cur_game->cells[index2]= -1;
                                                numShifts++;
						done = true;
						printf("done: %d\n",done);
						break; 
                                        }
					}						
					k++;
                                }
                        }
                }
        }
        //same as before
	if(numShifts == 0) return 0;
	return 1;
};

int move_a(game * cur_game) //slide left
{
	
        int rows = cur_game->rows;
        int cols = cur_game->cols;
        int numShifts = 0, k = 1;
        bool done = false;
        int found = 0;

        for(int j = 0; j < cols; j++){
                for(int i = 0; i < rows; i++){
                        cell * curr = get_cell(cur_game, i, j);
                        done = false;
			//if has val
                        if(*curr!=-1){
                                found++;
                                k=1;
                                while(!done){
                                        if(j == 0 || j-k < 0){
                                                done = true;
                                                break;
                                        }
                                        int index1 = i*cols+j-k;
                                        int index2 = i*cols+j-k+1;
 
					if(index1 < rows*cols && index2 < rows*cols && index1 >=0 && index2>=0){
					//if can't combine	
					if(cur_game->cells[index1] != -1 && cur_game->cells[index1] != cur_game->cells[index2]){
						break;
					}
					//if can move
                                        if(*get_cell(cur_game,i,j-k) == -1){
                                                cur_game->cells[index1] = cur_game->cells[index2];
                                                cur_game->cells[index2] = -1;
                                                numShifts++;
                                        }
					//if can combine
                                        if(cur_game->cells[index1] != -1 && cur_game->cells[index1] == cur_game->cells[index2]){
                                                cur_game->cells[index1] += cur_game->cells[index1];
                                                cur_game->score += cur_game->cells[index1];
                                                cur_game->cells[index2]= -1;
                                                numShifts++;
                                            	done = true;
						break;
                                        }
}
                                        k++;
                                }
                        }
                }
        }
	//same as before
        if(numShifts == 0) return 0;
        return 1;
};

int move_d(game * cur_game){ //slide to the right
        int rows = cur_game->rows;
        int cols = cur_game->cols;
        int numShifts = 0, k = 1;
        bool done = false;
        int found = 0;

        for(int j = cols-1; j >= 0; j--){
                for(int i = rows-1; i >= 0; i--){
                        cell * curr = get_cell(cur_game, i, j);
                        done = false;
                        //if has val
			if(*curr!=-1){
                                found++;
                                k=1;
                                while(!done){
                                        int index1 = i*cols+j+k;
                                        int index2 = i*cols+j+k-1; 
	                                if( j == cols||j+k >= cols){
                                                done = true;
                                                break;
                                        }

					if(index1 < rows*cols && index2 < rows*cols && index1 >=0 && index2>=0){
                                    	//if can't combine   	                                         
					if(cur_game->cells[index1] != -1 && cur_game->cells[index1] != cur_game->cells[index2]){
						break;
					}
					//if can move
                                        if(cur_game->cells[index1] == -1){
                                                cur_game->cells[index1] = cur_game->cells[index2];
                                                cur_game->cells[index2] = -1;
                                                numShifts++;
                                        }
					//if can combine
                                        if(cur_game->cells[index1] != -1 && cur_game->cells[index1] == cur_game->cells[index2]){
                                                cur_game->cells[index1] += cur_game->cells[index1];              
                                                cur_game->score += cur_game->cells[index1];
                                                cur_game->cells[index2]= -1;
                                                numShifts++;
						done = true;
                                                break;
                                        }
}
                                        k++;
                                }
                        }
                }
        }
        //same as before
	if(numShifts == 0) return 0;
        return 1;
};

int legal_move_check(game * cur_game)
        /*! Given the current game check if there are any legal moves on the board. There are
          no legal moves if sliding in any direction will not cause the game to change.
          Return 1 if there are possible legal moves, 0 if there are none.
          */
{       
	int rows = cur_game->rows;
	int cols = cur_game->cols;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			int index = i*cols + j;
			int top = (i-1)*cols + j;
			int bot = (i+1)*cols + j;
			int left = i*cols + j - 1;
			int right = i*cols + j + 1;
			
			if(cur_game->cells[index] == -1) return 1;
			if(top >=0)
				if(cur_game->cells[index] == cur_game->cells[top]) return 1;		
			if(bot < rows*cols)
				if(cur_game->cells[index] == cur_game->cells[bot]) return 1;		
			if(index % cols != 0 )
				if(cur_game->cells[index] == cur_game->cells[left]) return 1;		

			if(index % (cols -1) != 0)
				if(cur_game->cells[index] == cur_game->cells[right]) return 1;		
		}
	}	
        /*for(int i = 0; i < cur_game->rows*cur_game->cols; i++){
                if(cur_game->cells[i] == -1){
                	return 1;
		}
        }*/

        return 0;
}


void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
        /*! Given a game structure that is passed by reference, change the
          game structure to have the given number of rows and columns. Initialize
          the score and all elements in the cells to zero. Make sure that any 
          memory previously allocated is not lost in this function.	
          */
{
        cell * newBoard = malloc(sizeof(cell)*new_rows*new_cols);
        for(int i = 0; i < new_rows*new_cols; i++){
                newBoard[i] = -1;
        }
        (*_cur_game_ptr)->score = 0;
        (*_cur_game_ptr)->rows = new_rows;
        (*_cur_game_ptr)->cols = new_cols;
        free((*_cur_game_ptr)->cells);
        (*_cur_game_ptr)->cells = newBoard;
        return;

}

/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
        /*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
        */
{

        cell * cell_ptr;
        cell_ptr = 	cur_game->cells;

        if (cell_ptr == NULL){ 	
                printf("Bad Cell Pointer.\n");
                exit(0);
        }


        //check for an empty cell
        int emptycheck = 0;
        int i;

        for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
                if ((*cell_ptr) == -1){
                        emptycheck = 1;
                        break;
                }		
                cell_ptr += 1;
        }
        if (emptycheck == 0){
                printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
                exit(0);
        }

        int ind,row,col;
        int num;
        do{
                ind = rand()%((cur_game->rows)*(cur_game->cols));
                col = ind%(cur_game->cols);
                row = ind/cur_game->cols;
        } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
        num = rand()%20;
        if(num <= 1){
                *get_cell(cur_game, row, col) = 4; // 1/10th chance
        }
        else{
                *get_cell(cur_game, row, col) = 2;// 9/10th chance
        }
}

int print_game(game * cur_game) 
{
        cell * cell_ptr;
        cell_ptr = 	cur_game->cells;

        int rows = cur_game->rows;
        int cols = cur_game->cols;
        int i,j;

        printf("\n\n\nscore:%d\n",cur_game->score); 


        printf("\u2554"); // topleft box char
        for(i = 0; i < cols*5;i++)
                printf("\u2550"); // top box char
        printf("\u2557\n"); //top right char 


        for(i = 0; i < rows; i++){
                printf("\u2551"); // side box char
                for(j = 0; j < cols; j++){
                        if ((*cell_ptr) == -1 ) { //print asterisks
                                printf(" **  "); 
                        }
                        else {
                                switch( *cell_ptr ){ //print colored text
                                        case 2:
                                                printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 4:
                                                printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 8:
                                                printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 16:
                                                printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 32:
                                                printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 64:
                                                printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 128:
                                                printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 256:
                                                printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 512:
                                                printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 1024:
                                                printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 2048:
                                                printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 4096:
                                                printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        case 8192:
                                                printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                                                break;
                                        default:
                                                printf("  X  ");

                                }

                        }
                        cell_ptr++;
                }
                printf("\u2551\n"); //print right wall and newline
        }

        printf("\u255A"); // print bottom left char
        for(i = 0; i < cols*5;i++)
                printf("\u2550"); // bottom char
        printf("\u255D\n"); //bottom right char

        return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
        int rows,cols;
        char buf[200];
        char garbage[2];
        int move_success = 0;

        switch ( input_char ) {
                case 'w':
                        move_success = move_w(cur_game);
                        break;
                case 'a':
                        move_success = move_a(cur_game);
                        break;
                case 's':
                        move_success = move_s(cur_game);
                        break;
                case 'd':
                        move_success = move_d(cur_game);
                        break;
                case 'q':
                        destroy_game(cur_game);
                        printf("\nQuitting..\n");
                        return 0;
                        break;
                case 'n':
                        //get row and col input for new game
dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
            while (NULL == fgets(buf,200,stdin)) {
                    printf("\nProgram Terminated.\n");
                    return 0;
            }

            if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
                            rows < 0 || cols < 0){
                    printf("Invalid dimensions.\n");
                    goto dim_prompt;
            } 

            remake_game(&cur_game,rows,cols);

            move_success = 1;

                default: //any other input
            printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
        }




        if(move_success == 1){ //if movement happened, insert new tile and print the game.
                rand_new_tile(cur_game); 
                print_game(cur_game);
        } 

        if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
                printf("Game Over!\n");
                return 0;
        }
        return 1;
}
