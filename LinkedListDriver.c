#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main()
{
    List* myList = createLinkedList();
    data data1= {34,56};
    enqueue(myList,data1);
    data dequeued = dequeue(myList);
    printf("%d %d", dequeued.x , dequeued.y);
    return 0;
}
