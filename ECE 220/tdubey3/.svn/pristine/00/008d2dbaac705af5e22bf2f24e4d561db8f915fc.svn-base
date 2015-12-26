#include "queue.h"
/* Function to enqueue an item to queue */
void nQueue(queue *q, int x)
{
	push(&(q->stack1) ,x);
}

/* Function to dequeue an item from queue */
int dQueue(queue *q)
{
	if(q->stack1 == NULL && q->stack2 == NULL) {
		printf("Stacks Empty");
		exit(0);
	} else if (q->stack2 == NULL) {
		while(q->stack1 != NULL) {
			push(&q->stack2, pop(&q->stack1));
		}
	}
	return pop(&q->stack2);
}
 
/* Function to push an item to stack*/
void push(sNode** top_ref, int new_data)
{
  /* allocate node */
  sNode* new_node = (sNode*) malloc(sizeof(sNode));
  
  if(new_node == NULL)
  {
     printf("Stack overflow \n");
     exit(0);
  }         
  
  /* put in the data  */
  new_node->data  = new_data;
  
  /* link the old list off the new node */
  new_node->next = (*top_ref);   
  
  /* move the head to point to the new node */
  (*top_ref)    = new_node;
}
  
/* Function to pop an item from stack*/
int pop(struct sNode** top_ref)
{
  int res;
  sNode *top;
  
  /*If stack is empty then error */
  if(*top_ref == NULL)
  {
     printf("Stack overflow \n");
     exit(0);
  }
  else
  {
     top = *top_ref;
     res = top->data;
     *top_ref = top->next;
     free(top);
     return res;
  }
}
  
