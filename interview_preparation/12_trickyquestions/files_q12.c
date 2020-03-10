// What happens if we perform lseek more than the file size? Guess the size of the file 'hello.txt' when we run this code and comment:
// Ans : The file size if increased by those many bytes when we perform a lseek(), ie. 1000 in this case. And finally writes "bye" at the end of the file. The new file size was around 1kb.

#include <stdio.h> 
#include <fcntl.h>

int main() 
{
	int fd = open("hello.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666); 
	write(fd, "hello", 5);
	lseek(fd, 1000, SEEK_END);
	write(fd, "bye", 3);
	close(fd);
	return 0; 
}
