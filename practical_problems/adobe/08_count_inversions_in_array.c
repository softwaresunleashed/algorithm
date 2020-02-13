/*
	08_count_inversions_in_array.c
	==============================
	
	Problem : Count Inversions in an array
	--------------------------------------
	Inversion Count for an array indicates – how far (or close) the array is from being sorted. 
	If array is already sorted then inversion count is 0. If array is sorted in reverse order that 
	inversion count is the maximum.
	
	Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j

	Example:
	The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
	
	METHOD 1 (Simple) : Time Complexity: O(n^2)
	-------------------------------------------
	For each element, count number of elements which are on right side of it and are smaller than it.
	
	
	METHOD 2(Enhance Merge Sort)	--> Not implemented
	---------------------------------------------------
	Suppose we know the number of inversions in the left half and right half of the array (let be inv1 and inv2), 
	what kinds of inversions are not accounted for in Inv1 + Inv2? 
	The answer is – the inversions we have to count during the merge step. 
	Therefore, to get number of inversions, we need to add number of inversions in left subarray, right subarray and merge().
	
*/

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define TRUE	1
#define FALSE	0

#define ENABLE_DEBUG    1


#define METHOD	1		// Valid Values : 1,

int input_arr[] = { 1, 20, 6, 4, 5 }; 

#if (METHOD == 1)	/* Simple Approach */

typedef struct inversion_pairs
{
	int element1;
	int element2;
}inversion_pairs_t;


inversion_pairs_t * find_array_inversions(int arr[], int size)
{
	inversion_pairs_t * inversion_pair_arr = (inversion_pairs_t *)malloc(size * size * sizeof(inversion_pairs_t));	/* Max combos possible = size * size */
	int i = 0, j = 0;
	int pair_index = 0;
	
	for(i = 0; i < size; i++)
	{
		for(j = i+1; j < size; j++)
		{
#if ENABLE_DEBUG		    
			printf("\nchecking (%d , %d) : ", arr[i], arr[j]);
#endif
			if(arr[i] > arr[j])
			{
#if ENABLE_DEBUG
				printf("yes");
#endif
				/* Add to pair array */
				inversion_pair_arr[pair_index].element1 = arr[i];
				inversion_pair_arr[pair_index].element2 = arr[j];
				pair_index++;
			}
			else
			{
#if ENABLE_DEBUG			    
				printf("no");
#endif
			}
		}
	}
	
	/* Mark end of array by writing -1 to elements */
	inversion_pair_arr[pair_index].element1 = -1;
	inversion_pair_arr[pair_index].element2 = -1;
	
	return inversion_pair_arr;
}
#endif      /* METHOD == 1 */



void printf_array_int(int array[], int size)
{
	int i = 0;
	
	for(i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
}

void printf_inversion_array(inversion_pairs_t ip_array[])
{
	int index = 0;
	
	while(ip_array[index].element1 != -1 && ip_array[index].element2 != -1)
	{
		printf("(%d,%d) ", ip_array[index].element1, ip_array[index].element2);
		index++;
	}	
}


void main()
{
	int array_size = sizeof(input_arr) / sizeof(input_arr[0]);
	inversion_pairs_t * ip_array = NULL;
	
	printf("\nInput array : ");
	printf_array_int(input_arr, array_size);
	
	ip_array = find_array_inversions(input_arr, array_size);
	
	printf("\nInversion arrays : ");
	printf_inversion_array(ip_array);
	
}

