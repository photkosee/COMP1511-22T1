// A program rearranging given integers in order of higher to lower
// reverse_array.c
// by Phot Koseekrainiramon (5387411)
// 13/03/2022
// COMP1511 Lab 4 Exercise 5

#include <stdio.h>

#define MAX_SIZE 100

void arrange(int length, int numbers[MAX_SIZE]);

int main(void) {
    int num[MAX_SIZE]; 
    int index = 0;     
    printf("Enter numbers forwards: ");   
    while (scanf("%d", &num[index]) != EOF) {
        index++;    
    }   
    printf("\n");
    arrange(index, num);
    return 0;
}

void arrange(int length, int numbers[MAX_SIZE]) {   
    int count = length - 1;
    printf("Reversed: \n");
    while (count >= 0) {
        printf("%d\n", numbers[count]);
        count--;
    }
    return;
}

