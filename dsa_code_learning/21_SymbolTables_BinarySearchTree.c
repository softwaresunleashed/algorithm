/******************************************************************************
    SymbolTables_BinarySearchTree.c
	========================================

	* A BST is a binary tree. Implemented usually via Extended Linked List node.
	* Binary tree is either:
		- Empty
		- Two disjoint binary trees (left and right).
	* Symmetric Order : 
		- Each node has a key
		- Larger than all keys in its left subtree
		- Smaller than all keys in its right subtree
	* Each node comprises of 4 fields
		- Key
		- Value
		- reference to left subtree
		- reference to right subtree
	
	
	Differences from Heap Tree (using Arrays)
	==========================
	1) Heap tree all nodes on upper levels have key  values larger than lower nodes, 
	however, in BST the 'nodes on left are less than parent node', and all 'nodes on 
	the right of parent node are more than key of parent node'.
	
	
	
	Time complexity :
	---------------	
	get() : Number of compares = 1 + depth of node in tree
	
	put() : Number of compares = 1 + depth of node in tree 
	BST insert : Search for a key in BST tree. Two possibilities : 
		- Key in tree :: reset value with new one
		- Key not in tree :: add new node
	
	search() / insert() : number of compares => ~ 2 ln	N
	
	Expected Height : ~4.311 ln N
	Worst-case Height : N
	
	
	Remarks : 
	-------
	Tree shape of BST, depends on the order of keys as they come in. 
	Depending upon the way keys are entered the tree could be "balanced" , 
	"typical", or "worst case - where all nodes are right or left to its parent" 
	
	Ordered Operations on BST :
	=========================
	Minimum Key : Smallest key of BST (Left most "non-null" node's value)
	Maximum Key : Largest key of BST (Right most "non-null" node's value)
	Floor : Largest key less than or equal to a given key
	Ceiling : Smallest key greater than or equal to given key
	Rank : How many keys are less than key 'k'
	
	Finding Floor -
	Case 1) k equals key at root
		The floor of k is k itself
	Case 2) k is less than the key at root
		The floor of k is in the left subtree
	Case 3) k is greater than the key at root 
		The floor of k is in the right subtree (if there is any key less than 
		k in right subtree) otherwise it is the key in the root. 
		
		
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define ERROR_INVALID_VALUE     -5

typedef struct _bst_node 
{
	char key;
	int value;
	struct _bst_node * left_tree;
	struct _bst_node * right_tree;
	int size;
} bst_node_t;


bst_node_t * bst_root_node;

int compare(char key1, char key2)
{
	return (key1 - key2);
}

int size_node(bst_node_t * node)
{
	if(node == NULL)
		return 0;
	
	return node->size;
}

/* Returns Size of BST */
int size()
{
	return size_node(bst_root_node);
}

int rank_recursive(bst_node_t * node, char key)
{
	int compare_val = 0;
	
	if(node == NULL)
		return 0;
	
	compare_val = compare(key, node->key);
	if(compare_val < 0)
		return rank_recursive(node->left_tree, key);
	else if(compare_val > 0)
		return (1+ size_node(node->left_tree) + rank_recursive(node->right_tree, key));
	else if(compare_val == 0)
		return size_node(node->left_tree);
}

int rank(char key)
{
	return rank_recursive(bst_root_node, key);
}


bst_node_t * create_node(char key, int value)
{
	bst_node_t * new_node = malloc(sizeof(bst_node_t));
	if(new_node)
	{
		new_node->key = key;
		new_node->value = value;
		new_node->size = 1;
		new_node->left_tree = NULL;
		new_node->right_tree = NULL;
	}
	
	return new_node;
}



