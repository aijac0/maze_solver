// File: queue.c
// Header file to dynamic FIFO data structure 
//    capable of storing possible moves in maze.
// @author: Aidan Collins (ajc5660)
// @date: 12 APR 2022
// // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * Dynamic FIFO data structure able to store
 *    coordinate values.
 * @variable first: First linked list node in Queue
 * @variable last: Last linked list node in Queue
 */
struct QueueADT {
   Element first;
   Element last;
};

/**
 * Linked list node able to hold coordinate info
 * @variable from: encoded direction of move that lead
 *    to coordinate denoted by node.
 *    0: left, 1: up, 2: right, 3: down
 * @variable n: row component of coordinate
 * @variable m: column component of coordinate
 * @variable next: next node in linked list
 */
struct ElementADT {
   Element next;
   int n;
   int m;
};


/**
 * Initializes Queue with size default_elems
 * @return: created Queue
 */
Queue queue_create() {
   Queue queue = malloc(sizeof(struct QueueADT));
   queue->first = 0;
   queue->last = 0;
   return queue;
}


/**
 * Add a coordinate to Queue.
 * Grow Queue if necessary.
 * @param que: Queue to add coordinate to
 * @param n: Row component of coordinate
 * @param m: Column component of coordinate
 */
void queue_enqueue(Queue que, int n, int m) {
   // create new linked list node
   Element new = malloc(sizeof(struct ElementADT));
   new->n = n;
   new->m = m;
   new->next = 0;
   // determine placement of node based on Queue contents
   if (que->first && que->last) {
      que->last->next = new;
      que->last = new;
   } else if (que->first) {
      que->first->next = new;
      que->last = new;
   } else {
      que->first = new;
   }
}


/** 
 * Remove the next coordinate in Queue
 * @param que: Queue to dequeue from
 * @param arr: arr of length 2 to add coordinate components to
 * @return: 1 if successful, else 0 (Queue is empty)
 */
char queue_dequeue(Queue que, int* arr) {
   // determines if Queue is empty
   if (queue_is_empty(que)) {
      return 0;
   }
   arr[0] = que->first->n;
   arr[1] = que->first->m;
   if (que->first->next) {
      Element temp = que->first;
      que->first = que->first->next;
      free(temp);
      if (que->first == que->last) {
         que->last = 0;
      }
   } else {
      free(que->first);
      que->first = 0;
   }
   return 1;
}


/**
 * Determines if there is at least one element in Queue
 * @param que: Queue to check the contents of
 * @return: 0 if not empty, else != 0
 */
char queue_is_empty(Queue que) {
   return (!que->first);
}


/**
 * Free all dynamically allocated memory
 *    associated with Queue
 * @param que: Queue to destroy
 */
void queue_destroy(Queue que) {
   Element curr = que->first;
   Element next;
   while (curr) {
      next = curr->next;
      free(curr);
      curr = next;
   }
   free(que);
}
