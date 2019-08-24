/******************************************************************************
    PriorityQueue_HeapSort.c
	=========================
	Construct a MAX-Binary heap (Max key value is at root node), and then 
	recursively pull out max key from root node and exchange it current_array_index.
	
	Initially current_array_index points to array_size and gets reduced by one with every pull out of max key value.
	
	HeapSort : In-place sorting algo which takes (N log N) time.
	
	Timing Complexity
	=================
		Heap construction uses (less than) 2N compares and exchanges
		Heap Sort uses (less than) 2N log N compares and exchanges
		
		Best : N log N
		Worst / Average : 2N log N
		

	Significance : In-place algo, with N log N worst-case
	------------
	MergeSort : no, linear extra space required
	QuickSort : no, quadratic time in worst case
	HeapSort : yes
	
	Bottom line : HeapSort is optimal for both time and space. 
	-----------
		But its not used so heavily. Why? See below :-
			* Inner loop longer than quicksort's
			* Make poor use of cache memory (cuz references to data is all over 
						the memory and not limited to subsequent memory locations)
			* NOT STABLE!!! (does long distance exchanges, and hence can result in key imbalance among sub tree)
	
	
	
	
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0


/* Heap data structures */
int * heap_array = NULL;
int heap_array_size = 0;
int heap_array_current = 1;

int get_current_index()
{
    return heap_array_current;
}

void print_arr(char * message, int * arr, int arr_size)
{
    int i = 0;
    printf("\n");
    printf("%s",message);
    
    for(i = 0; i <= arr_size; i++)
	{
		printf("%d  ", arr[i]);
	}	
}

bool less(int value_1 , int value_2)
{
	return (value_1 < value_2) ? TRUE : FALSE;
}

void exch(int * array, int key_1, int key_2)
{
	int temp = 0;
	
	if(array != NULL)
	{
		temp = array[key_1];
		array[key_1] = array[key_2];
		array[key_2] = temp;
	}
}

void swim(int * heap_array, int key)
{	
	int key_parent = key / 2;
	
	/* checking if key's parent is less than key, 
		if yes, then exchange the key and its parent values */ 
	while( (key > 1) && less(heap_array[key_parent] , heap_array[key]) )		
	{
		exch(heap_array, key, key_parent);
		key = key_parent;
	}	 
}

void insert(int key)
{
	heap_array[heap_array_current] = key;
	heap_array_current++;
}

void sink(int * heap_array, int key)
{
    int j = 0;
    int local_key = key;
    
	// check if child of parent is within array bounds
	while( (2*local_key) <= heap_array_size)	
	{
		j = 2 * local_key;	// go to first child
		
		// check if first child's key is less than right child.
		// intention is to pick child with higher key value
		if(j < heap_array_size && less(heap_array[j], heap_array[j+1]))		// children of parent k are 2k & 2k+1
			j++;
		
		// break out of loop if parent key is greater than child key
		if( less(heap_array[local_key], heap_array[j]) )	
		{
		    // exchange keys of parent and child
		    exch(heap_array, local_key, j);
		    // set new parent to exchanged child
		    local_key = j;
		}
		else
		{
		    break;
		}
	}
}

int delMax(int * heap_array)
{
	int max_key_value = heap_array[1];

	exch(heap_array, 1, heap_array_size);	// exchange last entry with top of heap tree (index = 1).
	heap_array[heap_array_size] = 0;	    // make last entry null / invalid (zero in this case)
	heap_array_current--;
	heap_array_size--;						// reduce heap size by one
	
	// the root key after exchange would be a misfit. sink it to its apt position.
	sink(heap_array, 1);

	return max_key_value;		
}

// Sample data set
// 34  30  29  27  25  17  16  19  22  24
void heapsort(int * heap_array, int arr_size)
{
    int top_key_value = -1;
    int local_arr_size = arr_size;
    
	while(local_arr_size)
	{
		// Get top key from array
		top_key_value = delMax(heap_array);
		heap_array[local_arr_size] = top_key_value;
		local_arr_size--;
	}
}

void input_heap_keys(int heap_array_size)
{
    int index = 1;	// Leave first index of array. Root key starts at index 1
    int temp_key_value = 0;
    
    // Initialize array's memory
    heap_array = (int *) malloc( (heap_array_size + 1) * sizeof(int)); 
	
	// Input Binary Heap array key values 
	for(index = 1; index <= heap_array_size; index++)
	{
		printf("Enter key item %d (decimal value) : ", index);
		scanf("%d", &temp_key_value);
		
		// Insert item at the end of the array
		insert(temp_key_value);
		
		// Adjust the key according to Binary Heap Sort policies
		swim(heap_array, index);
	}
}

int main()
{
	int local_current_size = 0;
	
	printf("Enter heap size : ");
	scanf("%d", &heap_array_size);
	
	// Take input keys from user
	input_heap_keys(heap_array_size);
	
	// Print Array before Heap Sort
	print_arr("After key insertion : ", heap_array, heap_array_size);
	
	// Get current index after insertions
	local_current_size = get_current_index() - 1;
	
	// Perform Heap Sort
	heapsort(heap_array, heap_array_size);
	
	// Print final after Heap Sort
	print_arr("After Heap Sort (Sorted Array) : ", heap_array, local_current_size);
	
	getch();
    return 0;
}
