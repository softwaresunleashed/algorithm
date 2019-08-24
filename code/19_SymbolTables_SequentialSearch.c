/******************************************************************************
    SymbolTables_SequentialSearch.c
	========================================
	* Implemented via "Unordered" Linked List.
	
	Data Structure : 
	Maintain a (un-ordered ie. not in ascending / descending order) linked list to store key-value pair
	
	Search : 
	------
	Scan through all entries till you find a match (or null if not found).
	
	Insert : 
	------
	Scan through all entries of LL until a match is found, else insert at front.
	
	Time complexity :
	---------------
	
	----------------------------------------------------------------
						||	worst case			||		average case
	----------------------------------------------------------------
						||	search	| insert	||	search	| insert
	----------------------------------------------------------------
	Sequential Search	||	  N		|  	N		||	N/2		|	N 
	(un-ordered LL)		||			|			||			|		
	----------------------------------------------------------------
	
	
	
	
	
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct _node
{
	char key;
	int data;
	struct _node * next;
} node_t;



node_t * create_node(char key, int value)
{
	node_t * new_node = NULL;
	new_node = (node_t *)malloc(sizeof(node_t));
	if(new_node)
	{
		new_node->key = key;
		new_node->data = value;
		new_node->next = NULL;
	}
	return new_node;
}

/* Return node pointer with key , else return NULL */
node_t * search(node_t * head, int key)
{
	node_t * temp = head;
	while(temp)
	{
		if(key == temp->key)
			return temp;
		
		temp = temp->next;
	}

	return temp;
}

/* Insert node with key-value pair into linked list */
void insert(node_t ** pphead, char key, int value)
{
	node_t * new_node = NULL;
	node_t * search_node = NULL;
	node_t * head = *pphead;
	
	if(!head)
	{	// Just add a node if this is the first node in linked list.
		*pphead = create_node(key, value);
	}
	else
	{
		search_node = search(head, key);
		if(!search_node)
		{
			/* No node found add it to head */ 
			new_node = create_node(key, value);
			new_node->next = head;
			*pphead = new_node;			
		}
		else
		{
			/* Node found. Update its value */ 
			search_node->data = value;
		}
	}	
}

void print_symbol_table(node_t ** head)
{
	node_t * temp = *head;
	
	while(temp)
	{
		printf("Key : %c     | Val : %d", temp->key, temp->data);
		printf("\n");
		temp = temp->next;
	}
}

int main()
{
    node_t * head = NULL;

	insert(&head, 'S', 10);
	insert(&head, 'T', 10);
	insert(&head, 'V', 10);
	insert(&head, 'X', 10);
	insert(&head, 'S', 20);
		
	print_symbol_table(&head);
	
	getch();
    return 0;
}
