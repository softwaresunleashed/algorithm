// Will the file offset in the parent change when the child performs read/write operation on file. Run the below code and comment.
// Ans : file offset:6
// This means that when any operation is done in child process, the same is reflected in parent process (and vice versa), since file operation information is stored in file data structure. ie. Any file operation done in any process is preserved to other process.

#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdlib.h>

int main()
{
	pid_t pid;
	int fd = open("processess_q4_hello.txt", O_WRONLY|O_CREAT, 0644);
	
	if (fd < 0) 
	{ 
		perror("open failed"); 
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0) 
	{
		/* Child Process */
		write(fd, "hello", sizeof("hello"));
		close(fd);
		exit(EXIT_SUCCESS);
	} 
	else if (pid > 0) 
	{	/* Parent Process */
		wait(NULL);
		printf("file offset:%ld\n", lseek(fd, 0, SEEK_CUR));
		exit(EXIT_SUCCESS); 
	}
	
	return 0;
}
