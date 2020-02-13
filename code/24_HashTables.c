/******************************************************************************
    HashTables.c
	=============

	Basic Plan : Save items in a key-indexed table (index is a function of key)
		index = fn(key);
		
	Hash function - Method of computing array index from key.
	
	
	
	
	
		
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0



int main()
{
	int num_pairs = 0;
	printf("Enter Number of Key-Value pairs : ");
	scanf("%d", &num_pairs);

	/* Initialize arrays of both keys and values */
	init_arrays(num_pairs);

	/* Insert Key Value pairs */
	if(key_arr != NULL && value_arr != NULL)
	{
	    // 13 inserts
		insert('S', 0);
		insert('E', 1);
		insert('A', 2);
		insert('R', 3);
		insert('C', 4);
		insert('H', 5);
		insert('E', 6);
		insert('X', 7);
		insert('A', 8);
		insert('M', 9);
		insert('P', 10);
		insert('L', 11);
		insert('E', 12);
	}
	
	printf("\n=====================================================================================");
	printf("\nRange count between key(%c) and key(%c) : %d", 'A', 'L', range_count('A', 'L'));
	printf("\nKeys between key(%c) and key(%c) : ", 'A', 'L');
	range_search('A', 'L');
	
	printf("\n=====================================================================================");
	printf("\nRange count between key(%c) and key(%c) : %d", 'B', 'Q', range_count('B', 'Q'));
	printf("\nKeys between key(%c) and key(%c) : ", 'B', 'Q');
	range_search('B', 'Q');
	
	printf("\n=====================================================================================");
	print_arr("Array after Insertions : ", key_arr, value_arr, key_value_pair_size);
	delete('S'); delete('P');
	print_arr("Array after Deletion   : ", key_arr, value_arr, key_value_pair_size);
	
	
	getch();
    return 0;
}
