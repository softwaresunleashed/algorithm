/******************************************************************************
Merge two BSTs with limited extra space
=======================================
Given two Binary Search Trees(BST), print the elements of both BSTs in sorted 
form. The expected time complexity is O(m+n) where m is the number of nodes in 
first tree and n is the number of nodes in second tree. 

Maximum allowed auxiliary space is O(height of the first tree + height of 
the second tree).

Examples : 

-----------------------------------------------------
First BST 
       3
    /     \
   1       5
Second BST
    4
  /   \
2       6
Output: 1 2 3 4 5 6


-----------------------------------------------------

First BST 
          8
         / \
        2   10
       /
      1
Second BST 
          5
         / 
        3  
       /
      0
Output: 0 1 2 3 5 8 10 
-----------------------------------------------------


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
	struct bst *left;
	struct bst *right;
} bst_t;

bst_t * create_new_bst_node(int key)
{
	bst_t * temp_node = NULL;
	temp_node = (bst_t *) malloc(sizeof(bst_t));
	if(temp_node)
	{
		temp_node->key = key;
		temp_node->left = NULL;
		temp_node->right = NULL;
	}

	return temp_node;	
}

int less(int k1, int k2)
{
	int result = k1 - k2;

	if(result < 0)
		return -1;
	else if(result > 0)
		return 1;
	else if(result == 0)
		return 0;	
}

void merge_two_bst_extra_space(int array1[], int array2[], int merged_array[])
{
    int arr1_i = 1, arr2_j = 1, mergarr_k = 1;
    int i = 0, compare_val = 0;
	merged_array[0] = array1[0] + array2[0]; /* Size of merged array */
	
	for(i = 1; i <= merged_array[0]; i++)
	{
	    
		/* If one of the array has been exhausted, 
			then copy elements of other array(already sorted to 
			the merge array 
		*/
		if(arr1_i > array1[0])
		{
		    while(arr2_j <= array2[0])
                merged_array[mergarr_k++] = array2[arr2_j++];
		   break;
		}
		else if(arr2_j > array2[0])
		{
            while(arr1_i <= array1[0])
                merged_array[mergarr_k++] = array1[arr1_i++];
		   break;
		}
	    
		/* 
			Compare value of keys from two sorted arrays, 
			and take the lesser one and add to merge array 
		*/
	    compare_val = less(array1[arr1_i], array2[arr2_j]);
	    if( compare_val < 0 )
	    {
	        merged_array[mergarr_k++] = array1[arr1_i++];
	    }
	    else if( compare_val > 0 )
	    {
	        merged_array[mergarr_k++] = array2[arr2_j++];
	    }
	    else
	    {
	        /* if both keys are equal, add two entries */
	        merged_array[mergarr_k] = merged_array[mergarr_k + 1] = array1[arr1_i];
	        
	        arr1_i++;
	        arr2_j++;
	        mergarr_k = mergarr_k + 2;
	    }
	}
}

int compare(int k1, int k2)
{
	return less(k1, k2);
}

bst_t * insert_key_recursive(bst_t * node, int key)
{
	bst_t * node_to_insert = NULL;
	int compare_val = 0;
	
	if(node == NULL)
		return create_new_bst_node(key);
	
	compare_val = compare(key, node->key);
	if(compare_val < 0)
	{
		node_to_insert = insert_key_recursive(node->left, key);
		node->left = node_to_insert;
	}
	else if(compare_val > 0)
	{
		node_to_insert = insert_key_recursive(node->right, key);
		node->right = node_to_insert;
	}
	else if(compare_val == 0)
	{
		node_to_insert = insert_key_recursive(node->right, key);	// Keys are equal then store the node on right side (not on left)
		node->right = node_to_insert;
	}

	return node;
}

bst_t * insert_key(bst_t * bst_root, int key)
{
	bst_t * root = insert_key_recursive(bst_root, key);
	return root;
}

bst_t * create_bst(int bst_array[])
{
	int i = 0;
	int bst_size = bst_array[0];
	bst_t * new_tree = NULL;

	/* Start inserting keys from index 1,
		Index 0 is used to define number of entries in tree */
	for(i = 1; i <= bst_size; i++)
	{
	    printf("%d..", bst_array[i]);
		new_tree = insert_key(new_tree, bst_array[i]);
	}
	
	return new_tree;
}


/* =============== Array Insertion logic =========== */
static int array_index = 0;
void reset_array_index()
{
    array_index = 1;
}

void write_to_array(int array[], int key)
{
    array[array_index++] = key;
}
/* ================================================= */

void insert_array_sorted(bst_t * node, int array[])
{
	if(node == NULL)
		return;
	
	insert_array_sorted(node->left, array);
	write_to_array(array, node->key);
	insert_array_sorted(node->right, array);
}

void inorder_traversal_recursive(bst_t * node)
{
	if(node == NULL)
		return;
	
	inorder_traversal_recursive(node->left);
	printf("%d ", node->key);		// Print key at node
	inorder_traversal_recursive(node->right);
}

void print_bst_inorder(bst_t * tree_node)
{
	if(tree_node == NULL)
	{
		printf("\nTree is Empty");
		return;
	}	
	else
	{
		inorder_traversal_recursive(tree_node);
	}
}

int combined_array_size(int array1[], int array2[])
{
    return array1[0] + array2[0];
}

void print_array(int array[], int array_size)
{
    int i = 0;
    for(i = 1; i <= array_size; i++)
    {
        printf("%d..", array[i]);
    }
}

#if 0	/* Sample BST */
/* First element is the number of nodes in bst */
int bst1_array[] = {/* BST size */ 3, 3, 1, 5};
int bst2_array[] = {/* BST size */ 3, 2, 4, 6};
#else
int bst1_array[] = {/* BST size */ 4, 8, 2, 1, 10};
int bst2_array[] = {/* BST size */ 3, 5, 3, 0};	
#endif

void main()
{
	bst_t * tree1 = NULL;
	bst_t * tree2 = NULL;
	bst_t * merged_tree = NULL;
	
	int size_merged_tree = combined_array_size(bst1_array, bst2_array) + 1; /* one for size of merged array */
	int * merged_array = (int *)malloc(size_merged_tree * sizeof(int));
	
	printf("\n\r=========================================================");
	/* Create BST from two sample data */
	printf("\n\rInserting keys in Tree 1 : ");
	tree1 = create_bst(bst1_array);
	printf("\n\rInserting keys in Tree 2 : ");
	tree2 = create_bst(bst2_array);
    printf("\n\r=========================================================");
    
	/* Print sample BST */
	printf("\n\rContents of Tree 1 : ");
	print_bst_inorder(tree1);
	printf("\n\rContents of Tree 2 : ");
	print_bst_inorder(tree2);
    printf("\n\r=========================================================");
    
    printf("\n\rInserting contents of Tree 1 into Array : ");
    reset_array_index();
    insert_array_sorted(tree1, bst1_array);
    print_array(bst1_array, bst1_array[0]);
    printf("\n\rInserting contents of Tree 2 into Array : ");
    reset_array_index();
    insert_array_sorted(tree2, bst2_array);
    print_array(bst2_array, bst2_array[0]);
    printf("\n\r=========================================================");
    
	merge_two_bst_extra_space(bst1_array, bst2_array, merged_array);
    printf("\n\rContents of Merged Array : ");
	print_array(merged_array, merged_array[0]);
    printf("\n\r=========================================================");
}

