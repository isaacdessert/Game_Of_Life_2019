#include "life.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * get_grid creates new memory for a "grid".
 * x is the height and y is the width.
 */
char** get_grid(int x, int y) {
    char** grid;
	if(x <= 30 && y <= 30 && x >=3 && y >= 3)
	{
        grid = (char **)malloc(sizeof(char*)*x);
        for(int i = 0; i < y; i++)
            grid[i] = (char*)malloc(sizeof(char)*y);
        return grid;
	}
	else
		exit(EXIT_FAILURE);
}

/*
 * print_grid attempts to print an x height
 * by y width grid stored at the location
 * provided by grid
 */
void print_grid(int x, int y, char** grid) {
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			if(j == y -1)
				printf("%c\n", &grid[i][j]);
			else
				printf("%c", &grid[i][j]);
		}
	}
}

/*
 * mutate takes a grid and mutates that grid
 * according to Conway's rules.  A new grid
 * is returned.
 */
char** mutate(int x, int y, char** grid) {
    char** newGrid;
    newGrid = (char **)malloc(sizeof(char*)*x);
    for(int i = 0; i < y; i++)
        newGrid[i] = (char*)malloc(sizeof(char)*y);
	// TO DO: REPLACE THIS LINE YOUR IMPLEMENTATION
	for(int i = 0; i < x; i++)
	    for(int j = 0; j < y; j++)
	    {
	        //A live cell with less than two live neighbors dies
	        if(grid[i][j] == 'X' && get_neighbors(i,j,x,y,grid) < 2)
	            newGrid[i][j] = '.';
	        //A live cell with two or three live neighbors lives
	        else if(grid[i][j] == 'X' && get_neighbors(i,j,x,y,grid) == 2 || get_neighbors(i,j,x,y,grid) == 3)
	            newGrid[i][j] = 'X';
	        //A live cell with more than three neighbors dies
	        else if(grid[i][j] == 'X' && get_neighbors(i,j,x,y,grid) > 3)
	            newGrid[i][j] = '.';
	        //A dead cell with three live neighbors becomes live
	        else if(grid[i][j] == '.' && get_neighbors(i,j,x,y,grid) ==3)
	            newGrid[i][j] = 'X';
	        else
	            newGrid[i][j] = grid[i][j];
	    }


	return newGrid;
}

/* get_neighbors is a helper method that returns
 * the number of live neighbors a cell has.
 */
int get_neighbors(int i, int j, int x, int y, char** grid) {
	int numberLiving = 0;
	//check right by one
	if(j + 1 < y && grid[i][j + 1] == 'X')
		numberLiving++;
	//check diagonal bottom right
	else if(i + 1 < x && j + 1 < y && grid[i+1][j + 1] == 'X')
		numberLiving++;
	//check down by one
	else if(i + 1 < x && grid[i + 1][j] == 'X')
		numberLiving++;
	//check diagonal bottom left
	else if(i + 1 < x && j - 1 >= 0 && grid[i + 1][j - 1] == 'X')
		numberLiving++;
	//check left
	else if(j - 1 >= 0 && grid[i][j-1] == 'X')
		numberLiving++;
	//check diagonal up left
	else if(j -1 >= 0 && i - 1 >=0 && grid[i-1][j-1] == 'X')
		numberLiving++;
	//check up
	else if(i - 1 >= 0 && grid[i - 1][j] == 'X')
		numberLiving++;
	//check up right
	else if(i - 1 >= 0 && j + 1 <y && grid[i-1][j + 1] == 'X')
		numberLiving++;

	return numberLiving;
}


/*return the locations of the living neighbors
 * might implement this we will see
 */
// You are free to add other helper functions in this file
