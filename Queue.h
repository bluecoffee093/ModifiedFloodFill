#pragma once

typedef struct
{
    int x,y;
}Node;

typedef struct  {
    int front, rear, size;
    int capacity;
    Node* array;
}Queue;

Queue* createQueue(void);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, Node item);
Node dequeue(Queue* queue);
Node front(Queue* queue);
Node rear(Queue* queue);
