/*
    NETID: tdubey3
    Partners: schevli2, hqu5
    This file contains methods for performing operations on sparse matricies. Such operations are:
    load -> This method loads a text file containing information and creates a sparse array
    gv -> Returns the value at a specific x y coordinate 
    set -> Sets the value at a specific x y coordinate
    save -> Prints the non zero values of the sparse matrix to a file
    add -> Adds two matricies together
    multi -> Multiplies two matricies together
    destory -> Removes the matrix from memory
*/

#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>
/*
    load_tuples opens a file with the name 'input_file', read the data from the file, and return a matrix. 
    If any coordinates repeat in the input file, the newer coordinates ( a lower line closer to the end of  the text document ) 
    overwrite the old line
*/
sp_tuples * load_tuples(char* input_file)
{
    //Set variables
    int width, height;
    int x = 0, y=0;
    double value;
    int isHead = 1;
    FILE *ifp;

    //Open file and check if valid
    ifp = fopen(input_file, "r");
    if(ifp == NULL) {
        printf("ERROR: Could not open file!\n");
        exit(1);
    }

    //Get width and Height
    fscanf(ifp, "%d", &height);
    fscanf(ifp, "%d", &width);
    fgetc(ifp);

    //Create array and set width and height
    sp_tuples * tuplesArray = (sp_tuples *)malloc(sizeof(sp_tuples));
    tuplesArray->m = height;
    tuplesArray->n = width;
    tuplesArray->nz = 0;

    while(fscanf(ifp,"%i %i %lf", &x, &y, &value) == 3) {
        if(value == 0) {
            //do Nothing
        } else {
            if(isHead) {
                //Set only the head of the list
                sp_tuples_node * newNode = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
                tuplesArray->tuples_head = newNode;
                newNode->value = value;
                newNode->row = x;
                newNode->col = y;
                newNode->next = NULL;
                tuplesArray->nz = tuplesArray->nz + 1;
                isHead = 0;
            } else {
                //Check to see if a value already exists
                sp_tuples_node * curr = tuplesArray->tuples_head;
                int isDone = 0;
                while(curr != NULL) {
                    if(curr->row == x && curr-> col == y && !isDone){
                        if(curr->value == value){
                            isDone = 1;
                        } else {
                            curr->value = value;
                            isDone = 1;
                        }
                    }
                    curr = curr->next;
                }
                if(!isDone) {
                    //If not head or existing, create a new value and put it in approiate spot
                    sp_tuples_node * newNode = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
                    newNode->value = value;
                    newNode->row = x;
                    newNode->col = y;
                    tuplesArray->nz = tuplesArray->nz + 1;
                    sp_tuples_node * curr = tuplesArray->tuples_head;
                    newNode->next = NULL;
                    while(curr->next != NULL){
                        if(curr->next->col > y && y > curr->col) {
                            if(curr->next->row > x && x > curr->row) {
                                newNode->next = curr->next;
                                curr->next = newNode;
                            }
                        }

                        curr = curr->next;
                    }
                    curr->next = newNode;
                }
            }
            // sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples));
            // node->value = value;
            // node->row = x;
            // node->col = y;
            // node->next = NULL;
            // if(isHead) {
            //     tuplesArray->tuples_head = node;
            //     isHead = 0;
            // }
            // if(temp != NULL) {
            //     tem-p>next = node;
            // }
            // temp = node;
            // tuplesArray->nz = tuplesArray->nz - 1;
        }
    }
    fclose(ifp);
    return tuplesArray;
}

sp_lils * load_lils(char* input_file)
{
    return NULL;	
}

