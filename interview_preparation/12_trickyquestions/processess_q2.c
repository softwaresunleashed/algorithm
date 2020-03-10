//Will the parent printf work if the child closes the standard ouput. Run the below code and comment?
// Ans : Stdout would be closed only for child process, and not for parent process. Hence only Parent process hello world would be displayed. 

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

int main() 
{
	pid_t pid;
	pid = fork();
	
	if (pid == 0) 
	{
		close(1);					// Close standard output stream within child process
		printf("Child says : hello world\n"); 		// --> This is NOT displayed, as stdout is closed above for child process
		_exit(0);					// Inform Parent that child has exited successfully
	} 
	else if (pid > 0) 
	{ 
		wait(NULL); 					// Wait for child to finish.
		printf("Parent says : hello world\n"); 		// --> This is displayed as stdout is still available for parent process
	}

	return 0; 
}
