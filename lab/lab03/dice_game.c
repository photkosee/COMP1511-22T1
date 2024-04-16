// A simple C program to calculate 10 dice rolls with a special method.
// dice_game.c
// Written 28/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 03 Exercise 3

#include <stdio.h>

int main(void) {
    
    int num;
    int pre_num = 0;
    int count = 0;
    int sum = 0;
    int error = 1;
    
    printf("Enter numbers: ");
    
    while (count < 10) {
    
        scanf("%d", &num);
        
        if (error == 1) {
            if (num <= 0 || num > 6) {
                error = num;
            } 
        }
        
        if (pre_num == 1) {
            sum += 2*num;
        } else {
            sum += num;
        }
         
        pre_num = num;
        count += 1;
        
    }
    
    if (error == 1) {
        printf("The sum of dice rolls is %d.\n", sum);
    } else {
        printf("%d is not a number on a 6-sided dice.\n", error);
    }
    
    return 0;

}
