/******************************************************************************
    Percolation.c

	
	Find: Check if p and q have the same root.
	
	Union: To merge components containing p and q, set the id of p's root 
	to the id of q's root.
	
*******************************************************************************/

#include <stdio.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

 
 

int MAX_NODES;
int * id;		// Percolation array

void initPercolation(int row, int col)
{   
    int i = 0;
	MAX_NODES = row * col;
	
	id = malloc(MAX_NODES * sizeof(int));
	if(!id)
		return;
		
    for(i = 0; i < MAX_NODES; i++)
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
        printf("[%d] ", i);
    
    printf("\n");
        
    for( i = 0; i < MAX_NODES; i++)
        printf(" %d ", id[i]);
    
    printf("\n");
}

void create_maze()
{
    union_join(0, 1);
    union_join(1, 6);
    union_join(6, 7);
    union_join(7, 12);
    union_join(12, 13);
    union_join(13, 18);
    union_join(18, 23);
    
}

int main()
{
    int row = 0, col = 0;
    printf("Enter Row : ");
	scanf("%d", &row);
    printf("Enter Col : ");
    scanf("%d", &col);
    
    initPercolation(row, col);
    
    display();  // Before connecting maze points
    create_maze();
    display();  // After connecting maze points
    
    // Check if maze points are connected or not?
    printf((connected(0,24) == TRUE) ? "\nConnected" : "\nNot Connected");
    printf((connected(0,23) == TRUE) ? "\nConnected" : "\nNot Connected");
    
	
    return 0;
}

