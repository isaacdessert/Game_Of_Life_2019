//Authors: Jesse David and Isaac Dessert

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
			
			//if its at the end of the matrix add to new lines
			if(j == y - 1  && i == x - 1)
				if (grid[i][j] == 0) 
    					printf(" .\n-------------------------\n");
				else 
   					 printf(" X\n-------------------------\n");
			//if its at the end of the line make a new line
			else if(j == y - 1)
				if (grid[i][j] == 0) 
    					printf(" .\n");
				else 
   					 printf(" X\n");

			else
				if (grid[i][j] == 0) 
    					printf(" . ");
				else 
   					 printf(" X ");
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
	int gNeighbors = 0;
    newGrid = (char **)malloc(sizeof(char*)*x);
    for(int i = 0; i < y; i++)
        newGrid[i] = (char*)malloc(sizeof(char)*y);
    for(int i = 0; i < x; i++)
	    for(int j = 0; j < y; j++)
	    {
			gNeighbors = get_neighbors(i,j,x,y,grid);
	        //A live cell with less than two live neighbors dies
	        if(grid[i][j] == 1 && gNeighbors < 2){
				newGrid[i][j] = 0;
			}
	           
	        //A live cell with two or three live neighbors lives
	        else if(grid[i][j] == 1 && (gNeighbors == 2 || gNeighbors == 3)){
				newGrid[i][j] = 1;
			}
	            
	        //A live cell with more than three neighbors dies
	        else if(grid[i][j] == 1 && gNeighbors > 3){
				newGrid[i][j] = 0;
			}
	            
	        //A dead cell with three live neighbors becomes live
	        else if(grid[i][j] == 0 && gNeighbors ==3){
				newGrid[i][j] = 1;
			}
	            
	        else{
				newGrid[i][j] = grid[i][j];
			}
				
		}
	return newGrid;
}

/* get_neighbors is a helper method that returns
 * the number of live neighbors a cell has.
 */
int get_neighbors(int i, int j, int x, int y, char** grid) {
	int numberLiving = 0;

	//Check from top left
	if(j == 0 && i == 0){
		//check right
		if(grid[i][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom right
		if(grid[i + 1][j+1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom
		if(grid[i + 1][j] == 1)
			numberLiving = numberLiving +  1;
	}

	//Check left column
	if(j == 0 && i > 0 && i < x-1){
		//check right
		if(grid[i][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check upper right
		if(grid[i - 1][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom right
		if(grid[i + 1][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom
		if(grid[i + 1][j] == 1)
			numberLiving = numberLiving + 1;
		//check top
		if(grid[i - 1][j] == 1)
			numberLiving = numberLiving + 1;
	}

	//Check bottom left corner
	if(j == 0 && i == x - 1){
		//check top
		if(grid[i - 1][j] ==1)
			numberLiving = numberLiving + 1;
		//check upper right
		if(grid[i - 1][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check right
		if(grid[i][j + 1] == 1)
			numberLiving = numberLiving + 1;
	}

	//Check upper right corner
	if(j == y - 1 && i == 0){
		//check left
		if(grid[i][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom
		if(grid[i + 1][j]== 1)
			numberLiving = numberLiving + 1;
		//check bottom left
		if(grid[i + 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
	}

	//Check far right column
	if(j == y - 1 && i > 0 && i < x-1){
		//check left
		if(grid[i][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom left
		if(grid[i + 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check upper left
		if(grid[i - 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom
		if(grid[i + 1][j] == 1)
			numberLiving = numberLiving + 1;
		//check top
		if(grid[i - 1][j] == 1)
			numberLiving = numberLiving + 1;
	}

	//Check bottom right corner
	if(j == y - 1 && i == x - 1){
		//check left
		if(grid[i][j  - 1] == 1)
			numberLiving = numberLiving + 1;
		//check top
		if(grid[i - 1][j]== 1)
			numberLiving = numberLiving + 1;
		//check upper left
		if(grid[i - 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
	}

	//Check top row
	if(i == 0 && j > 0 && j < y-1){
		//check left
		if(grid[i][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom left
		if(grid[i + 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom right
		if(grid[i + 1][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom
		if(grid[i + 1][j] == 1)
			numberLiving = numberLiving + 1;
		//check right
		if(grid[i][j + 1] == 1)
			numberLiving = numberLiving + 1;
	}

	//Check bottom row
	if(i == x - 1 && j > 0 && j < y-1){
		//check left
		if(grid[i][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check top left
		if(grid[i - 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check top right
		if(grid[i - 1][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check top
		if(grid[i - 1][j] == 1)
			numberLiving = numberLiving + 1;
		//check right
		if(grid[i][j + 1] == 1)
			numberLiving = numberLiving + 1;
	}

	//Check middle
	if(i > 0 && i < x -1 && j > 0 && j < y-1){
		//check left
		if(grid[i][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom left
		if(grid[i + 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom right
		if(grid[i + 1][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check bottom
		if(grid[i + 1][j] == 1)
			numberLiving = numberLiving + 1;
		//check right
		if(grid[i][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check top left
		if(grid[i - 1][j - 1] == 1)
			numberLiving = numberLiving + 1;
		//check top right
		if(grid[i - 1][j + 1] == 1)
			numberLiving = numberLiving + 1;
		//check top
		if(grid[i - 1][j] == 1)
			numberLiving = numberLiving + 1;
	}

	return numberLiving;
}

// You are free to add other helper functions in this file

