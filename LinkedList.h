#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Data{
    int x;
    int y;
} data;

typedef struct node{
    data data;
    struct node* next;
    struct node* previous;
} Node;

typedef struct LinkedList{
    Node* HEAD;
    int size;
} List;

List* createLinkedList(void);
int isEmpty(List* list);
void enqueue(List* list, data data);
data dequeue(List* list);
data front(List* list);
data rear(List* list);