// spiral.c
// A program creating spiral from asterisks by given n*n square.
// Phot Koseekrainiramon (5387411)
// 06/03/2022

#include <stdio.h>

int main(void) {
    
    int size; 
    int x = 1;
    int y = 1;
    int middle;
    int i = 1;
    int j = 0;
    int k = 0;
    int p = 1;
    
    printf("Enter size: ");
    scanf("%d", &size);
    middle = (size + 1) / 2; 
    
    while (x <= size) {
        while (y <= size) {
            if (x == 1 || x == size || y == size) {
                printf("*");
            } else if (x % 2 == 0 && x <= middle) {
                if (y == i || y == size - j) {
                    printf("*");
                    i += 2;                    
                    j += 2;
                } else {
                    printf("-");
                }
            } else if (x % 2 != 0 && x <= middle) {
                if (y == k || y == size - p) {
                    printf("-");
                    k += 2;                    
                    p += 2;
                } else {
                    printf("*");
                }           
            }
            
            if (y == size) {
                printf("\n");
            }
            
            y++;
        }
        y = 1;
        x++;
        i = 1;
        j = 0;
        k = 0;
        p = 1;
    }
}
