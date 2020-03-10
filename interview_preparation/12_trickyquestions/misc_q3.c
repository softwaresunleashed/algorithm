// Will heap section exists in the address space of process using the below code? Use /proc to find out.
// Ans : Check /proc/<pid>/maps for section labled "Heap". In present scenario, no such section is defined in process map table.

/*
01d56000-07026000 rw-p 00000000 00:00 0                       [heap]
*/



#include <stdio.h> 

int main()
{
	while(1); 
}
