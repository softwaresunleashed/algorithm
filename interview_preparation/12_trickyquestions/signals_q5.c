// Try this code and check what happens:
// Ans : kill(-1, SIGKILL) will send a Kill signal to all the processes except KILL and INIT processes. It killed all my applications. :)
 
// Negative PID values are used to indicate the process group ID. If you pass a process group ID then all the process within that group will receive the signal.
// A PID of -1 is very special as it indicates all the processes except kill and init, which is the parent process of all processes on the system.

#include <stdlib.h> 
#include <stdio.h> 
#include <signal.h>

int main() 
{ 
	kill(-1, SIGKILL);	
}
