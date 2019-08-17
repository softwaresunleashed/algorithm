/******************************************************************************
    QuickFind.c
*******************************************************************************/


#include <stdio.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

 
 

#define MAX_NODES   8
int id[MAX_NODES];

void initQuickFind(int n)
{   
    int i = 0;
    for(i = 0; i < n; i++)
    {
        id[i] = i;
    }
}

bool connected(int p, int q)
{ 
    return id[p] == id[q]; 
}

void union_join(int p, int q)
{
    int pid = id[p];
    int qid = id[q];
    int i = 0;
    
    for ( i = 0; i < MAX_NODES; i++)
        if (id[i] == pid) 
            id[i] = qid;
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
 
    initQuickFind(MAX_NODES);
    
    union_join(0, 5);
    union_join(5, 6);
    union_join(6, 1);
    union_join(1, 2);
    union_join(2, 7);
    display();
    
    printf((connected(0,7) == TRUE) ? "\nConnected" : "\nNot Connected");
    
    return 0;
}
