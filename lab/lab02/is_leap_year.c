// A simple C program to print whether that year is a leap year.
// is_leap_year.c
// Written 23/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 02 Exercise 4

#include <stdio.h>

int main(void){
    
    int year;
    printf("Enter year: ");
    scanf("%d", &year);
    
    if (year % 4 != 0) {
        printf("%d is not a leap year.\n", year);
    } else if (year % 100 != 0) {
        printf("%d is a leap year.\n", year);
    } else if (year % 400 != 0) {
        printf("%d is not a leap year.\n", year);
    } else {
        printf("%d is a leap year.\n", year);
    }
    
}
