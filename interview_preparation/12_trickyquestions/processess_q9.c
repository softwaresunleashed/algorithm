// How many times ‘hello’ will be printed? (HINT: RLIMIT_STACK)
// Ans : RLIMIT_STACK -- This is the maximum size of the initial thread's stack, in bytes. The implementation does not automatically grow the stack beyond this limit. If this limit is exceeded, SIGSEGV shall be generated for the thread. If the thread is blocking SIGSEGV, or the process is ignoring or catching SIGSEGV and has not made arrangements to use an alternate stack, the disposition of SIGSEGV shall be set to SIG_DFL before it is generated. 
// i:0 hello
// i:1 hello
// i:2 hello
// Segmentation fault: 11


#include <stdio.h> 

static int i = 0;

int hello()
{
	char buf[8192*256]; 
	printf("i:%d %s\n", i++, __func__); 
	hello();
}

int main()
{
	hello(); 
}
