#include <limits.h>
#include "LinkedList.h"

List* createLinkedList(void)
{
    List* list = (List*)malloc(sizeof(List));
    list->HEAD = NULL;
    list->size = 0;
    return list;
}

int isEmpty(List* list)
{
    if(list->size == 0)
        return 1;
    return 0;
}

void enqueue(List* list, data data)
{
    Node* empty;
    empty =  (Node*)malloc(sizeof(Node));
    empty->data = data;
    empty->previous = NULL;
    empty->next = list->HEAD;
    if (!isEmpty(list))
    {
        list->HEAD->previous = empty;
    }
    list->HEAD = empty;
    list->size++;
    return;
}

data dequeue(List* list)
{
    if(list->size == 0)
    {
        fprintf(stderr,"Queue is Empty\n");
        fflush(stderr);
        exit(1);
    }
    Node* iter = list->HEAD;
    for(int x=0;x<list->size-1;x++)
    {
        iter = iter->next; 
    }
    data result = iter->data;
    Node* end = iter; 
    if (list->size > 1)
        iter->previous->next = NULL;
    free(end);
    list->size--;
    return result;
}

data front(List* list)
{
    Node* iter = list->HEAD;
    for(int x=0;x<list->size-1;x++)
    {
        iter = iter->next; 
    }
    return iter->data;
}

data rear(List* list)
{
    Node* start = list->HEAD;
    return start->data;
}