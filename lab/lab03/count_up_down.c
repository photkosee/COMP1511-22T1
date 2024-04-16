// A simpls program counting 0 to n.
// count_up_down.c
// Written 28/02/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 03 Exercise 1

#include <stdio.h>

int main(void) {

    int num;
    int count = 0;
    
    printf("Enter number: ");
    scanf("%d", &num);
    
    if (num >= 0) {
        while (count <= num) {
            printf("%d\n", count);
            count += 1;
        }
    } else {
        while (count >= num) {
            printf("%d\n", count);
            count -= 1;
        }
    }
    
    return 0;
}
