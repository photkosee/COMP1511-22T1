// A program separates positive, negative and zero.
// negative.c
// Written 22/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 02 Exercise 2

#include <stdio.h>

int main(void) {
    
    int number;
    scanf("%d", &number);
    if (number < 0) {
        printf("Don't be so negative!\n");
    } else if (number == 0) {
        printf("You have entered zero.\n");
    } else {
        printf("You have entered a positive number.\n");
    }
    
}