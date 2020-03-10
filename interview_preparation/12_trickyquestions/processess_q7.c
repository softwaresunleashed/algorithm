// Why is the argc address different each time we run the executable?
// Ans : That is because argc and argv are pushed onto the stack, and everytime we run executable, its unpredicatble where the process's stack would be located in memory, hence different addresses.

#include <stdio.h>
int main(int argc, char *argv[]) 
{
	printf("Argc Address:%p\n", &argc);
	return 0; 
}
