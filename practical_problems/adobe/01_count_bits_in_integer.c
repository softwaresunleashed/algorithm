/******************************************************************************
    \practical_problems\adobe\01_count_bits_in_integer.c
	====================================================
	
	Count set bits in an integer
	----------------------------
	Write an efficient program to count number of 1s in binary representation 
	of an integer.
	
	Examples :

		Input : n = 6
		Output : 2
		Binary representation of 6 is 110 and has 2 set bits

		Input : n = 13
		Output : 3
		Binary representation of 13 is 1101 and has 3 set bits


	Approach 1 : Simple Method 					Time Complexity: (-)(logn) (Theta of logn)
	---------------------------
	1. Loop through all bits in an integer, check if a bit is set and if it is then increment the set bit count.
	
	
	Approach 2 :  Recursive Approach
	--------------------------------
	1. Recursive call function till n = 0, and return the count of 1+ on each iteration
	
	
	Approach 3 :  Brian Kernighan’s Algorithm				Time Complexity: O(log n)
	-----------------------------------------
	1. Subtracting 1 from a decimal number flips all the bits after the rightmost
	set bit(which is 1) including the rightmost set bit.
	
	for example :
		10 in binary is 00001010
		9 in binary is 00001001
		8 in binary is 00001000
		7 in binary is 00000111
	
	So if we subtract a number by 1 and do bitwise & with itself 
	(n & (n-1)), we unset the rightmost set bit. If we do n & (n-1) in a loop 
	and count the no of times loop executes we get the set bit count.
	
	The beauty of this solution is the number of times it loops is equal to the 
	number of set bits in a given integer.
	
	
	Approach 4 :  Map of numbers for a nibble			Time Complexity: O(1)
	-----------------------------------------
	1. Mapping numbers with the bit. It simply maintains a Map(or array) of 
		numbers to bits for a nibble. A Nibble contains 4bits. So we need an 
		array up to 15.

		int num_to_bits[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
		
	2. Now we just need to get nibbles of given long/int/word etc recursively.
	Storage Complexity: O(1) Whether given number is short, int, long or 
	long long we require array of 16 size only which is constant.
	
*******************************************************************************/
#include <stdio.h>
#include<time.h>
#include <stdlib.h> 

#define APPROACH 	4	/* Valid values : 1, 2, 3, 4 */


#if (APPROACH == 1)		/* Simple Loop And Compare Method */
#define MASK_LSb	0b1
int count_bits(int integer)
{
	int count = 0;
	
	while(integer)
	{
		if(integer & MASK_LSb)
		{
			count++;
		}
		
		integer = integer >> 1;		
	}

	return count;
}
#elif (APPROACH == 2)	/* Recursive Approach */
int count_bits(int integer)
{
    // base case
	if(integer == 0)
		return 0;
	
	 // if last bit set add 1 else add 0 
	return (integer & 1) + count_bits(integer >> 1);
}
#elif (APPROACH == 3)	/* Brian Kernighan’s Algorithm */
int count_bits(int integer)
{
	int count = 0;
	
	while(integer)
	{
		integer = integer & (integer - 1);
		count++;
	}
	
	return count;	
}
#elif (APPROACH == 4)	/* Map of numbers for a nibble */

/* Contains the map of 0-F (16 combos) of nibble bits. 
Use this hash-table to quickly get the count of 1's in the nibble value represented by the index.
Value of each index points to number of 1's in the bit field pattern */
#define MAX_NIBBLE_PATTERNS		16
int nibble_map[MAX_NIBBLE_PATTERNS] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

int count_bits(int integer)
{
	int count = 0;
	
	while(integer)
	{
		count += nibble_map[integer & 0xf];
		integer = integer >> 0x4;	// shift out the LSB nibble (4bits)
	}

	return count;
}
#endif


#define MAX_INTEGER_ARRAY       6500
int bit_to_count_array[MAX_INTEGER_ARRAY];
void init_array_with_random_integer()
{
    int i = 0;
    printf("\nInitializing array with random numbers");
    for (i = 0; i < MAX_INTEGER_ARRAY; i++) {
		printf(".");
        bit_to_count_array[i] = rand() % MAX_INTEGER_ARRAY + 1;
	}
	printf("Done\n");    
}

void main()
{
	int index = 0, integer = 0, count = 0;
	clock_t begin = 0, end = 0, iteration_run = 0, total_time = 0;
	int sizeofarray  = sizeof(bit_to_count_array) / sizeof(bit_to_count_array[0]);
	
	init_array_with_random_integer();
	
	while(sizeofarray > 0)
	{
		integer = bit_to_count_array[index++];
		
		
		// Mark beginning of algo 
    	begin = clock();
    	
    	// do some stuff here
    	count = count_bits(integer);
	    
	    // Mark end of algo 
	    end = clock();
	    
	    iteration_run = end - begin;
		printf("\nInput : %d \t\t Number of 1\'s : %d \t\t Time (in clocks) : %ld", integer, count, iteration_run);

		sizeofarray--;
		total_time += iteration_run;
	}
	
	printf("\nTotal Time (in clocks) : %ld", total_time);
}
