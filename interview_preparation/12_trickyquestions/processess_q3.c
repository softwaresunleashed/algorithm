//Will this below program ever ends?
// Ans : This program keeps on going till we press Ctrl+C (Terminate Signal to process).
// 	exec() family of functions replaces the current process image with a new process image.


#include <stdio.h> 
#include <unistd.h>

int main(int argc, char *argv[]) 
{ 
	printf("Hello Linux\n"); 
	execl(argv[0], argv[0], NULL);	// --> Replaces current process's image with the one specified in first argument.
}
