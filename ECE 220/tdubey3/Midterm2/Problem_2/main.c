#include "queue.h"
int main()
{
   /* Create a queue with items 1 2 3*/
   queue *q = (queue*)malloc(sizeof(queue));
   q->stack1 = NULL;
   q->stack2 = NULL;
   nQueue(q, 1);
   nQueue(q, 2);
   nQueue(q, 3);
   nQueue(q, 81);
   nQueue(q, 1);    
  
   /* Dequeue items */
   printf("%d  ", dQueue(q));
   printf("%d  ", dQueue(q));
   printf("%d  ", dQueue(q));
   printf("%d  ", dQueue(q));
   printf("%d \n", dQueue(q));  
  
   return 0;
}
 
