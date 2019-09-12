/******************************************************************************
Count BST nodes that lie in a given range
=========================================

Given a Binary Search Tree (BST) and a range, count number of nodes that lie in 
the given range.

Examples:
--------
Input:
        10
      /    \
    5       50
   /       /  \
 1       40   100

Range: [5, 45]

Output:  3
There are three nodes in range, 5, 10 and 40


******************************************************************************/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <stdlib.h>

typedef int bool;
#define TRUE	1;
#define FALSE	0;

typedef struct bst
{
	int key;
	struct bst * left;
	struct bst * right;
}bst_t;

typedef struct linkedlist
{
	bst_t * key_node;
	struct linkedlist * next;
}linkedlist_t;

linkedlist_t * node_iterator = NULL;

linkedlist_t * create_new_linkedlist_node(bst_t * node)
{
	linkedlist_t * temp_node = NULL;
	temp_node = (linkedlist_t *)malloc(sizeof(linkedlist_t));
	if(temp_node)
	{
		temp_node->key_node = node;
		temp_node->next = NULL;
	}
	return temp_node;
}

void insert_in_queue(linkedlist_t **linked_list, bst_t * bst_node, int range_low, int range_high)
{
	linkedlist_t * temp_node = *linked_list;
	
	/* Do not add to iterator queue, if the key of node is out of range */
	if(bst_node->key < range_low || bst_node->key > range_high)
	    return;
	
	if(*linked_list == NULL)
	{
		*linked_list = create_new_linkedlist_node(bst_node);
	}
	else
	{
		while(temp_node->next != NULL)
			temp_node = temp_node->next;
		
		temp_node->next =  create_new_linkedlist_node(bst_node);
	}
}

void inorder_traversal(bst_t * tree_head, int range_low, int range_high)
{
	if(tree_head == NULL)
		return;
	
	inorder_traversal(tree_head->left, range_low, range_high);
	
	insert_in_queue(&node_iterator, tree_head, range_low, range_high);
	
	inorder_traversal(tree_head->right, range_low, range_high);
}

linkedlist_t * find_nodes_in_range(bst_t * tree_head, int range_low, int range_high)
{
	
	if(tree_head)
		inorder_traversal(tree_head, range_low, range_high);
	
	return node_iterator;
}

bst_t * create_new_node(int key)
{
	bst_t * bst_node = (bst_t *) malloc(sizeof(bst_t));
	if(bst_node)
	{
		bst_node->key = key;
		bst_node->left = NULL;
		bst_node->right = NULL;		
	}
	
	return bst_node;
}

void insert_in_bst(bst_t **tree_head, int key)
{
    int compare_val = 0;
    bst_t * temp_tree_head = *tree_head;
    
	if(*tree_head == NULL)
	{
		*tree_head = create_new_node(key);
	}
	else
	{
		compare_val = ( key - temp_tree_head->key );
		if(compare_val < 0)
			insert_in_bst( &temp_tree_head->left, key );
		else if(compare_val > 0)
			insert_in_bst( &temp_tree_head->right, key );
		else if(compare_val == 0)
			insert_in_bst( &temp_tree_head->right, key );
	}
	

}

/* V. NOTE: 
	In 'C' language, we have to pass array size in function parameters 
		(when passing array as parameter in function). 
		
	C Language treats array as pointer when passed as argument in function parameter.
	
	Either use actual array name (global array name to calculate array size) or Pass array size in function name.
	
#if 0
	void function(int *arr, int arr_size)
	{
		...
	}
#else
	int arr[] = {0,1,2,3};
	void function()
	{
		int size = sizeof(arr) /  sizeof(arr[0]);
		...
	}
#endif
*/
bst_t * insert_keys_in_bst(int keys[], int num_elements)
{
	int i = 0;
	bst_t * tree_head = NULL;

	for(i = 0; i < num_elements; i++)
	{
		insert_in_bst(&tree_head, keys[i]);
	}

	return tree_head;
}

void print_nodes(linkedlist_t * llNodes)
{
	printf("\n\rNode Keys : ");
	while(llNodes != NULL)
	{
		printf("%d ", llNodes->key_node->key);
		llNodes = llNodes->next;
	}	
}

int bst_keys[] = {10, 5, 50, 40, 100, 1};
void main()
{
	int range_start = 0, range_end = 0;
	int num_elements = sizeof(bst_keys) / sizeof(bst_keys[0]);
	linkedlist_t * llNodes = NULL;
	bst_t * tree_head = NULL;
	
	printf("\n\rEnter Range : ");
	scanf("%d %d", &range_start, &range_end);
	
	tree_head = insert_keys_in_bst(bst_keys, num_elements);
	
	llNodes = find_nodes_in_range(tree_head, range_start, range_end);
	
	print_nodes(llNodes);	
}