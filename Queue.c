#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#define MAX_SIZE 256

Queue* createQueue(void)
{
    Queue* queue = (Queue*)malloc(
        sizeof(Queue));
    queue->capacity = MAX_SIZE;
    queue->front = queue->size = 0;
 
    // This is important, see the enqueue
    queue->rear = queue->capacity - 1;
    queue->array = (Node*)malloc(
        queue->capacity * sizeof(Node));
    return queue;
}
int isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}
int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}
void enqueue(Queue* queue, Node item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //fprintf(stderr,"(%d,%d) enqueued to queue\n", item.x,item.y);
    //fflush(stderr);
}
Node dequeue(Queue* queue)
{
    if (isEmpty(queue))
    {
        fprintf(stderr,"Queue is Empty\n");
        fflush(stderr);
        exit(1);
    }
    Node item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
Node front(Queue* queue)
{
    if (isEmpty(queue))
    {
        fprintf(stderr,"Queue is Empty\n");
        fflush(stderr);
        exit(1);
    }
    return queue->array[queue->front];
}
Node rear(Queue* queue)
{
    if (isEmpty(queue))
    {
        fprintf(stderr,"Queue is Empty\n");
        fflush(stderr);
        exit(1);
    }
    return queue->array[queue->rear];
}