// A simple C program to create n boxes inside a boxe by given integer.
// boxes.c
// Written 28/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 03 Exercise 6

#include <stdio.h>

int main(void) {
    
    int num;
    int total;
    int x = 1;
    int y = 1;
    int odd;
    int count = 1;
    int mid;
    int count2 = 2;
    
    printf("How many boxes: ");
    scanf("%d", &num);
    
    total = 3 + 4*(num - 1);
    odd = 1 + 2*(num - 1);
    mid = total - odd; 
    
    while (x <= total) {
    
        while (y <= total) {  
          
            if (x == 1 || x == total) {    
                printf("*");
            } else if (x % 2 == 0 && x < mid && 
                       count <= x && y < mid && y == count) {            
                printf("*");
                count += 2;                            
            } else if (x % 2 == 0 && x < mid && y == total - count + 3) {
                printf("*");
                count -= 2;                              
            } else if (x == mid && y % 2 == 0) {
                printf("-");
            } else if (x == mid && y % 2 != 0) {
                printf("*");
            } else if (x % 2 == 0 && x > mid && 
                       count <= total - x && y < mid && y == count) {
                printf("*");
                count += 2;                            
            } else if (x % 2 == 0 && x > mid && y == total - count + 3) {
                printf("*");
                count -= 2;
            } else if (x % 2 == 0) {
                printf("-");
            } else if (x % 2 != 0 && x < mid && 
                       count2 <= x && y < mid && y == count2) {
                printf("-");
                count2 += 2;                            
            } else if (x % 2 != 0 && x < mid && y == total - count2 + 3) {
                printf("-");
                count2 -= 2;        
            } else if (x % 2 != 0 && x > mid && 
                       count2 <= total - x && y < mid && y == count2) {
                printf("-");
                count2 += 2;                           
            } else if (x % 2 != 0 && x > mid && y == total - count2 + 3) {
                printf("-");
                count2 -= 2;
            } else {
                printf("*");
            }
            y += 1;           
        }   
        printf("\n");  
        x += 1;
        y = 1;
        count = 1;
        count2 = 2;
    }  
        
    return 0;
    
}
