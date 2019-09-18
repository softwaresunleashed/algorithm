/*
	06_palindrome.c
	===============
	
	Problem : Check if a number is Palindrome
	-----------------------------------------
	Given an integer, write a function that returns true if the given number 
	is palindrome, else false. For example, 12321 is palindrome, but 1451 
	is not palindrome.
	
	
	Solution :
	========
	Extract the integer into an array, and start comparing elements at beginning++ and end-- , 
	till both pointers cross each other.
	Break if at anytime, two elements are not same.

*/

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define TRUE	1
#define FALSE	0

#define MAX_POSSIBLE_DIGITS	200
int scratch_array[MAX_POSSIBLE_DIGITS];

bool isPalindrome(char * number_to_check)
{
	int index = 0;
	int number_at_index = 0;
	int lo = 0, hi = 0;
	bool ret_val = TRUE;
	
	while(number_to_check[index] != '\0')
	{
	    /* Convert "string number" to number by subtracting '0' from string 
	        number */
		number_at_index = number_to_check[index] - '0';

        scratch_array[index] = number_at_index;
		index++;
	}
	
	/* Set hi to size of number of digits in integer */
	hi = index-1;   /* Minus 1 to adapt for zero indexed array */
	
	/* Check extreme elements for in-equality */
	while(lo < hi)
	{
		if(scratch_array[lo] != scratch_array[hi])
		{
			ret_val = FALSE;
			break;
		}
		
		lo++; hi--;
	}
	
	return ret_val;
}

void main()
{
	char * number = (char *)malloc( MAX_POSSIBLE_DIGITS + 1 );
	bool isNumPalindrome = FALSE;
	
	printf("\nEnter number to check for Palindrome (max digits %d) : ", MAX_POSSIBLE_DIGITS);
	scanf("%s", number);
	
	isNumPalindrome = isPalindrome(number);
	printf("\nNumber is %s", (isNumPalindrome == TRUE) ? "Palindrome" : "Not Palindrome");
}
