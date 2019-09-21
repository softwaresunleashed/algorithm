/*
	07_trapping_rain_water.c
	========================
	
	Problem : Trapping Rain Water
	------------------------------
	Given n non-negative integers representing an elevation map where 
	the width of each bar is 1, compute how much water it is able 
	to trap after raining.

	Examples:
	========
	Input: arr[]   = {2, 0, 2}
	Output: 2
	Structure is like below
	| |
	|_|
	We can trap 2 units of water in the middle gap.

	Input: arr[]   = {3, 0, 0, 2, 0, 4}
	Output: 10
	Structure is like below
		 |
	|    |
	|  | |
	|__|_| 
	We can trap "3*2 units" of water between 3 an 2,
	"1 unit" on top of bar 2 and "3 units" between 2 
	and 4.  See below diagram also.

	Input: arr[] = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
	Output: 6
		   | 
	   |   || |
	_|_||_||||||
	Trap "1 unit" between first 1 and 2, "4 units" between
	first 2 and 3 and "1 unit" between second last 1 and last 2
	
*/

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define TRUE	1
#define FALSE	0


void print_array(int array[], int size)
{
    int index = 0;
    
    printf("Structure array : { ");
    while(size--)
    {
        printf("%d, ", array[index++]);
    }
    printf("}");
}

int max_col_value(int arr[], int size_of_array)
{
	int max = 0;
	int index = 0;
	
	while(size_of_array)
	{
		if(arr[index] > max)
			max = arr[index];
		
		index++;
		size_of_array--;
	}
	
	return max;	
}

int ** create_matrix(int row, int col)
{
	int i = 0, j = 0;
	int **matrix = NULL;
	
	matrix = (int **) malloc(row * sizeof(int *));
	
	for(i = 0; i < row; i++)
	{
		matrix[i] = (int *) malloc(col * sizeof(int));
		for(j = 0; j < col; j++)
		{
			matrix[i][j] = 1;	/* Fill whole matrix with water (1) */
		}
	}
	return matrix;
}

void init_matrix(int ** matrix, int arr[], int array_size, int max_height)
{
	int col = 0, row = 0;
	int col_height = 0;
	int col_threshold = arr[col];
	
	for(col = 0; col < array_size; col++)
	{
		if(arr[col] > col_threshold)
			col_threshold = arr[col];
		
		col_height = arr[col];
		if(col_height != 0)	/* Modify col which is non zero */
		{
			for(row = 0; row < col_height; row++)
			{
				matrix[row][col] = 0;	/* Mark the structure blocks as zero */
			}
		}
		
		for(row = col_threshold; row < max_height; row++)
		{
			matrix[row][col] = 0;	/* Mark the structure blocks as zero */
		}
	}
}

int calculate_units_of_water(int ** matrix, int row, int col)
{
	int units_of_water = 0;
	int i = 0, j = 0;

	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			if(matrix[i][j] == 1)
			{
				units_of_water++;
			}
		}
	}
	
	return units_of_water;
}

/* Sample arrays */
//int arr[] = {2, 0, 2};    // Output : 2
int arr[] = {3, 0, 0, 2, 0, 4};   // Output : 10
//int arr[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};   // Output : 6 - not yet working for this dataset

void main()
{
	int rain_water_trap = 0;
	int matrix_width = sizeof(arr) / sizeof(arr[0]);
	int matrix_height = max_col_value(arr, matrix_width); /* max column of the array */
	
	int ** matrix = create_matrix(matrix_height, matrix_width);
	
	/* Print structure array */
	print_array( arr, (sizeof(arr) / sizeof(arr[0])) );
	
	/* Initialize as per structure array */
	init_matrix(matrix, arr, matrix_width, matrix_height);
	
	/* Calculate amount of water trapped in blocks */
	rain_water_trap = calculate_units_of_water(matrix, matrix_height, matrix_width);
	
	printf("\nRain water captured in structure : %d", rain_water_trap);
	
}

