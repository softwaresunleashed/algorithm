/******************************************************************************
    SymbolTables_BinarySearch.c
	========================================
	* Implemented via "Ordered" Array.
	* Maintain an ordered array of key-value pairs
	* Good for scenarios where lots of searches [O(log N)] are involved, rather than insertions [O(N or N/2)]
	
	Data Structure : 
	--------------
	Maintain two ordered arrays, one to hold keys and one to hold values (ordered).
	ie. keys[] & vals[]
	
	Rank Helper Function - rank() : returns How many keys are less than 'k'
	
	Pseudo Code : 
	Value get(Key key)
	{
		if(isEmpty())
			return null;
		
		int i = rank(key);
		if(i < N && keys[i].compareTo(key) == 0)
			return vals[i];
		else
			return null;
	}
	
	int rank(Key key)
	{
		int lo = 0, hi = N-1;
		while(lo <= hi)
		{
			int mid = lo + (hi-lo)/2;
			int cmp = key.compareTo(keys[mid]);
			
			if(cmp < 0)
				hi = mid - 1;
			else if (cmp > 0) 
				lo = mid + 1;
			else if (cmp == 0)
				return mid;
		}
		return lo;		
	}
	
	Problem with Binary Search (using arrays) : 
	------------------------------------------
	To insert a new key in-between, all the right hand side items have to be moved to right for both key and value array.

	
	Time complexity :
	---------------	
	----------------------------------------------------------------
						||	worst case			||		average case
	----------------------------------------------------------------
						||	search	| insert	||	search	| insert
	----------------------------------------------------------------
	Binary Search		||	log N	|  	N		||	log N	|	N/2 
	----------------------------------------------------------------

*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define EMPTY_ARRY		-1
#define KEY_NOT_FOUND	-2

/* Sample Key Value Pair */
/* S0, E1, A2, R3, C4, H5, E6, X7, A8, M9, P10, L11, E12 */

char * key_arr;
int  * value_arr;
int  key_value_pair_size;
int  key_value_pair_current;

int compare(char key1, char key2)
{
    /* Subtract key2 from key1, 
        returns +ve if key1 is greater than key2,
        returns -ve if key1 is less than key2,
        returns 0 if key1 is equal to key2 */
    return key1-key2;
}

/* Find rank using binary search algo */
int rank(char key)
{
	int lo = 0, hi = key_value_pair_current-1, result = 0;
	int mid = 0;
	
	while(lo <= hi)
	{
	    // This is very important formula...don't miss "lo+" term, 
	    // else it would be Problem during right side of array
	    mid = lo + ((hi - lo)/2);               
		result = compare(key, key_arr[mid]);
		if(result < 0)
			hi = mid - 1;
		else if(result > 0)
			lo = mid + 1;
		else if(result == 0)
			return mid;
	}
	return lo;	
}

bool isEmpty()
{
	return (key_value_pair_current == 0) ? TRUE : FALSE;
}

int get_value(char key)
{
	int index_of_key = 0;
	
	if(isEmpty())
		return EMPTY_ARRY;
	
	index_of_key = rank(key);
	if(index_of_key < key_value_pair_size && key_arr[index_of_key] == key)
		return value_arr[index_of_key];
	else
		return KEY_NOT_FOUND;
}

void insert(char key, int value)
{
    int index_of_key = -1;
    int mtr_index = -1;

	if(isEmpty())
	{
		// First key-value pair goes to zeroth index
		key_arr[0] = key;
		value_arr[0] = value;
		key_value_pair_current++;
	}
	else
	{
		/* Search for the index of key if already present */
		index_of_key = rank(key);
		if(index_of_key < key_value_pair_size && key_arr[index_of_key] == key)
		{
			/* Key is present, just modify its value */
			value_arr[index_of_key] = value;
		}
		else
		{
			/* Key not present, but index_of_key represents the insertion point. Move all others to right */
			for(mtr_index = key_value_pair_current-1; mtr_index >= index_of_key; mtr_index-- )
			{
				key_arr[mtr_index+1] = key_arr[mtr_index];
				value_arr[mtr_index+1] = value_arr[mtr_index];
			}
			key_arr[index_of_key] = key;
			value_arr[index_of_key] = value;
			key_value_pair_current++;
		}		
	}	
}

void init_arrays(int num_pairs)
{
	key_arr = (char *)malloc(num_pairs * sizeof(char));
	value_arr = (int *)malloc(num_pairs * sizeof(int));
	key_value_pair_size = num_pairs;
}

void print_arr(char * message, char * key_arr, int * value_arr, int arr_size)
{
    int i = 0;
    printf("\n");
    printf("%s",message);
    
    for(i = 0; i < arr_size; i++)
	{
		printf("\nKey :%c     Value : %d  ", key_arr[i], value_arr[i]);
	}	
}

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
	
	print_arr("Array after Insertions", key_arr, value_arr, key_value_pair_size);
	
	getch();
    return 0;
}
