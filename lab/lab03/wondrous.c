// A simple C program to calculate sequence from the Collatz Conjecture.
// wondrous.c
// Written 28/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 03 Exercise 5

#include <stdio.h>

int main(void) {

    int num;
    int count;
    
    printf("What number would you like to see: ");
    scanf("%d", &num);
    
    while (num != 1) {
    
        count = 0;
        if (num % 2 == 0) {
            while (count < num) {
                printf("*");
                count += 1;
            }
            printf("\n");
            num /= 2;
        } else {
            while (count < num) {
                printf("*");
                count += 1;
            }
            printf("\n");
            num = 3*num + 1;
        }
    
    }
    
    return 0;

}
