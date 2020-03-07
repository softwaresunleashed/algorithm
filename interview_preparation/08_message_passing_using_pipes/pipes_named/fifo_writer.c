#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


#define MaxLoops	12000	/* outer loop */
#define ChunkSize	16	/* How many bytes written at a time */
#define IntsPerChunk	4	/* four 4-byte ints per chunk */
#define MaxZs		250	/* max microseconds to sleep */

int main()
{
	const char * pipeName = "./fifoChannel";

	mkfifo(pipeName, 0644);		/* read/write for user / group / other */

	int fd = open(pipeName, O_CREAT | O_WRONLY);	/* open as write only */
	if(fd < 0)
		return -1;

	int i;
	for(i = 0; i < MaxLoops; i++){		/* write MaxWrites times */
		int j;
		for(j = 0; j < ChunkSize; j++){	/* each time, write ChunkSize bytes */
			int k;
			int chunk[IntsPerChunk];
			for(k = 0; k < IntsPerChunk; k++){
				chunk[k] = rand();
			}
			
			write(fd, chunk, sizeof(chunk));
		}
		usleep((rand() % MaxZs) + 1);	/* pause a bit for realism */
	}

	close(fd);	/* close pipe : generates end-of-stream marker */
	unlink(pipeName);
	printf("%i ints sent to the pipe.\n", MaxLoops * ChunkSize * IntsPerChunk);

	return 0;
}








