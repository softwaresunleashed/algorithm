// Will the threadid(tid) and processid(pid) same for a process with a single thread? Run the below code and find out.
// Ans : No both are different. Thread ID is obtained by system call - syscall(SYS_gettid())

#include <unistd.h> 
#include <stdio.h> 
#include <sys/syscall.h>

int main() 
{
	printf("Process ID:%u\t Thread ID:%lu\n", getpid(), syscall(SYS_gettid));
	return 0; 
}
