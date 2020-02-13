/*
	09_mirror_tree.c
	================
	
	Problem : Convert a Binary Tree into its Mirror Tree
	----------------------------------------------------
	Mirror of a Tree: Mirror of a Binary Tree T is another Binary Tree M(T) 
	with left and right children of all non-leaf nodes interchanged.
	
	-------------------------------
		1			|		1
       / \			|      / \
      3	  2			|     2   3
         / \		|    / \
		5	4		|   4   5
	------------------------------

	Trees in the above figure are mirror of each other.

    Tree (Inorder Traversal) : 3 1 5 2 4
    Mirror Tree (Inorder Traversal) : 4 2 5 1 3
	
	Method 1 (Recursive)
	--------------------
	Time & Space Complexities: This program is similar to traversal of tree 
	space and time complexities will be same as Tree traversal
	------------------------
	(1)  Call Mirror for left-subtree    i.e., Mirror(left-subtree)
	(2)  Call Mirror for right-subtree  i.e., Mirror(right-subtree)
	(3)  Swap left and right subtrees.
			  temp = left-subtree
			  left-subtree = right-subtree
			  right-subtree = temp
	
	Method 2 (Iterative)
	--------------------
	The idea is to do a Level Order (BFS) tree traversal, and keep pushing nodes into a queue.
	Now, While de-queuing nodes from queue, swap left and right children of every node.

	
*/

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define TRUE	1
#define FALSE	0

#define ENABLE_DEBUG    1

#define METHOD_POST_ORDER_TRAVERSAL_n_SWAP	1
#define METHOD_BFS_n_QUEUE	                2
/* Valid Values : METHOD_POST_ORDER_TRAVERSAL_n_SWAP, METHOD_BFS_n_QUEUE */
#define METHOD				METHOD_BFS_n_QUEUE


typedef struct tree_node
{
	int key;
	struct tree_node * left;
	struct tree_node * right;
}tree_node_t;

tree_node_t * create_tree_node(int key)
{
	tree_node_t * temp_tree_node = (tree_node_t *) malloc(sizeof(tree_node_t));
	
	if(temp_tree_node)
	{
		temp_tree_node->key = key;
		temp_tree_node->left = NULL;
		temp_tree_node->right = NULL;
		return temp_tree_node;
	}

	return NULL;
}

tree_node_t * create_tree()
{
	/*-------------------------------
		Orig Tree	|	Mirror Tree
		1			|		1
       / \			|      / \
      3	  2			|     2   3
         / \		|    / \
		5	4		|   4   5
	------------------------------*/
	tree_node_t * tree_root = create_tree_node(1);	/* Insert root node*/

	/* Left and right of node (1) */
	tree_root->left = create_tree_node(3);
	tree_root->right = create_tree_node(2);
	
	/* Left and right of node (2) */
	tree_root->right->left = create_tree_node(5);
	tree_root->right->right = create_tree_node(4);
	
	return tree_root;
}

void inorder_traversal(tree_node_t * tree)
{	
	if(tree == NULL)
		return;
	
	inorder_traversal(tree->left);
	
	/* Print node as per inorder traversal */
	printf("%d ", tree->key);
	
	inorder_traversal(tree->right);	
}

#if (METHOD == METHOD_POST_ORDER_TRAVERSAL_n_SWAP)

void postorder_traversal_and_swap(tree_node_t * tree)
{
	tree_node_t * temp_node = NULL;
	
	if(tree == NULL)
		return;
	
	/* Traverse to left tree (recursively */
	postorder_traversal_and_swap(tree->left);
	
	/* Traverse to right tree (recursively */
	postorder_traversal_and_swap(tree->right);
	
	/* When mid node is reached , swap left <--> right child */
	temp_node = tree->left;
	tree->left = tree->right;
	tree->right = temp_node;
}	
#endif

#if (METHOD == METHOD_BFS_n_QUEUE)

typedef struct linkedlist
{
	tree_node_t * node;
	struct linkedlist * next;
} linkedlist_t;

linkedlist_t * create_new_node(tree_node_t * tree_node)
{
	linkedlist_t * queue_node = NULL;

	queue_node = (linkedlist_t *)malloc(sizeof(linkedlist_t));
	queue_node->node = tree_node;
	queue_node->next = NULL;
	
	return queue_node;
}

/* Global pointer to queue 
(used to hold nodes of tress after bfs traversal) */
linkedlist_t * queue = NULL;

void enqueue_item(tree_node_t * tree_node)
{
	if(queue == NULL)
	{
		/* Check if queue is empty, then create a new one */
		queue = create_new_node(tree_node);
	}
	else
	{
		/* Check if queue is non-empty, then Traverse till end of the list */
		while(queue->next != NULL)
			queue = queue->next;
		
		queue->next = create_new_node(tree_node);
	}
}

void bfs_and_queue(tree_node_t * tree)
{
	if(tree == NULL)
		return;

	/* Enqueue node that is reached */
	enqueue_item(tree);
#if ENABLE_DEBUG
    printf("\nEnquing Item : %d", tree->key);
#endif

	/* Now traverse left and right trees recursively */
	bfs_and_queue(tree->left);
	bfs_and_queue(tree->right);
}

void iterate_queue_and_swap_nodes(linkedlist_t * queue, tree_node_t * tree)
{
	tree_node_t * temp_node = NULL; 
	
	while(queue->next != NULL)
	{
		/* pull out tree node from queue */
		temp_node = queue->node;
		
		/* Swap left and right child nodes */
		temp_node = tree->left;
		tree->left = tree->right;
		tree->right = temp_node;
		
		/* Move to next node */
		queue = queue->next;
	}
}
#endif

tree_node_t * mirror_tree(tree_node_t * tree)
{

#if (METHOD == METHOD_POST_ORDER_TRAVERSAL_n_SWAP)
	postorder_traversal_and_swap(tree);
#elif (METHOD == METHOD_BFS_n_QUEUE)
	bfs_and_queue(tree);
	iterate_queue_and_swap_nodes(queue, tree);
#endif

	return tree;	
}

void main()
{
	tree_node_t * tree = create_tree();
	
	printf("\nTree (Inorder Traversal) : ");
	inorder_traversal(tree);
	
	/* Mirror Tree */
	mirror_tree(tree);
	
	printf("\nMirror Tree (Inorder Traversal) : ");
	inorder_traversal(tree);
}
