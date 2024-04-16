// A program reads in a character and an integer
// get_letter.c
// Written 22/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 02 Exercise 3

#include <stdio.h>

int main(void) {
    
    char upper_case;
    int number;
    char letter;
    
    printf("Uppercase: ");
    scanf("%c", &upper_case);
    
    if (upper_case == 'n') {
        printf("Index: ");
        scanf(" %d", &number);
        if (number < 1 || number > 26) {
            printf("You need to enter a number between 1 and 26 inclusive\n");
            printf("Exiting the program with error code 2\n");
        } else {
            letter = '`' + number;
            printf("The letter is %c\n", letter);
        }
    } else if (upper_case == 'y') {
        printf("Index: ");
        scanf(" %d", &number);
        if (number < 1 || number > 26) {
            printf("You need to enter a number between 1 and 26 inclusive\n");
            printf("Exiting the program with error code 2\n");
        } else {
            letter = '@' + number;
            printf("The letter is %c\n", letter);
        }
    } else {
        printf("You need to enter 'y' or 'n'\n");
        printf("Exiting the program with error code 1\n");
    }
    
}
