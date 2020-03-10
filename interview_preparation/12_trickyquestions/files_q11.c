// Why is "bye world" printing first in the below code.
// Ans : printf() buffers messages till the buffer is full or unless we forcefully flush the buffer by using '\n' in the printf() function


#include <stdio.h>
int main() 
{
	printf("hello world");		// Bye world is printed first 
	//printf("hello world\n"); 	// In this case, we added \n to flush buffered printf messages immediately
	perror("bye world"); 
	return 0;
}
