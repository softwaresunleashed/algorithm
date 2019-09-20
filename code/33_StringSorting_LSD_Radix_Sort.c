/******************************************************************************
    33_StringSorting_LSD_Radix_Sort.c
	===================================

	LSD (String) Radix Sort - Least Significant Digit 
	----------------------
	* Consider characters from right to left.
	* Stably sort using d'th character as key (using key-indexed counting).
	
	Time Complexity :
	---------------
	Guarantee - 2WN
	Random - 2WN
	Extra Space - N (Number of elements) + R (Radix)
	
	Stable : Yes
	
	Output : 
	------
	Input Array : dab cab fad bad dad ebb ace add fed bed fee bee                                                                                                                                         
	Sorted Aux Array : ace add bad bed bee cab dab dad ebb fad fed fee                                                                                                                                    

	
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define DEBUG_ENABLE    1	/* Enable to print debug messages */



#define RADIX_SIZE	26

void print_array_char(char *arr[], int size)
{
	int index = 0;
	while(size)
	{
		printf("%s ", arr[index]);
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

void key_indexed_counting( char * input_arr[], char * aux_arr[], int input_arr_size )
{
	int index = 0;
	int input_arr_key = 0;
	int max_count_array_index = 0;
	int index_into_count_array = 0;
	int aux_index = 0;
	int element_string_size = strlen(input_arr[0]);		/* Length of string of each element */
	int * count_arr = NULL; 

	while(element_string_size)
	{
		/* Count array - one for each string literal of element */
		count_arr = (int *)malloc( ( RADIX_SIZE + 1 ) * sizeof( int ) );
		memset( count_arr, 0, ( ( RADIX_SIZE + 1 ) * sizeof( int ) ) );
		
		/* 1. Scan input_arr and populate count_arr[] (taking char as radix key into count array) */
		for(index = 0; index < input_arr_size; index++)
		{
			input_arr_key = input_arr[index][element_string_size - 1] - 'a';
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

#if DEBUG_ENABLE	
    	/* Print Count array */
	    printf("\n\rCount Array (%d): ", (element_string_size - 1) );
	    print_array_int( count_arr, max_count_array_index );
#endif

        /* 3. start placing keys in sorted manner in aux array, using input array & count array */
		for(index = 0; index < input_arr_size; index++)
		{
			/* Calculate index where to check in count array */
			index_into_count_array = input_arr[ index ][element_string_size - 1] - 'a';   
			
			/* This gives the index in aux array where to put the key (and increment next index to put key by 1) */
			aux_index = count_arr[ index_into_count_array  ]++;
			
			/* Write the key from input array into aux array */
			strcpy(aux_arr[ aux_index ], input_arr[ index ]);
		}
		
		/* 4. copy aux array to input array */
		for(index = 0; index < input_arr_size; index++)
		{
			/* Write the key from input array into aux array */
			strcpy(input_arr[ index ], aux_arr[ index ]);
		}
		
		/* Move to left character */
		element_string_size--;
		free(count_arr);
	}
}

char * input_array[] = {"dab", "cab", "fad", "bad", "dad", "ebb", "ace", "add", "fed", "bed", "fee", "bee"};

void main()
{
    int i = 0;
	int size_of_input_arr = sizeof(input_array) / sizeof(input_array[0]);
	int size_of_element_string = strlen(input_array[0]);
	char ** aux_array = NULL;	/* Aux Array (Size : size of input array) */
    char ** inp_array = NULL;	/* Input Array (Size : size of input array) */
	
	/* Input Array Creation - copy contents from input sample array */
	inp_array = (char **)malloc( size_of_input_arr * sizeof( char * ) );
	for(i = 0; i < size_of_input_arr; i++)
	{
	    inp_array[i] = (char *) malloc( (size_of_element_string + 1) * sizeof(char) );
	    strcpy(inp_array[i], input_array[i]);
	}

	/* Aux array creation */
	aux_array = (char **)malloc( size_of_input_arr * sizeof( char * ) );
	for(i = 0; i < size_of_input_arr; i++)
	    aux_array[i] = (char *)malloc( (size_of_element_string + 1) * sizeof(char) );
	
	/* Print Input array */
	printf("\n\rInput Array : ");
	print_array_char(input_array, size_of_input_arr);
	
	/* Key Indexed Counting Algo - to sort keys based on characters */
	key_indexed_counting(inp_array, aux_array, size_of_input_arr);
	
	/* Print Aux (Sorted) array */
	printf("\n\rSorted Aux Array : ");
	print_array_char(aux_array, size_of_input_arr );
}
