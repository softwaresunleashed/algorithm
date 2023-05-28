/*
    Reference : 
    https://www.hackerrank.com/challenges/students-marks-sum/problem?isFullScreen=true
*/


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


//Complete the following function.

int marks_summation(int* marks, int number_of_students, char gender) {
  //Write your code here.
  int marks_sum = 0;
  
  // set initial value of i based on gender
  int i = (gender == 'b') ? 0 : 1;  
  
  // start iterating till end of list with a gap of 2
  for(; i < number_of_students; i=i+2 ) {
      marks_sum += marks[i]; 
  }
  
  return marks_sum;
}

int main() {
    int number_of_students;
    char gender;
    int sum;
  
    scanf("%d", &number_of_students);
    int *marks = (int *) malloc(number_of_students * sizeof (int));
 
    for (int student = 0; student < number_of_students; student++) {
        scanf("%d", (marks + student));
    }
    
    scanf(" %c", &gender);
    sum = marks_summation(marks, number_of_students, gender);
    printf("%d", sum);
    free(marks);
 
    return 0;
}