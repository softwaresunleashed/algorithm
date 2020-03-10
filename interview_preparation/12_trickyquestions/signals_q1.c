//Guess the output of this code:
// Segmentation fault is ignored and process doesn't exit (and not return to shell)

#include <stdio.h> 
#include <signal.h>
int main()
{
	int *ptr = NULL; 
	signal(SIGSEGV, SIG_IGN);	//--> This says to IGNORE , segmentation fault 
	*ptr = 10;			// Segmentation fault will happen here however will be ignored by process

	return 0;
}