double gv_lils(sp_lils * mat_l,int row,int col)
{
    return 0;
}
/*
gv_tuples returns the value of the element at the given row and column within the matrix.
*/
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    int found = 0;
    double value;
    sp_tuples_node * curr;
    curr = mat_t->tuples_head;
    //Go through the list and see if value exists
    while(curr->next != NULL) {
        if((curr->row == row) && (curr->col == col)) {
            value = curr->value;
            found = 1;
        }
        curr = curr->next;
    }
    //If the value doesn't exist, just return zero, I mean, what else are you going to do? Make me a cofee? 
    if(found){
        return value;
    } else {
        return 0;
    }
}
/*
set_lils and set_tuples sets the element at row and col to value
    if value is 0, it will find the node at row and col if it exists, and delete it from the list.
    For any other value, the function will find the correct location for the node within the sorted linked list. 
        If the entry already exists, the function will replace the old value. 
        If the entry doesn't exist, a node will be created and inserted into the linked list.
*/
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    //If it's null, make it the head, like you should be doing, or don't do this, I don't even care
    if(mat_t->tuples_head == NULL){
        sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples));
        node->value = value;
        node->row = row;
        node->col = col;
        node->next = NULL;
        mat_t->tuples_head = node;
        return;
    }
    //If the value is zero, why do anyting? Oh wait, we must delete it if it is already is a node
    if(value == 0) {
        sp_tuples_node * curr = mat_t->tuples_head;
        sp_tuples_node * currForward;
        while(curr->next->row != row && curr->next->col != col) {
            curr = curr->next;
            if(curr == NULL || curr->next == NULL){
                return;
            }
        }
        currForward = curr->next->next;
        free(curr->next);
        curr->next = currForward;
        mat_t->nz = mat_t->nz - 1;
        return;
    } else {
        //I honestly don't know why this works. It was 3AM and I just wrote crap, but it works. 
        sp_tuples_node * curr = mat_t->tuples_head;
        if(gv_tuples(mat_t, row, col) == 0) {
            while(curr->row < row && curr->col < col) {
                if(curr->next == NULL){
                    break;
                } else {
                    curr = curr->next;
                }
            }
            //This also works!
            sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples));
            node->value = value;
            node->row = row;
            node->col = col;
            node->next = curr->next;
            if(curr != NULL){
                curr->next = node;
            } else {
                //Why do I have this? the world may never know
            }
            return;
        } else {
            while(curr->row != row && curr->col != col) {
                curr = curr->next;
            }
            curr->value = value;
            return;
        }
    }
}

void set_lils(sp_lils * mat_l, int row, int col, double value)
{
	return;
}

/*
save_tuples writes the data in a sparse matrix structure to a text file
*/
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    //Create file
    FILE *ofp;
    ofp = fopen(file_name, "w");
    if(ofp == NULL) {
        printf("ERROR: Could not create write file!\n");
        exit(1);
    }
    //Print width and height
    fprintf(ofp, "%d %d\n",mat_t->m, mat_t->n);
    sp_tuples_node * curr = mat_t->tuples_head;
    //Go through the list and print them all out
    while(curr != NULL){
        fprintf(ofp, "%d %d %lf\n",curr->row, curr->col, curr->value);
        curr = curr->next;
    }
    //Close the file
    fclose(ofp);
	return;
}

void save_lils(char * file_name,sp_lils * mat_l)
{
	return;
}
/*
    Add Two matricies together
*/
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    //If you can't add the matricies, then don't
    if((matA->m != matB->m) && (matA->n != matB->n)) {
        return NULL;
    }
    //Make the return matrix
    sp_tuples * retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    sp_tuples_node * currA = matA->tuples_head;
    //Put values of A in this matrix
    while(currA != NULL) {
        set_tuples(retmat, currA->row, currA->col, currA->value);
        retmat->nz = retmat->nz + 1;
        currA = currA->next;
    }
    //Put value of B in matrix while adding it with A
    currA = matB->tuples_head;
    while(currA != NULL) {
        set_tuples(retmat, currA->row, currA->col, currA->value + gv_tuples(retmat, currA->row, currA->col));
        retmat->nz = retmat->nz + 1;
        currA = currA->next;
    }
	return retmat;
}

sp_lils * add_lils(sp_lils * matA, sp_lils * matB){

	return NULL;
}

/*
    Multiply Two matricies together
*/
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    sp_tuples * retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    sp_tuples_node * currA = matA->tuples_head;
    while(currA != NULL) {
        set_tuples(retmat, currA->row, currA->col, currA->value);
        retmat->nz = retmat->nz + 1;
        currA = currA->next;
    }
    currA = matB->tuples_head;
    while(currA != NULL) {
        set_tuples(retmat, currA->row, currA->col, currA->value * gv_tuples(retmat, currA->row, currA->col));
        retmat->nz = retmat->nz + 1;
        currA = currA->next;
    }
    return retmat;
}

sp_lils * mult_lils(sp_lils * matA, sp_lils * matB){
    return NULL;
}

//Helper function to recursively destory a matrix
void destructor(sp_tuples_node * curr){
    //Base Case
    if(curr == NULL){
        return;
    }
    //DESTROY DESTROY DESTROY
    destructor(curr->next);
    //And free it
    free(curr);
    return;
}

//destroy_tuples will free all memory associated with the given matrix.	
void destroy_tuples(sp_tuples * mat_t){
    if(mat_t == NULL){
        return;
    }
    //Make the recursive call
    destructor(mat_t->tuples_head);
    free(mat_t);
    return;
}

void destroy_lils(sp_lils * mat_l){
    return;
}

sp_lils * tuples2lil(sp_tuples * input_mat_t){
	return NULL;
}

sp_tuples * lil2tuples(sp_lils * input_mat_l){
	return NULL;
}