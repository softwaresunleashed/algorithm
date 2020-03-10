// Will the child receive SIGALARM if the parent has started a timer using alarm system call before calling fork()? Try this code and find out.
// pause() causes the calling process (or thread) to sleep until a signal is delivered that either terminates the process or causes the invocation of a signal-catching function.
// Ans: Child process gets the alarm signal and alarm handler is invoked. (This signal is inherited from Parent process). A child process inherits all the signals registerd by Parent.


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h> 
#include <sys/signal.h>

void alarm_handler(int signum) 
{ 
	printf("%s:PID:%d\n", __func__, getpid());
}

int main()
{
	pid_t pid;
	printf("Process PID:%d\n", getpid()); 

	//set up alarm handler 
	signal(SIGALRM, alarm_handler); 
	
	//schedule alarm for 2 second 
	alarm(2);
	
	pid = fork();
	if (pid == 0) 
	{
		printf("Hi, I am Child with PID:%d\n", getpid()); 
	}
	
	//wait for signal	
	pause(); 

	return 0;
}
