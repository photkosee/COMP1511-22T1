// A simple C program to set a dice and find its range and average value.
// dice_range.c
// Written 23/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 02 Exercise 5

#include <stdio.h>

int main(void){

    int side;
    int roll;
    float min;
    float average;
    int max;
    
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &side);
    
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &roll);
        
    if (roll < 1 || side < 1) {
        printf("These dice will not produce a range.\n");
    } else {
    
        min = roll;
        max = side*roll;
        average = (max + min) / 2;
    
        printf("Your dice range is %d to %d.\n", roll, max);
        printf("The average value is %lf\n", average);
    }
    
}
