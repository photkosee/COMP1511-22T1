// sawtooth.c
// Phot Koseekrainiramon (5387411)
// A program drawing sawtooth form given integers
// 06/03/2022

#include <stdio.h>

int main(void) {
    
    int height;
    int length;
    int x = 1;
    int y = 1;
    int n = 1;
    int i = 0;
    
    printf("Please enter the height of the sawtooth: ");
    scanf("%d", &height);
    printf("Please enter the length of the sawtooth: ");
    scanf("%d", &length);
    
    while (x <= height) {
        while (y <= length) {
              
            if (n == 1) {         
                if (y == 1 || y == x + i) {
                    printf("*");
                } else if (y != length) {
                    printf(" ");
                } 
            } else {
                if (y == 1 || y % n == 0 || y == x + i) {
                    printf("*");
                } else if (y != length) {
                    printf(" ");
                } 
            }
            
            if (y % height == 0) {
                n += height;
                i += height;
            } 
            
            if (y == length) {
                printf("\n");
            } 
            
            y++;
        }
        
        x++;
        y = 1;
        n = 1;
        i = 0;
    }

}
