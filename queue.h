// File: queue.h
// Header file to dynamic FIFO data structure 
//    capable of storing possible moves in maze.
// @author: Aidan Collins (ajc5660)
// @date: 12 APR 2022
// // // // // // // // // // // // // // // // //

#ifndef _QUEUE_H_
#define _QUEUE_H_

#define DEFAULT_SIZE 16

typedef struct QueueADT* Queue;
typedef struct ElementADT* Element;


/**
 * Initializes Queue with size default_elems
 * @return: created Queue
 */
Queue queue_create();


/**
 * Add a coordinate to Queue.
 * Grow Queue if necessary.
 * @param que: Queue to add coordinate to
 * @param n: Row component of coordinate
 * @param m: Column component of coordinate
 */
void queue_enqueue(Queue que, int n, int m); 


/** 
 * Remove the next coordinate in Queue
 * @param que: Queue to dequeue from
 * @param arr: arr of length 2 to add coordinate compents to
 * @return: 1 if successful, else 0 (Queue is empty)
 */
char queue_dequeue(Queue que, int* arr);


/**
 * Determines if there is at least one element in Queue
 * @param que: Queue to check the contents of
 * @return: 0 if not empty, else != 0
 */
char queue_is_empty(Queue que);


/**
 * Free all dynamically allocated memory
 *    associated with Queue
 * @param que: Queue to destroy
 */
void queue_destroy(Queue que);


#endif
