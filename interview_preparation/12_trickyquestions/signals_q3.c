// Will the signal handler executes when you run the below code? To find the answer use: "man -s7 signal"
// Ans : No signal handler was not called. Reason unknown.(?) 

#include <signal.h> 
#include <stdio.h>

void sighandler(int signum) {
	printf("Signal Handler of SIGKILL\n"); 
}

int main() {
	signal(SIGKILL, sighandler); 
	
	//sleep(15);	// Add sleep between signal registration and raising signal
	
	raise(SIGKILL);
	while(1);
}
