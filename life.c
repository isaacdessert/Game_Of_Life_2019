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
			//if its at the end of the line make a new line
			if(j == y - 1)
				if (grid[i][j] == 0) 
    					printf(" .\n");
				else 
   					 printf(" X\n");
			//if its at the end of the matrix add to new lines
			else if(j == y - 1  && i == x - 1)
				if (grid[i][j] == 0) 
    					printf(" .\n\n");
				else 
   					 printf(" X\n\n");

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
				printf("Rule one activated\n");
			}
	           
	        //A live cell with two or three live neighbors lives
	        else if(grid[i][j] == 1 && (gNeighbors == 2 || gNeighbors == 3)){
				newGrid[i][j] = 1;
				printf("Rule two activated\n");
			}
	            
	        //A live cell with more than three neighbors dies
	        else if(grid[i][j] == 1 && gNeighbors > 3){
				newGrid[i][j] = 0;
				printf("Rule three activated\n");
			}
	            
	        //A dead cell with three live neighbors becomes live
	        else if(grid[i][j] == 0 && gNeighbors ==3){
				newGrid[i][j] = 1;
				printf("Rule four activated\n");
			}
	            
	        else{
				newGrid[i][j] = grid[i][j];
				printf("Piece remaines the same\n");
			}
				
		}
	return newGrid;
}

/* get_neighbors is a helper method that returns
 * the number of live neighbors a cell has.
 */
int get_neighbors(int i, int j, int x, int y, char** grid) {
	printf("Enters get_neighbors\n");
	int numberLiving = 0;
	printf("\nPiece being looked at: %d\n", grid[i][j]);

	//Check from top left
	if(j == 0 && i == 0){
		//check right
		if(grid[i][j + 1] == 1)
			numberLiving = numberLiving + 1;

	}
	//check right by one
	if(j + 1 < y && grid[i][j + 1] == 1){
		numberLiving = numberLiving + 1;
	}	
	//check diagonal bottom right
	else if(i + 1 < x && j + 1 < y && grid[i+1][j + 1] == 1)
		numberLiving = numberLiving + 1;
	//check down by one
	else if(i + 1 < x && grid[i + 1][j] == 1)
		numberLiving = numberLiving + 1;
	//check diagonal bottom left
	else if(i + 1 < x && j - 1 >= 0 && grid[i + 1][j - 1] == 1)
		numberLiving = numberLiving + 1;
	//check left
	else if(j - 1 >= 0 && grid[i][j-1] == 1)
		numberLiving = numberLiving + 1;
	//check diagonal up left
	else if(j -1 >= 0 && i - 1 >=0 && grid[i-1][j-1] == 1)
		numberLiving = numberLiving + 1;
	//check up
	else if(i - 1 >= 0 && grid[i - 1][j] == 1)
		numberLiving = numberLiving + 1;
	//check up right
	else if(i - 1 >= 0 && j + 1 <y && grid[i-1][j + 1] == 1)
		numberLiving = numberLiving + 1;

	printf("Your number is: %d\n", numberLiving);
	return numberLiving;
}

// You are free to add other helper functions in this file

