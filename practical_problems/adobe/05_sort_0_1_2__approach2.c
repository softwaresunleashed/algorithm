/*
	05_sort_0_1_2__approach2.c
	==========================
	
	Problem : Sort an array of 0s, 1s and 2s
	----------------------------------------
	Given an array A[] consisting 0s, 1s and 2s. The task is to write a function that sorts the given array. The functions should put all 0s first, then all 1s and all 2s in last.

	Examples:

	Input: {0, 1, 2, 0, 1, 2}
	Output: {0, 0, 1, 1, 2, 2}

	Input: {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1}
	Output: {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2}
	
	
	Solution :
	========
	Simple solution would be to count number of 0,1,2's and then write the array again using this count values.
	

*/

#include <stdio.h>



void print_array(int input_array[], int size)
{
	int i = 0;
	for(i = 0; i < size; i++)
	{
		printf("%d ", input_array[i]);
	}
}

void sort_array_012(int input_array[], int size)
{
	int i = 0, count_0 = 0, count_1 = 0, count_2 = 0;
	
	for(i = 0; i < size; i++)
	{
		switch(input_array[i])
		{
			case 0:
				count_0++;
				break;
			case 1:
				count_1++;
				break;
			case 2:
				count_2++;
				break;
		}
	}
	
	/* Reset index to zero, before filling array again */
	i = 0;
	
	/* Start writing ZERO */
	while(count_0--)
	{
		input_array[i++] = 0;
	}

	/* Start writing ONE */
	while(count_1--)
	{
		input_array[i++] = 1;
	}

	/* Start writing TWO */
	while(count_2--)
	{
		input_array[i++] = 2;
	}
	
}

#if 0
int input_array[] = {0, 1, 2, 0, 1, 2};
#else
int input_array[] = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
#endif


void main()
{
	int size = sizeof(input_array) / sizeof(input_array[0]);
	
	printf("\nArray before sort : ");
	print_array(input_array, size);
	
	sort_array_012(input_array,  size);
	
	printf("\nArray after sort : ");
	print_array(input_array, size);

}
