/******************************************************************************
    PriorityQueue_BinaryHeaps.c
	============================
	
	* PQ are based on Binary Trees. 
	* Binary tree : is "empty or node with links to left and right binary trees".
	* Complete Binary Tree : Perfectly balanced tree, except for the bottom 
		most level.
	
	* Height of "complete" Binary Tree => integer value of (log n) 	
										; where n - number of total nodes
										
	* Height of the tree increases only when number of nodes increases in the 
		order of 2^n
	
	Binary Tree Implementation using Array.
	---------------------------------------
	Key properties : 
	* Largest key is at a[1], which is root of the binary tree.
	* Parent of node at 'k' is at 'k/2'
	* Children of node at 'k' would be '2k' & '2k+1'

	Swim Operation : 
	--------------
	When key in child is bigger than the parent, its a voilation of basic heap sort algo. 
	And to fix it, we use the "SWIM" functionality.

	swim(int key)
	{	// checking if key's parent is less than key, if yes, then exchange the key and its parent values
		while( (key > 1) && less(k/2 , k) )		
		{
			exch(k, k/2);
			k = k/2;
		}	 
	}


	Item Insertion:
	--------------
	We insert an item at the end of the heap...ie. first empty slot of the array.
	And then apply swim(key) operation on that newly added node.


	Sink Operation : 
	--------------
	When key of parent somehow becomes less than its two children, 
	eg. say when we delete the max key (root) of the tree.
	Then this violation is corrected by the operation 'sink'. code is as follows : 
	
	sink(int k)
	{
		while(2*k <= N)
		{
			int j = 2 * k;	// go to first child
			if(j < N && less(j, j+1))		// children of parent k are 2k & 2k+1
				j++;
			
			// break out of loop if parent key is greater than child key
			if(! less(k, j))	
				break;
			
			// exchange keys of parent and (right side) child
			exch(k, j);
	
			// set new parent to exchanged child
			k = j;
		}
	}
	
	Delete Max Operation :  cost - at most (2 log N)
	--------------------
	Returns the root of the tree ie. the max key value of the tree. 
	Then exchange last entry of the heap array to root key, and then perform 
	a sink operation on root. 
	
	int delMax()
	{
		Key max = pq[1];

		exch(1, N--);
		sink(1);
		pq[N+1] = NULL;
		
		return max;		
	}
	
	
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

    printf("\nheap_array_current = %d", heap_array_current);
    printf("\nheap_array_size = %d", heap_array_size);
    
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

int main()
{
	int index = 1;	// Leave first index of array. Root key starts at index 1
	int temp_key_value = 0, top_key_value = -1;
	
	printf("Enter heap size : ");
	scanf("%d", &heap_array_size);
	
	heap_array = (int *) malloc( (heap_array_size + 1) * sizeof(int)); 
	
	for(index = 1; index <= heap_array_size; index++)
	{
		printf("Enter key item %d (decimal value) : ", index);
		scanf("%d", &temp_key_value);
		
		// Insert item at the end of the array
		insert(temp_key_value);
		
		// Adjust the key according to Binary Heap Sort policies
		swim(heap_array, index);
	}
	
	print_arr("After key insertion : ", heap_array, heap_array_size);
	
	// Get top key from array
	top_key_value = delMax(heap_array);
	printf("\nTop Key = %d", top_key_value);
	
	// Print final 
	print_arr("After Top Key sink : ", heap_array, heap_array_size);
	
	getch();
    return 0;
}
