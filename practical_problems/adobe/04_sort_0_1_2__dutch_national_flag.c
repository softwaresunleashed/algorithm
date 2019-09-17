/*
	04_sort_0_1_2__dutch_national_flag.c
	====================================
	
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
	This kind of sorting (0/1) or (0/1/2) can be done 
	by Dutch National Flag algo (2 way partitioning / 3 way partitioning).
			
	Dijkstra used the Dutch National Flag Problem* as a structured programming 
	exercise in program derivation and program proof. Given `N' objects coloured 
	red, white or blue, sort them so that objects of the same colour are adjacent, 
	with the colours in the order red, white and blue.
	
	The problem is closely related to the partition operation of quick sort: 
	the attribute need not be a `colour' but can be `greater than the median', 
	or `leading digit is zero', or whatever property you care to choose.

	Two Colours
	-----------
	It is easiest to consider just two "colours", {zero,one}, first. 
	The algorithm maintains three sections (possibly empty) in the array a[ ]:

		1) a[1..Lo-1] zeroes
		2) a[Lo..Hi] unknown
		3) a[Hi+1..N] ones
	
	The unknown section is shrunk while maintaining these conditions:
		1. Lo := 1; Hi := N;
		2. while Lo <= Hi do
			1. Invariant: a[1..Lo-1] are all zero and a[Hi+1..N] are all one; a[Lo..Hi] are unknown.
			2. if a[Lo] = 0 then Lo++
			3. else swap a[Lo] and a[Hi]; Hi--
	--- 2-way Partitioning ---
	
	
	
	
	Three Colours
	-------------
	The problem was posed with three colours, here `0', `1' and `2'. The array is divided into four sections:

		1) a[1..Lo-1] zeroes (red)
		2) a[Lo..Mid-] ones (white)
		3) a[Mid..Hi] unknown
		4) a[Hi+1..N] twos (blue)

	The unknown region is shrunk while maintaining these conditions
		1. Lo := 1; Mid := 1; Hi := N;
		2. while Mid <= Hi do
			1. Invariant: a[1..Lo-1]=0 and a[Lo..Mid-1]=1 and a[Hi+1..N]=2; a[Mid..Hi] are unknown.
			2. case a[Mid] in
				0: swap a[Lo] and a[Mid]; Lo++; Mid++
				1: Mid++
				2: swap a[Mid] and a[Hi]; Hi--
				
--- Dutch National Flag Algorithm, or 3-way Partitioning ---


*/

#include <stdio.h>

void exch(int array[], int index1, int index2)
{
	int temp = 0;
	
	/* Optimization : 
		If both elements are same, then dont swap, 
		This avoids unnecessary swaps. 
	*/
	if(array[index1] == array[index2])
		return;
	
	temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

void sort_array_3way_dutch_flag(int source_array[], int size)
{

	int lo = 0, mid = 0, hi = size-1;
	
	while(mid <= hi)
	{
		switch(source_array[mid])
		{
			case 0:
				exch(source_array, mid, lo);
				lo++; mid++;
				break;
			
			case 1:
			    mid++;
				break;
			
			case 2:
				exch(source_array, mid, hi);
				hi--;
				break;
		}
	}
}

void print_array(int input_array[], int size)
{
	int i = 0;
	for(i = 0; i < size; i++)
	{
		printf("%d ", input_array[i]);
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
	
	sort_array_3way_dutch_flag(input_array,  size);
	
	printf("\nArray after sort (using Dijkstra\'s Dutch Flag Algorithm) : ");
	print_array(input_array, size);

}
