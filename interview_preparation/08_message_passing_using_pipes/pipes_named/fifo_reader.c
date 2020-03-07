#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define TRUE	1
#define FALSE	0

int is_prime(unsigned n){	/* not pretty, but efficient */
	int i = 0;
	int isPrime = TRUE;

	for(i = 2; i < n; i++)
	{
		if((n % i) == 0)
		{
			isPrime = FALSE;
			break;
		}
	}

	return isPrime;
}


int main()
{
	const char * file = "./fifoChannel";
	int fd = open(file, O_RDONLY);
	
	if(fd < 0)
		return -1;

	unsigned count = 0, total = 0, prime_count = 0;
	
	while(1)
	{
		int next;
		int i;
	
		ssize_t count = read(fd, &next, sizeof(int));
		if(0 == count)
		{
			break;
		}
		else if(count == sizeof(int))
		{
			total++;
			if(is_prime(next) == TRUE)
				prime_count++;
		}
	};

	close(fd);	/* close pipe from read end */
	unlink(file);	/* unlink from the underlying file */
	
	printf("Received ints: %u, primes: %u\n", total, prime_count);

	return 0;
}
