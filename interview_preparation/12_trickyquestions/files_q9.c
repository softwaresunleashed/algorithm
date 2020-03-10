// Will the "hello world" get printed in the below code. Explain why?
// Ans : Yes "hello world" would be printed, however, the executable file would be deleted since we call unlink(argv[0]) on it

#include <stdio.h> 
#include <fcntl.h> 
#include <sys/stat.h>

int main(int argc, char **argv) 
{
	unlink(argv[0]);
	printf("hello world\n"); 
}