bst_node_t * put_recursive(bst_node_t * node, char key, int value)
{
	int compare_val = 0;
	bst_node_t * temp_node = node;
	
	if(temp_node == NULL)
		return create_node(key, value);

	compare_val = compare(key, temp_node->key);
	if(compare_val < 0)
		temp_node->left_tree = put_recursive(temp_node->left_tree, key, value);
	else if(compare_val > 0)
		temp_node->right_tree = put_recursive(temp_node->right_tree, key, value);
	else if(compare_val == 0)
		temp_node->value = value;
    
    // Store the size of node
	temp_node->size = 1 + size_node(temp_node->left_tree) + size_node(temp_node->right_tree);
	
	return temp_node;
}

/* Insert into BST - Binary Search Tree */
void put(char key, int value)
{
	bst_root_node = put_recursive(bst_root_node, key, value);
}


/* Get Value from BST for a specific Key */
int get(bst_node_t * bst_root_node, char key)
{
	bst_node_t * temp_node = bst_root_node;
	int comp_val = 0;

	while(temp_node != NULL)
	{
		comp_val = compare(key, temp_node->key);
		if(comp_val < 0)
		{
			temp_node = temp_node->left_tree;
		}	
			else if(comp_val > 0)
		{
			temp_node = temp_node->right_tree;
		}
		else if(comp_val == 0)
		{
			return temp_node->value;
		}
	}
	return ERROR_INVALID_VALUE;
}

/* Smallest key of BST (Left most "non-null" node's value) */
char minimum_key(bst_node_t * bst_root_node)
{
	bst_node_t * iterator = bst_root_node;
	
	if(iterator)
	{
		while(iterator->left_tree != NULL)
			iterator = iterator->left_tree;
		
		return iterator->key;	
	}
	else
	{
		return 0;
	}
}

/* Largest key of BST (Right most "non-null" node's value)*/
char maximum_key(bst_node_t * bst_root_node)
{
	bst_node_t * iterator = bst_root_node;
	
	if(iterator)
	{
		while(iterator->right_tree != NULL)
			iterator = iterator->right_tree;
		
		return iterator->key;	
	}
	else
	{
		return 0;
	}
}

/* Floor : Largest key less than or equal to a given key */
char bst_floor(bst_node_t * bst_root_node)
{
	/* TODO : Implementation pending */

}

/* Ceiling : Smallest key greater than or equal to given key */
char bst_ceiling(bst_node_t * bst_root_node)
{
	/* TODO : Implementation pending */
}
	
/* Delete a node with specific key */
void delete(bst_node_t * bst_root_node, char key)
{
	/* TODO : Implementation pending */
	
}

void inorder_traversal(bst_node_t * bst_root_node)
{
	if(bst_root_node == NULL)
		return;
	inorder_traversal(bst_root_node->left_tree);
	printf("%c ", bst_root_node->key);
	inorder_traversal(bst_root_node->right_tree);	
}


int main()
{
	// 13 inserts into Binary Search Tree
	put('S', 0);
	put('E', 1);
	put('A', 2);
	put('R', 3);
	put('C', 4);
	put('H', 5);
	put('E', 6);
	put('X', 7);
	put('A', 8);
	put('M', 9);
	put('P', 10);
	put('L', 11);
	put('E', 12);
	
	printf("\n===================================================");
	printf("\nSmallest Key : %c", minimum_key(bst_root_node));
	printf("\nLargest Key  : %c", maximum_key(bst_root_node));
	//	printf("\nFloor Key : %c", bst_floor(bst_root_node));
	//	printf("\nCeiling Key : %c", bst_ceiling(bst_root_node));
	printf("\n===================================================");
	printf("\nSize of BST : %d", size());
	printf("\n===================================================");
	printf("\nRank of Key (%c) : %d", 'S' ,rank('S'));
	printf("\nRank of Key (%c) : %d", 'X' ,rank('X'));
	printf("\nRank of Key (%c) : %d", 'N' ,rank('N'));
	printf("\n===================================================");
	printf("\nInorder Traversal : Keys in Acending order => \n");
	inorder_traversal(bst_root_node);
	printf("\n===================================================");
	
	getch();
    return 0;
}

