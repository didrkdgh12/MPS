#include <stdio.h>
#include "maze.h"

/*
 * findStartEnd -- finds the x and y location of the start and end of the  maze
 *                 if the end or start does not exist should output (-1, -1) as the location
 * INPUTS:         maze -- 2D char array that holds the contents of the maze
 *                 width -- width of the maze
 *                 height -- height of the maze
 *                 xStart -- pointer to where x start location should be stored
 *                 yStart -- pointer to where y start location should be stored
 *                 xEnd -- pointer to where x end location should be stored
 *                 yEnd -- pointer to where y end location should be stored
 * OUTPUTS: xStart, yStart, xEnd, and yEnd set to corresponding locations
 * RETURN: none
 * SIDE EFFECTS: none
 */ 
void findStartEnd(char ** maze, int width, int height, int * xStart, int * yStart, int * xEnd, int * yEnd)
{
    *xStart = -1;
    *yStart = -1;
    *xEnd = -1;
    *yEnd = -1;
    int i, j;
    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            if(maze[i][j] == 'S') {
                *xStart = j;
                *yStart = i;
            }
            if(maze[i][j] == 'E') {
                *xEnd = j;
                *yEnd = i;
            }
        }
    }
}

/*
 * printMaze -- prints out the maze in a human readable format (should look like examples)
 * INPUTS:      maze -- 2D char array that holds the contents of the maze 
 *              width -- width of the maze
 *              height -- height of the maze
 * OUTPUTS:     none
 * RETURN:      none
 * SIDE EFFECTS: prints the maze to the console
 */
void printMaze(char ** maze, int width, int height)
{
   int i, j;
   for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
   }
}

int abso(int val) {
    if(val < 0) {
        return val * -1;
    } else {
        return val;
    } 
}

int calculateManhattan(int x1, int x2, int y1, int y2) {
    return abso(y1 - y2) + abso(x1 - x2);
}
/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:                  maze -- 2D char array that holds the contents of the maze
 *                          width -- the width of the maze
 *                          height -- the height of the maze
 *                          xPos -- the current x position within the maze
 *                          yPos -- the current y position within the maze
 *                          xEnd -- the x position of the end of the maze
 *                          yEnd -- the y position of the end of the maze
 * OUTPUTS:                 updates maze with the solution path ('.') and visited nodes ('~')
 * RETURNS:                 0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:            none
 */ 
int solveMazeManhattanDFS(char ** maze, int width, int height, int xPos, int yPos, int xEnd, int yEnd)
{
    if(xPos < 0 || xPos >= width  || yPos < 0 || yPos >= height) {
        return 0;
    }
    if(maze[yPos][xPos] == '%' || maze[yPos][xPos] == '.' || maze[yPos][xPos] == '~') {
        return 0;
    }
    if(xPos == xEnd && yPos == yEnd) {
        return 1;
    }
    if(maze[yPos][xPos] != 'S') {
        maze[yPos][xPos] = '.';
    }
    int distances[4];
    distances[0] = calculateManhattan(xPos, xEnd, yPos-1, yEnd);
    distances[1] = calculateManhattan(xPos, xEnd, yPos+1, yEnd);
    distances[2] = calculateManhattan(xPos-1, xEnd, yPos, yEnd);
    distances[3] = calculateManhattan(xPos+1, xEnd, yPos, yEnd);
    char directions[4] = {'u','d','l','r'};
    int i;
    int s = 1;
    //printMaze(maze, width, height);
    //printf("\n");
    while(s) {
        s = 0;
        for(i = 1; i < 4; i++) {
            if(distances[i] < distances[i-1]) {
                int t = distances[i];
                distances[i] = distances[i-1];
                distances[i-1] = t;
                char tc = directions[i];
                directions[i] = directions[i-1];
                directions[i-1] = tc;
                s = 1;
            }
        }
    }
    for(i = 0; i < 4; i++){
        if(directions[i] == 'l') {
            if(solveMazeManhattanDFS(maze, width, height, xPos-1, yPos, xEnd, yEnd)) {
                return 1;
            }
        } else if(directions[i] == 'r') {
            if(solveMazeManhattanDFS(maze, width, height, xPos+1, yPos, xEnd, yEnd)) {
                return 1;
            }
        } else if(directions[i] == 'd') {
            if(solveMazeManhattanDFS(maze, width, height, xPos, yPos+1, xEnd, yEnd)) {
                return 1;
            }
        } else {
            if(solveMazeManhattanDFS(maze, width, height, xPos, yPos-1, xEnd, yEnd)) {
                return 1;
            }
        }
    }
    if(maze[yPos][xPos] != 'S') {
        maze[yPos][xPos] = '~';
    }
    return 0;
}

/*
 * checkMaze -- checks if a maze has a valid solution or not
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- the starting x position in the maze
 *              y -- the starting y position in the maze
 * OUTPUTS:     none
 * RETURN:      1 if the maze has a valid solution, otherwise 0
 * SIDE EFFECTS: none
 */ 
int checkMaze(char ** maze, int width, int height, int x, int y)
{
    int j;
    int i;
    for (j=1; j< height-1; j++){
        for(i=1; i<width-1; i++){
            int count = 0;
            if (maze[i][j] == '.'){
                if(maze[i][j-1] == '.') count++;
                if (maze[i+1][j] == '.') count++;
                if (maze[i][j+1] == '.') count++;
                if (maze[i-1][j] == '.') count++;
                if (count > 2) return 0;
            }
        }
    }

    return 1;
}

/*
 * solveMazeBFS -- solves the maze using a breadth first search algorithm
 * INPUTS:         maze -- A 2D array that contains the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the starting x position within the maze
 *                 yPos -- the starting y position within the maze
 * OUTPUTS:        none
 * RETURNS:        0 if the maze is unsolvable, else 1
 * SIDE EFFECTS:   marks the cells within the maze as visited or part of the solution path
 */
int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos)
{
    return 1;
}

/*
 * enqueue -- enqueues an integer onto the given queue
 * INPUTS:    queue -- a pointer to the array that will hold the contents of the queue
 *            value -- the value to  enqueue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   none
 * SIDE EFFECTS: adds an item to the queue
 */ 
void enqueue(int * queue, int value, int * head, int * tail, int maxSize)
{
    if ((*tail - maxSize) == *head)
    {
        printf("Queue is full\n");
        return;
    }
    *tail = *tail + 1;
    queue[*tail % maxSize] = value;
}

/* dequeue -- dequeues an item from the given queue
 * INPUTS:    queue -- a pointer to the array that holds the contents of the queue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   the value dequeued from the queue
 * SIDE EFFECTS: removes an item from the queue
 */
int dequeue(int * queue, int * head, int * tail, int maxSize)
{
    if (*head == *tail)
    {
        printf("Queue is empty\n");
        return -1;
    }
    *head = *head + 1;
    return queue[*head % maxSize];
}
