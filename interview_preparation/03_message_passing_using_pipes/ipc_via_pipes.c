

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>


int main()
{
	int pipefd[2];
	int pid;	/* This is zero in child process after fork() and greater than zero in parent process */
	char recv[32];

	pipe(pipefd);	/* create the pipe fd[0] & fd[1] */

	//pid = fork();	/* Create a child process ...total of 4 fds now */

	switch(pid = fork())
	{
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("Entered Child :\n");		/* The child goes here */
			close(pipefd[0]);			// close unnecessary fds
			FILE *out = fdopen(pipefd[1], "w");	// open write stream from child
			fprintf("Hello world from pid = %d\n", pid);	// write to out stream
			break;
		default:		
			printf("Entered Parent :\n");		/* Parent comes here */
			close(pipefd[1]);			// close unnecessary fds
			FILE *in = fdopen(pipefd[0], "r");	// open write stream from child
			fscanf(in, "%s", recv);
			printf("Message from pipe : %s\n", recv);
			break;
	};
}
