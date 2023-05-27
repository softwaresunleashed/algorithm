/******************************************************************************
    QuickUnion.c

	Data structure: Same as quick-union, but maintain extra array sz[i]
	to count number of objects in the tree rooted at i.

	Find: Check if p and q have the same root.(Identical to quick-union.)
	
	Union:  Modify quick-union to:
				・Link root of smaller tree to root of larger tree.
				・Update the sz[] array
	
	==================================================
	algorithm 		initialize 		union	find
	==================================================
	Weighted QU 		N 			log N 		log N
	==================================================
	
*******************************************************************************/

#include <stdio.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

 
 

#define MAX_NODES   8
int id[MAX_NODES];
int sz[MAX_NODES];

void initWeightedQuickUnion(int n)
{   
    int i = 0;
    for(i = 0; i < n; i++)
    {
        id[i] = i;
    }
}

int root(int i)
{
	while(i != id[i])
		i = id[i];
	return i;	
}

bool connected(int p, int q)
{ 
    return root(p) == root(q);
}

void union_join(int p, int q)
{
    int i = root(p);
    int j = root(q);
	id[i] = j;
	
	if (i == j) 
		return;
	
	/* This is number of elements in tree (and not height of tree) */
	if (sz[i] < sz[j]) 
	{ 
		id[i] = j; 
		sz[j] += sz[i]; 
	} else { 
		id[j] = i; 
		sz[i] += sz[j]; 
	}
}

void display()
{
    int i = 0;
    for( i = 0; i < MAX_NODES; i++)
        printf("%d ", id[i]);
    
    printf("\n ");
}



int main()
{
 
    initWeightedQuickUnion(MAX_NODES);
    
    union_join(0, 5);
    union_join(5, 6);
    union_join(6, 1);
    union_join(1, 2);
    union_join(2, 7);
    display();
    
    printf((connected(0,7) == TRUE) ? "\nConnected" : "\nNot Connected");
    
    return 0;
}

