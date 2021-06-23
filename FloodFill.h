#pragma once
#define BFS 1
#define DFS 0

#ifndef X_DIM
#define X_DIM 16
#endif

#ifndef Y_DIM
#define Y_DIM 16
#endif

void floodFillBFS(int startCell_x, int startCell_y, int maze[Y_DIM][X_DIM], int wall[Y_DIM][X_DIM]);
void floodFillMaze(int startCell_x, int startCell_y, int maze[Y_DIM][X_DIM], int wall[Y_DIM][X_DIM]);