#include<stdio.h>
#include<stdlib.h>
 
/* structure of a stack node */
typedef struct sNode
{
   int data;
   struct sNode *next;
}sNode;
  
/* Function to push an item to stack*/
void push(sNode** top_ref, int new_data);
  
/* Function to pop an item from stack*/
int pop(sNode** top_ref);
 
  
/* structure of queue having two stacks */
typedef struct queue 
{
	sNode* stack1;
	sNode* stack2;
}queue;

/* Function to enqueue an item to queue */
void nQueue(queue *q, int x);

/* Function to dequeue an item from queue */
int dQueue(queue *q);
