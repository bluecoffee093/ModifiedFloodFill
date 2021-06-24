#define X_DIM 16
#define Y_DIM 16

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Queue.h"
#include "API.h"
#include "FloodFill.h"

int X =0;
int Y=0;
int dir=0;

void UpdateXY(void)
{
    switch(dir)
    {
    case 0:
        Y++;
        break;
    case 1:
        X++;
        break;
    case 2:
        Y--;
        break;
    case 3:
        X--;
         break;
    default:
        break;
    }
}
int findMinimum(int a,int b,int c,int d, int reference)
{
    int values[4] = {INT_MAX,INT_MAX,INT_MAX,INT_MAX};
    if (abs(reference - a) == 1)
        values[0] = a;
    if (abs(reference - b) == 1)
        values[1] = b;
    if (abs(reference - c) == 1)
        values[2] = c;
    if (abs(reference - d) == 1)
        values[3] = d;
    int min=INT_MAX;
    for(int i=0;i<4;i++)
    {
        if(values[i] < min)
        {
            min = values[i];
        }
    }
    return min;
}
void displayCellValues(int value[Y_DIM][X_DIM]);
void UpdateWalls(int wall[Y_DIM][X_DIM]);
char findNextNeighbour(int current_X,int current_Y,int maze[Y_DIM][X_DIM],int wall[Y_DIM][X_DIM]);
void moveToNextNode(int current_X,int current_Y,char move);


int main()
{
    int maze[Y_DIM][X_DIM] = {0};
    int wall[Y_DIM][X_DIM] = {0};

    int Target_cell_X = X_DIM/2;
    int Target_cell_Y = Y_DIM/2;
    while(!(X == Target_cell_X && Y== Target_cell_Y))
    {
        UpdateWalls(wall);
        floodFillMaze(X_DIM/2,Y_DIM/2,maze,wall);
        displayCellValues(maze);
        char move=findNextNeighbour(X,Y,maze,wall);
        //fprintf(stderr,"MOVE=%c\t",move);
        //fflush(stderr);
        moveToNextNode(X,Y,move);
    }
    return 0;
}


