/*
	02_convert_binary_to_decimal.c
	==============================
	
	Program for Binary To Decimal Conversion
	----------------------------------------
	Given a binary number as input, we need to write a program to convert the given binary number into equivalent decimal number.

	Examples :

	Input : 111
	Output : 7

	Input : 1010
	Output : 10

	Input: 100001
	Output: 33

*/

#include <stdio.h>

#define MASK_LSb		0b1
int convert_to_decimal(int binary_integer)
{
	int decimal = 0;
	int index = 0;
	int base = 1;
	
	while(binary_integer)
	{   
		if(binary_integer % 10)
		{
			decimal = decimal + base;
		}
		base = base * 2;
		binary_integer = binary_integer / 10;
	}

	return decimal;	
}

int binary_input_array[] = {111, 1010, 100001};
void main()
{
	int size = sizeof(binary_input_array) / sizeof(binary_input_array[0]);
	int i = 0;
	int decimal_val = 0;
	
	for(i = 0; i < size; i++)
	{
		decimal_val = convert_to_decimal(binary_input_array[i]);	
		printf("\n\rBinary : %-32d --> Decimal : %d", binary_input_array[i], decimal_val);
	}

}