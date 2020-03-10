// Run the below code and check the name of the process using ps command (ps -ef). Try passing argument and without argument
// Ans : If no argument is provided then, argv[0] is used to display the name of process in ps. However, when we copy the argument argv[1] onto argv[0] then the new process name is displayed (since argv[1] is now over written onto argv[0]).

#include <stdio.h> 
#include <unistd.h> 
#include <string.h>

int main(int argc, char *argv[]) {
	printf("hello world\n"); 
	
	if (argc == 2)
		strcpy(argv[0] , argv[1]); 

	pause();
}
