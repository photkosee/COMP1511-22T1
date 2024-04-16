// A program which will add two integers
// addition.c
// Written 22/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 02 Exercise 1

#include <stdio.h>

int main(void) {
    
    int number1;
    int number2;
    int sum;
    printf("Please enter the number of students and tutors: ");
    scanf("%d %d", &number1, &number2);
    sum = number1 + number2;
    printf("%d + %d = %d\n", number1, number2, sum);
    
}
