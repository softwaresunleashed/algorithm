
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>


#define SHM_SIZE	27		/* size of shared memory */
#define UNIQUE_KEY	5678

int main()
{

	char c;
	int shmid;
	key_t key;
	char * shm, *s;

	key = UNIQUE_KEY;

	/* Locate the shared memory segment */
	if((shmid = shmget(key, SHM_SIZE,  0666) ) < 0 ){
		perror("shmget returned error.");
		exit(1);
	}

	/* attach the segment to our data space */
	if( (shm = shmat(shmid, NULL, 0) ) == (char *) -1 ){
		perror("shmat returned error.");
		exit(1);
	}

	/* read the data put by server */
	for(s= shm; *s != 0; s++)
		putchar(*s);

	putchar('\n');

	/* finally change the first character of shared memory to * on which
	the server is looping on */
	*shm = '*';
	
	exit(0);
}



