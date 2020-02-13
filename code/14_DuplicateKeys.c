/******************************************************************************
    DuplicateKeys.c			(aka 3-way partitioning)
	===============
	Purpose of sort is to bring items with equal keys together.
	e.g. 	1) Sort population by age, 
			2) Find collinear points, 
			3) Remove duplicates from mailing list, 
			4) Sort job applicants by college attended.
	
	Typical characteristics of data for such algos  : 
			(1) Huge array  
			(2) Small number of key values
	
	Performance of famous sorting algos (when data array has duplicate keys) :
	========================================================================
	Merge Sort  => (n log n / 2)   ~~ (n log n) compares
	Quick Sort  => quadratic if you don't stop the partitioning at equal keys
	
	3-way partitioning
	=================
	Put all keys with same value at one place. Mark this space as lt & gt
	Entries between lt & gt equal to partition item 'v'
	No larger enteries to left of lt.
	No smaller entries to right of gt.

before	
	--------------------------------------
	|v|									| |
	--------------------------------------
	 ^									 ^	
	 |									 |
	 lo									 hi								
	
after
	--------------------------------------
	| < V   |		=V			|   > V  |
	--------------------------------------
	^		^					^		 ^	
	 |		|					|		 |
	 lo		lt					gt		 hi								
	
	
	
	
*******************************************************************************/

#include <stdio.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0






int main()
{
	
	
	getch();
    return 0;
}

