#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "FloodFill.h"

int isDeadEnd(int cell_x, int cell_y, int wall[Y_DIM][X_DIM])
{
    return (wall[cell_y][cell_x] == 14 ||  wall[cell_y][cell_x]== 7 || wall[cell_y][cell_x] == 11 ||  wall[cell_y][cell_x] == 13);
}
void floodFillMaze(int startCell_x, int startCell_y, int maze[Y_DIM][X_DIM], int wall[Y_DIM][X_DIM])
{
    for(int i=0;i<Y_DIM;i++)
        for(int j=0;j<X_DIM;j++)
            maze[i][j] = 0;
    int prevValue = 0;
    floodFillBFS(startCell_x, startCell_y, maze, wall);
}
void floodFillBFS(int startCell_x, int startCell_y, int maze[Y_DIM][X_DIM], int wall[Y_DIM][X_DIM])
{
    List *queue = createLinkedList();
    List *wallMaxvalue = createLinkedList();
    data node= {startCell_x,startCell_y};
    maze[startCell_y][startCell_x] = 0;
    enqueue(queue,node);
    while(!isEmpty(queue))
    {
        data checkNode = dequeue(queue);

        if(isDeadEnd(checkNode.x,checkNode.y,wall))
                enqueue(wallMaxvalue,checkNode);
        if(checkNode.x>0 && maze[checkNode.y][checkNode.x - 1]==0 && !(wall[checkNode.y][checkNode.x] & 0b1000))
        {
            maze[checkNode.y][checkNode.x - 1] = maze[checkNode.y][checkNode.x] + 1;
            data newNode={checkNode.x - 1,checkNode.y};
            enqueue(queue,newNode);
        }
        if(checkNode.x<(X_DIM-1) && maze[checkNode.y][checkNode.x +1]==0 && !(wall[checkNode.y][checkNode.x] & 0b0010))
        {
            maze[checkNode.y][checkNode.x + 1] = maze[checkNode.y][checkNode.x] + 1;
            data newNode={checkNode.x + 1,checkNode.y};
            enqueue(queue,newNode);
        }
        if(checkNode.y>0 && maze[checkNode.y-1][checkNode.x]==0 && !(wall[checkNode.y][checkNode.x] & 0b0100))
        {
            maze[checkNode.y-1][checkNode.x] = maze[checkNode.y][checkNode.x] + 1;
            data newNode={checkNode.x,checkNode.y - 1};
            enqueue(queue,newNode);
        }
        if(checkNode.y<(Y_DIM-1) && maze[checkNode.y+1][checkNode.x]==0 && !(wall[checkNode.y][checkNode.x] & 0b0001))
        {
            maze[checkNode.y+1][checkNode.x] = maze[checkNode.y][checkNode.x] + 1;
            data newNode={checkNode.x,checkNode.y + 1};
            enqueue(queue,newNode);
        }
    }
    for(int x=0; x<wallMaxvalue->size;x++)
    {
        data deadEnd = dequeue(wallMaxvalue);
        maze[deadEnd.y][deadEnd.x] = Y_DIM*X_DIM + 1;
    }
    maze[startCell_y][startCell_x] = 0;
}