/******************************************************************************
    stack.c

    
	
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_ENABLED           1
#define STACK_OVERFLOW_ERR      -1

#define STACK_DEPTH     256
char stack[STACK_DEPTH];
int current_index = STACK_DEPTH - 1;
int last_push_size = 0;

int stack_push_len[STACK_DEPTH];
int push_len_index = STACK_DEPTH - 1;


#define TRUE    1
#define FALSE   0

int isEmpty()
{
    if(current_index == (STACK_DEPTH - 1))
        return TRUE;
    else
        return FALSE;
}

void push(char * string)
{
    char * temp = string;
    int i = 0;
    last_push_size = 0;
    
    while(temp[i] != '\0')
    {
        stack[current_index] = temp[i];
        current_index--;
        i++;
        
        if(current_index == -1)
        {
            printf("Stack Overflow Detected...Exiting.");
            //exit(STACK_OVERFLOW_ERR);
        }
    }
    
    last_push_size = i;
    stack_push_len[push_len_index--] = last_push_size;
}

char * pop()
{
    char * temp_ptr = NULL;
    
    if(isEmpty())
    {
        printf("\nStack is empty. Fill stack before poping...");
        return NULL;
    }
    
    last_push_size = stack_push_len[++push_len_index];
#if DEBUG_ENABLED
    printf("\nlast_push_size = %d", last_push_size);
#endif
    
    temp_ptr = (char *) malloc(last_push_size + 1);
    if(temp_ptr)
    {
        temp_ptr[last_push_size] = '\0';
        
        for(int i = 1; i <= last_push_size; i++)
        {
            current_index++;
            temp_ptr[last_push_size - i] = stack[current_index];
        }
    }
    return temp_ptr;
}

void print_stack()
{
    int temp_index = current_index;
    
    printf("\n Stack Printing - Start...\n");
    while(temp_index < STACK_DEPTH)
    {
        printf("%c ", stack[temp_index]);
        temp_index++;
    }
    printf("\n Stack Printing - End.\n");   
    
    temp_index = push_len_index;
    printf("\n Push Len - Start...\n");
    while(temp_index < STACK_DEPTH)
    {
        printf("%d ", stack_push_len[temp_index]);
        temp_index++;
    }
    printf("\n Push Len - End.\n");   
}

int main()
{
    char * temp_ptr = NULL;
    char input_string[STACK_DEPTH];
    
	while(1)        /* Infinite Loop */
	{
	  printf("Enter String : ");
	  scanf("%s", input_string);
	  
	  if(strcmp(input_string, "-") == 0)
	  {
	    temp_ptr = pop();
	    if(temp_ptr)
	    {
	        printf("\nLast String Entered : %s \n", temp_ptr);
	        free(temp_ptr);
	        temp_ptr = NULL;
	    }
	  }
	  else if(strcmp(input_string, "*") == 0)
	  {
	      print_stack();
	  }
	  else 
	  {
	    push(input_string);    
	  }
	};
	
    return 0;
}

