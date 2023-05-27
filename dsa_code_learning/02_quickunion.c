/******************************************************************************
    QuickUnion.c

	Find: Check if p and q have the same root.
	
	Union: To merge components containing p and q, set the id of p's root 
	to the id of q's root.
	
	==============================================
	algorithm 		initialize 		union	find
	==============================================
	quick-union 		N 			N 		N (worst case)
	==============================================
	
*******************************************************************************/

#include <stdio.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

 
 

#define MAX_NODES   8
int id[MAX_NODES];

void initQuickUnion(int n)
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
}

void display()
{
    int i = 0;
    for( i = 0; i < MAX_NODES; i++)
        printf("%d ", id[i]);
    
    printf("\n ");
}

/*
method find() to the union-find data type so that find(i) returns the largest
 element in the connected component containing i.
*/
int find(int p)
{
	int ret_largest = -1;
	int i = p;

	while(i != id[i])
	{
		i = id[i];
		if(ret_largest < id[i])
			ret_largest = id[i];
	}
	
	return ret_largest;
}

int main()
{
	int largest_number_in_con_components = -1;
 
    initQuickUnion(MAX_NODES);
    
    union_join(0, 5);
    union_join(5, 6);
    union_join(6, 1);
    union_join(1, 2);
    union_join(2, 7);
    display();
    
    printf((connected(0,7) == TRUE) ? "\nConnected" : "\nNot Connected");
    
	largest_number_in_con_components = find(7);
	printf("Largest Number among connected components = %d", largest_number_in_con_components);
	
    return 0;
}

