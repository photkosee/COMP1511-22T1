// A simple C program to make an x from given integer n*n.
// x.c
// Written 28/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 03 Exercise 4

#include <stdio.h>

int main(void) {

    int size;
    int x = 1;
    int y = 1;
    int count;
    
    printf("Enter size: ");
    scanf("%d", &size);
    count = size;
        
    while (x <= size) {
        
        while (y <= size) {
            
            if (x == y) {
                printf("*");                   
            } else if (y == count) {
                printf("*");
            } else {
                printf("-");
            }
                
            y += 1;
                
        }
                                
        printf("\n");
            
        x += 1;
        y = 1;
        count -= 1;
            
    }
       
    return 0;   

}
