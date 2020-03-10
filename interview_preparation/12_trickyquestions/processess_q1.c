// How many times "Hello world" will be printed in the below code?
// Ans : It displayed hello world twice, however, if i add "\n" to the printf() then "hello world" is printed only once 
// Using puts() solve the problem , and prints only once

#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <string.h> 
#include <unistd.h>

int main(int argc, char **argv) 
{
	printf("Hello, world.");		// Orig Program : Hello world is printed twice.
	//printf("Hello, world.\n");		// Hello world is printed only once. (use of \n)
	//puts("Hello world...");		// Hello world is printed only once.
	fork(); 
}