char findNextNeighbour(int current_X,int current_Y,int maze[Y_DIM][X_DIM],int wall[Y_DIM][X_DIM])
{
   int min = findMinimum( (current_X > 0) ? maze[current_Y][current_X-1] : INT_MAX,
                (current_Y > 0) ? maze[current_Y-1][current_X] : INT_MAX,
                (current_X < X_DIM-1) ? maze[current_Y][current_X+1] : INT_MAX,
                (current_Y < Y_DIM-1) ? maze[current_Y + 1][current_X] : INT_MAX,
                maze[current_Y][current_X]
   );
   switch (dir)
   {
   case 0:
        if(current_Y <(Y_DIM -1) && maze[current_Y + 1][current_X] == min && !(wall[current_Y][current_X] & 0b0001))
            return 'f';
        if(current_X <(X_DIM -1) && maze[current_Y][current_X+1] == min && !(wall[current_Y][current_X] & 0b0010))
            return 'r';
        if(current_X > 0 && maze[current_Y][current_X-1] == min && !(wall[current_Y][current_X] & 0b1000))
            return 'l';
        if(current_Y > 0 && maze[current_Y - 1][current_X] == min && !(wall[current_Y][current_X] & 0b0100))
           return 'b';

    case 1:
        if(current_X <(X_DIM -1) && maze[current_Y][current_X+1] == min && !(wall[current_Y][current_X] & 0b0010))
            return 'f';
        if(current_Y <(Y_DIM -1) && maze[current_Y + 1][current_X] == min && !(wall[current_Y][current_X] & 0b0001))
            return 'l';
        if(current_Y > 0 && maze[current_Y - 1][current_X] == min && !(wall[current_Y][current_X] & 0b0100))
            return 'r';
        if(current_X > 0 && maze[current_Y][current_X-1] == min && !(wall[current_Y][current_X] & 0b1000))
            return 'b';

    case 2:
        if(current_Y > 0 && maze[current_Y - 1][current_X] == min && !(wall[current_Y][current_X] & 0b0100))
            return 'f';
        if(current_X <(X_DIM -1) && maze[current_Y][current_X+1] == min && !(wall[current_Y][current_X] & 0b0010))
            return 'l';
        if(current_X > 0 && maze[current_Y][current_X-1] == min && !(wall[current_Y][current_X] & 0b1000))
            return 'r';
        if(current_Y <(Y_DIM -1) && maze[current_Y + 1][current_X] == min && !(wall[current_Y][current_X] & 0b0001))
            return 'b';

    case 3:
        if(current_X > 0 && maze[current_Y][current_X-1] == min && !(wall[current_Y][current_X] & 0b1000))
            return 'f';
        if(current_Y <(Y_DIM -1) && maze[current_Y + 1][current_X] == min && !(wall[current_Y][current_X] & 0b0001))
            return 'r';
        if(current_Y > 0 && maze[current_Y - 1][current_X] == min && !(wall[current_Y][current_X] & 0b0100))
            return 'l';
        if(current_X <(X_DIM -1) && maze[current_Y][current_X+1] == min && !(wall[current_Y][current_X] & 0b0010))
           return 'b';
   }
   return 'N';
}
void displayCellValues(int value[Y_DIM][X_DIM])
{
    char buffer[5];
    for(int y=0; y < Y_DIM; y++)
        for(int x=0;x<X_DIM;x++)
            API_setText(x,y,itoa(value[y][x],buffer,10));
}
void UpdateWalls(int wall[Y_DIM][X_DIM])
{
    int Wall_state = 0;
    int Neighbour_state[4] = {0};
    switch(dir)
    {
    case 0:
        if (API_wallFront())
        {
            API_setWall(X,Y,'n');
        Wall_state += 1;
        Neighbour_state[0] += 4;
        }
        if (API_wallRight())
        {
            API_setWall(X,Y,'e');
        Wall_state += 2;
        Neighbour_state[1] += 8;
        }
        if (API_wallLeft())
        {
            API_setWall(X,Y,'w');
        Wall_state += 8;
        Neighbour_state[3] += 2;
        }
        break;
    case 1:
        if (API_wallFront())
        {
            API_setWall(X,Y,'e');
        Wall_state += 2;
        Neighbour_state[1] += 8;
        }
        if (API_wallRight())
        {
            API_setWall(X,Y,'s');
        Wall_state += 4;
        Neighbour_state[2] += 1;
        }
        if (API_wallLeft())
        {
            API_setWall(X,Y,'n');
        Wall_state += 1;
        Neighbour_state[0] += 4;
        }
        break;
    case 2:
        if (API_wallFront())
        {
            API_setWall(X,Y,'s');
        Wall_state += 4;
        Neighbour_state[2] += 1;
        }
        if (API_wallRight())
        {
            API_setWall(X,Y,'w');
        Wall_state += 8;
        Neighbour_state[3] += 2;
        }
        if (API_wallLeft())
        {
            API_setWall(X,Y,'e');
        Wall_state += 2;
        Neighbour_state[1] += 8;
        }
        break;
    case 3:
        if (API_wallFront())
        {
            API_setWall(X,Y,'w');
            Wall_state += 8;
            Neighbour_state[3] += 2;
        }
        if (API_wallRight())
        {
            API_setWall(X,Y,'n');
            Wall_state += 1;
            Neighbour_state[0] += 4;
        }
        if (API_wallLeft())
        {
            API_setWall(X,Y,'s');
            Wall_state += 4;
            Neighbour_state[2] += 1;
        }
         break;
    default:
        break;
    }
    wall[Y][X] = Wall_state;
    if(Y<Y_DIM - 1 && !(wall[Y+1][X] & Neighbour_state[0]))
        wall[Y+1][X] += Neighbour_state[0];
    if(Y<X_DIM - 1 && !(wall[Y][X+1] & Neighbour_state[1]))
        wall[Y][X+1] += Neighbour_state[1];
    if(Y>0 && !(wall[Y-1][X] & Neighbour_state[2]))
        wall[Y-1][X] += Neighbour_state[2];
    if(X>0 && !(wall[Y][X-1] & Neighbour_state[3])) 
        wall[Y][X-1] += Neighbour_state[3];
    for(int j=0;j<Y_DIM;j++)
    {
        for(int k =0;k<X_DIM;k++)
        {
            fprintf(stderr,"%3d ",wall[Y_DIM - j -1][k]);
            fflush(stderr);
        }
        fprintf(stderr,"\n");
        fflush(stderr);
    }
    fprintf(stderr,"\n\n\n");
    fflush(stderr);
}
void moveToNextNode(int current_X,int current_Y,char move)
{
    if(move == 'r')
    {
        API_turnRight();
        (dir == 3) ? dir = 0: dir++;

    }
    else if(move == 'l')
    {
        API_turnLeft();
        (dir == 0) ? dir = 3: dir--;
    }
    else if(move == 'b')
    {
        API_turnRight();
        API_turnRight();
        switch(dir)
        {
            case 0:
            dir = 2;
            break;

            case 1:
            dir = 3;
            break;

            case 2:
            dir = 0;
            break;

            case 3:
            dir = 1;
            break;
        }
    }
    else if(move == 'N')
    {
        fprintf(stderr,"ERROR!");
        fflush(stderr);
        exit(1);
    }
    API_moveForward();
    //fprintf(stderr,"CRASH = %d\n", !API_moveForward());
    //fflush(stderr);
    UpdateXY();
}
