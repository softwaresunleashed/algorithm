#include <stdio.h>
int main () 
{
	freopen("/dev/null", "w", stdout); 
	printf("Hello World\n");
	return 0;
}

