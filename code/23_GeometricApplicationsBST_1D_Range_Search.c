/******************************************************************************
    GeometricApplicationsBST_1D_Range_Search.c
	========================================

	1-D Range Search
	----------------
	Extension of "ordered symbol table" (implemented via Array)
	* Insert Key-value pair
	* Search for key k
	* Delete key k
	* Range search : Find all keys between k1 & k2
	* Range count : number of keys between k1 & k2
	
	Application : Database queries
	
	
	
		
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

void delete(char key)
{
    int index_of_key = -1;
	if(!isEmpty())
	{
		/* Search for the index of key if already present */
		index_of_key = rank(key);
		if(index_of_key < key_value_pair_size && key_arr[index_of_key] == key)
		{
			while(index_of_key < key_value_pair_current)
			{
				key_arr[index_of_key] = key_arr[index_of_key + 1];
				value_arr[index_of_key] = value_arr[index_of_key + 1];
				index_of_key++;
			}
			key_value_pair_current--;
		}			
	}
}


/* Range search : Find all keys between k1 & k2 */	
void range_search(char lo_key, char hi_key)
{
	int rank_lo = rank(lo_key);
	int rank_hi = rank(hi_key);
	
	if(rank_lo  < rank_hi)
		while(rank_lo < rank_hi)
		{
			printf("%c, ", key_arr[rank_lo]);
			rank_lo++;
		}
}

/* Range count : number of keys between k1 & k2 */
int range_count(char lo_key, char hi_key)
{
	if( KEY_NOT_FOUND != get_value(hi_key))
		return rank(hi_key) - rank(lo_key) + 1;
	else
		return rank(hi_key) - rank(lo_key);
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
		printf("%c-%d   ", key_arr[i], value_arr[i]);
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
