/******************************************************************************
    MergeSort.c
    
	Time Complexity = n * (log n)
	
*******************************************************************************/

#include <stdio.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

void sort(int * arr, int low, int high)
{
    
}

void mergesort(int * arr, int arr_size)
{
    int lo = 0;
    int hi = arr_size;
    int mid = (hi - lo) / 2;
    
    sort(arr, )

	
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

