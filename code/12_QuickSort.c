/******************************************************************************
    QuickSort.c
	===========
    * Quick sort is in place sorting algo. 
	
	* Quick sort is not stable - meaning, that during partitioning there are long 
	range exchanges that may put a key with certain value over a key with certain 
	value (not checking both key and value pair before exchanging, so to say)
	
	
	Space complexity
	================
	Partitioning : Constant extra space.
	Depth of recursion : algorithmic extra space 
	
	Time Complexity (See presentation slides)
	===============
	Average --> n * (log n) 		~ 1.39 N log N (Mathematically derived)
	Worst case --> Quadratic 		~ 1/2 N^2
	
	Shuffling in the algo, provides a probabilistic guarantee against worst case.
	
	When not to use QuickSort
	=========================
	Might take quadratic time, if array is sorted (either ascending / descending)
	or if there are duplicates in array (even in randomized).
	
*******************************************************************************/

#include <stdio.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0



void quicksort(int * arr, int arr_size)
{

	
}

void print_arr(char * message, int * arr, int arr_size)
{
    int i = 0;
    printf("\n");
    printf(message);
    
    for(i = 0; i < arr_size; i++)
	{
		printf("%d  ", i);
	}	
}


int main()
{
	int num_elem = 0;
	int i = 0;
	char * parse_string = NULL;
	int * arr = NULL;
    printf("Enter Number of Elements : ");
	scanf("%d", &num_elem);
	
	arr = (int *) malloc(num_elem * sizeof(int));
	
	for(i = 0; i < num_elem; i++)
	{
		printf("\nEnter [%d] element : ", i);
		scanf("%d", &arr[i]);
	}	
	
	print_arr("Array before MergeSort :", arr, num_elem);
	
	mergesort(arr, num_elem);
	
	print_arr("Array after MergeSort :", arr, num_elem);
	
	getch();
    return 0;
}

