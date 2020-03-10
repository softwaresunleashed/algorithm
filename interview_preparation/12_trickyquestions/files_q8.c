#include <stdio.h> 
#include <fcntl.h>

int main() {
	int fd;
	FILE *fp;
	fd = open("linux.txt", O_RDWR); 
	
	if (fd < 0) {
		perror("open failed"); 
	} else {
		printf("Opening file successful\n");
		close(fd); 
	}
	
	fp = fopen("linux.txt", "r");
	if (fp) 
	{
		printf("opening file successful\n"); 
		fclose(fp);
	} 
	else 
	{
		perror("open failed");
	}	

	return 0;
}
