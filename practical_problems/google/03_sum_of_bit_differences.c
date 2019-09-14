/*

Sum of bit differences among all pairs
======================================
Given an integer array of n integers, find sum of bit differences in all pairs 
that can be formed from array elements. Bit difference of a pair (x, y) is 
count of different bits at same positions in binary representations of x and y.

For example, bit difference for 2 and 7 is 2. 
Binary representation of 2 is 010 and 7 is 111 ( first and last bits differ 
in two numbers).

Examples :
--------
Input: arr[] = {1, 2}
Output: 4
All pairs in array are (1, 1), (1, 2), (2, 1), (2, 2)
Sum of bit differences = 0 + 2 + 2 + 0 = 4

Input:  arr[] = {1, 3, 5}
Output: 8
All pairs in array are (1, 1), (1, 3), (1, 5)
						(3, 1), (3, 3) (3, 5),
						(5, 1), (5, 3), (5, 5)
Sum of bit differences =  0 + 1 + 1 +
                          1 + 0 + 2 +
                          1 + 2 + 0 
					= 8

*/
#include<stdio.h>
#include<time.h>


// Valid Values of APPROACH : 1,2,3
#define APPROACH	3		

#if (APPROACH == 1)	/* Comparing parallel bits */
int count_bit_diff(int array[], int size)
{
	#define LSB_MASK_0B1	0b1
	int count = 0, a = 0, b = 0, i = 0, j = 0, k = 0;
	int test_a_bit = 0, test_b_bit = 0;
	
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			a = array[i];
			b = array[j];
			
			/* If both digits are equal then 
			there wont be any difference in bits */
			if(a == b)
				continue;

			for(k = 0; k < sizeof(int); k++)
			{
			    test_a_bit = a & LSB_MASK_0B1;
			    test_b_bit = b & LSB_MASK_0B1;
			
			    // Increase count, if both bits are different
			    if(test_a_bit != test_b_bit)
				    count++;

				a = a >> 1;
				b = b >> 1;    
			}
		}
	}

	return count;
}

#elif (APPROACH == 2)	
/* XOR and count number of one's...
XOR is 1 if the two bits are different */
int count_bit_diff(int array[], int size)
{
	#define LSB_MASK_0B1	0b1
	int count = 0, a = 0, b = 0, i = 0, j = 0;
	int xor_result = 0;

	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			a = array[i];
			b = array[j];
			
			/* If both digits are equal then 
				there wont be any difference in bits */
			if(a == b)
				continue;
			
			// XOR to set bits in xor_result which are different
			xor_result = a ^ b;
    
            // Optimization : loop till the time number is non-zero
			while(xor_result)
			{
			    // Increase count, if both bits are different
			    if(xor_result & LSB_MASK_0B1)
				    count++;

                // Remove the bit already counted
				xor_result = xor_result >> 1;
			}
		}
	}

	return count;
}
	
#elif (APPROACH == 3)	/* Custom Algo - increas pointer till find 1 */

#define LSB_MASK_0B1	0b1
#define RESET_BIT(var, bit)		var = var & ~(LSB_MASK_0B1 << bit)
int count_bit_diff(int array[], int size)
{
    int i = 0, j = 0, a = 0, b = 0, a_bit_index = 0, b_bit_index = 0;
	int count = 0;
	
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			a = array[i];
			b = array[j];
			
			/* If both digits are equal then 
			there wont be any difference in bits */
			if(a == b)
				continue;
			
			a_bit_index = 0;
			b_bit_index = 0;
			
			while(a || b)
			{
				while(!(a & (LSB_MASK_0B1 << a_bit_index)) 
				                            && (a_bit_index < sizeof(int)) )
				{
					a_bit_index++;
				}
				
				while(!(b & (LSB_MASK_0B1 << b_bit_index)) 
				                            && (b_bit_index < sizeof(int)) )
				{
					b_bit_index++;
				}
				
				if(a_bit_index == b_bit_index)
				{
					// Both are same bits reset both to zero and move forward
					RESET_BIT(a, a_bit_index);
					RESET_BIT(b, b_bit_index);
					a_bit_index++;
					b_bit_index++;
				}
				else
				{
					if(a_bit_index > b_bit_index)
					{
						RESET_BIT(b, b_bit_index);
						b_bit_index++;
						count++;
					}
					else
					{
						RESET_BIT(a, a_bit_index);
						a_bit_index++;
						count++;
					} /* if */		
				} /* if */
			}/* while */
		} /* for */
	} /* for */

	return count;
}

#endif



/* Sample Input */
#if 0
int arr[] = {1, 2};
#else
int arr[] = {1, 3, 5, 10, 255, 16, 1237};	
#endif


void main()
{
    int i = 0, diff_bits = 0;
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	clock_t begin = 0, end = 0;
	
	printf("\n\rSample Input : ");
	for(i = 0; i < arr_size; i++)
	{
		printf("%d " , arr[i]);
	}
	
	printf("\n\rUsing APPROACH : %d to calculate different bits in pairs... ", APPROACH);

	// Mark beginning of algo 
	begin = clock();

	// do some stuff here
	diff_bits = count_bit_diff(arr, arr_size);
	
	// Mark end of algo 
	end = clock();
	
	printf("\n\rBit difference : %d", diff_bits);
	printf("\n\rAlgo Runtime in clk ticks : %d", end - begin);
}
