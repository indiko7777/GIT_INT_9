#ifndef QUEUE_H
#define QUEUE_H

#include "loc.h"

/**
 * @brief Structure for the queue of positions
 */
typedef struct s_queue
{
    t_position *values;
    int size;
    int first;
    int last;
} t_queue;

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
t_queue createQueue(int size);

/**
 * @brief Function to enqueue a position into the queue
 * @param p_queue : pointer to the queue
 * @param pos : position to enqueue
 */
void enqueue(t_queue *p_queue, t_position pos);

/**
 * @brief Function to dequeue a position from the queue
 * @param p_queue : pointer to the queue
 * @return the dequeued position
 */
t_position dequeue(t_queue *p_queue);

#endif // QUEUE_H
