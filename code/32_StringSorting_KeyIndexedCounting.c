/******************************************************************************
    32_StringSorting_KeyIndexedCounting.c
	===================================

	Key-indexed counting : assumption about keys
	
	Assumption - Keys are integers between 0 and R-1
	where R means Radix (Radix is the number of alphabets present in string models)
	e.g. String model 
		Decimal 		0123456789				Radix - 10
		Hex				0123456789ABCDEF		Radix - 16
		ASCII			256 ascii chars			Radix - 256
		
	Implication - Can use key as an array index for sorting
	
	Applications of Key Indexed Counting Algo :
	=========================================
	* Sort string by first letter
	* Sort class roster by section
	* Sort phone numbers by area code
	* Subroutine in a sorting algo
	
	Goal : 
	====
	Sort an array a[] of N integers below 0 and R-1
	
	Key Indexed Counting Algo : 
	=========================
	1) Count frequencies of each letter using key as index.
	2) Compute frequency cumulates which specify destinations.
	3) Access cumulates using key as index to move items.
	4) Copy back into original array.
	
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define DEBUG_ENABLE    0	/* Enable to print debug messages */


int input_array[] = {'d', 'a', 'c', 'f', 'f', 'b', 'd', 'b', 'f', 'b', 'e', 'a', 'x', 'y', 'z'};
#define RADIX_SIZE	26

void key_indexed_counting(int input_arr[], int count_arr[],  int aux_arr[], int input_arr_size )
{
	int index = 0;
	int input_arr_key = 0;
	int max_count_array_index = 0;
	int index_into_count_array = 0;
	int aux_index = 0;
	
	/* 1. Scan input_arr and populate count_arr[] (taking char as radix key into count array) */
	for(index = 0; index < input_arr_size; index++)
	{
		input_arr_key = input_arr[index] - 'a';
		count_arr[ input_arr_key + 1 ]++;   /* Store the key count offsetted by 1 */
		
		/* Keep a note of max index written into count array */
		if( (input_arr_key + 1) > max_count_array_index)
		    max_count_array_index = input_arr_key + 1;
	}
	
	/* 2. Update count array as "cumulates" */
	for(index = 0; index < max_count_array_index; index++)
	{
		count_arr[ index + 1 ] += count_arr[ index ];
	}
	
	/* 3. start placing keys in sorted manner in aux array, using input array & count array */
	for(index = 0; index < input_arr_size; index++)
	{
	    // Calculate index where to check in count array
	    index_into_count_array = input_arr[ index ] - 'a';   
	    
	    // This gives the index in aux array where to put the key (and increment next index to put key by 1)
	    aux_index = count_arr[ index_into_count_array  ]++;
		
		// Write the key from input array into aux array
		aux_arr[ aux_index ] = input_arr[ index ];
	}
	
}

void print_array_char(int arr[], int size)
{
	int index = 0;
	while(size)
	{
		printf("%c ", arr[index]);
		index++;
		size--;
	}
}

void print_array_int(int arr[], int size)
{
	int index = 0;
	while(size)
	{
		printf("%d ", arr[index]);
		index++;
		size--;
	}
}

void main()
{
	int size_of_input_arr = sizeof(input_array) / sizeof(input_array[0]);
	int * count_array = NULL;	/* Count Array (Size : Radix size + 1)*/
	int * aux_array = NULL;	/* Aux Array (Size : size of input array)*/
		
	/* Count array creation */
	count_array = (int *)malloc( ( RADIX_SIZE + 1 ) * sizeof( int ) );
	memset( count_array, 0, ( ( RADIX_SIZE + 1 ) * sizeof( int ) ) );
	
	/* Aux array creation */
	aux_array = (int *)malloc( size_of_input_arr * sizeof( int ) );
	memset( aux_array, 0, ( size_of_input_arr * sizeof( int ) ) );
	
	/* Print Input array */
	printf("\n\rInput Array : ");
	print_array_char(input_array, size_of_input_arr);
	
	/* Key Indexed Counting Algo - to sort keys based on characters */
	key_indexed_counting(input_array, count_array, aux_array, size_of_input_arr);
	
	/* Print Count array */
	printf("\n\rCount Array : ");
	print_array_int(count_array, ( RADIX_SIZE + 1 ) );
	
	/* Print Aux (Sorted) array */
	printf("\n\rSorted Aux Array : ");
	print_array_char(aux_array, size_of_input_arr );
}
