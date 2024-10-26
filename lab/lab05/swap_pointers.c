// swap_pointers.c
// A program swapping number values
// Phot Koseekrainiramon (5387411)
// 15/03/2022
// COMP1511 Lab 5 Exercise 1

#include <stdio.h>

void swap_pointers(int *a, int *b);

// This is a simple main function which could be used
// to test your swap_pointers function.
// It will not be marked.
// Only your swap_pointers function will be marked.

int main(void) {
    int first = 1;
    int second = 2;
    
    swap_pointers(&first, &second);
    
    printf("%d, %d\n", first, second);
    return 0;
}

// swap the values in two integers, given as pointers
void swap_pointers(int *a, int *b) {
    // PUT YOUR CODE HERE (you must change the next line!)
    int c;
    c = *a;
    *a = *b;
    *b = c;
    
}
