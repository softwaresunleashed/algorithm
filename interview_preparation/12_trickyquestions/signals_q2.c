// What happens when signal is delivered to the process who called sleep(), will the remaining sleep continue after the signal handler?
// $ ./signals_q2 &
// [2] 30500
// Registered signal handler for pid(30500) : SIGUSR1(30)
// $ kill 30500
// [2]+  Terminated: 15          ./signals_q2


#include <stdio.h> 
#include <signal.h>

void sighandler(int signum) 
{
	write(1, "sighandler", 10); 
}

int main(int argc, char *argv[]) {
	// Register handler for SIGUSR1
	signal(SIGUSR1, sighandler); 
	
	printf("Registered signal handler for pid(%d) : SIGUSR1(%d)\n", getpid(), SIGUSR1);	


	sleep(20);
	printf("After Sleep\n"); 
	return 0;
}
