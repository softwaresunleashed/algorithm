// What happens to the file offset in the parent when the child process writes to the file? Try this code and comment.
// Ans : 
// offset before creating child:5
// offset after child terminates:11

#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/wait.h>

int main() {
	int fd; pid_t pid;
	
	fd = open("output", O_CREAT|O_TRUNC|O_WRONLY, 0666);
	write(fd, "hello", 5);
	printf("offset before creating child:%u\n", lseek(fd, 0, SEEK_CUR));
	
	pid = fork();
	if (pid == 0) {
		write(fd, " world", 6);
	} else if (pid > 0) {
		wait(NULL);
		printf("offset after child terminates:%u\n", lseek(fd, 0, SEEK_CUR)); } else {
		perror("fork failed");
	}
	close(fd);
	
	return 0; 

}
