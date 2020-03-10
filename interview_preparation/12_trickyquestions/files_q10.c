// Will "hello world" get printed in the below code on Linux?
// Ans : No it will not be printed, since we have closed the stdout stream.

#include <stdio.h> 
#include <unistd.h>

int main() 
{
	close(1);
	printf("hello world\n"); 
	return 0;
}
