
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

	/* Create the shared memory segment */
	if((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666) ) < 0 ){
		perror("shmget returned error.");
		exit(1);
	}

	/* attach the segment to our data space */
	if( (shm = shmat(shmid, NULL, 0) ) == (char *) -1 ){
		perror("shmat returned error.");
		exit(1);
	}

	/* Now put some things in shared memory */
	s  = shm;
	for(c = 'a'; c <= 'z'; c++){
		*s++ = c;
	}
	*s = 0;

	/* wait until second thread sets the shared memory to '*' */
	while(*shm != '*')
		sleep(1);

	exit(0);
}



