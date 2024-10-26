// Phot Koseekrainiramon (z5387411)
// Starter code for exam_q3.

#include <stdio.h>

#define MAX_SIZE 10000

int main(void) {
    // Add code to the main function to implement exam_q3!
    int x[MAX_SIZE];
    int i = 0;
    int repeat = 0;
    
    while (repeat == 0 && scanf("%d", &x[i]) == 1) {
        int j = 0;
        while (j < i) {
            if (x[j] == x[i]) {
                repeat = x[i];
            }
            j++;
        }
        
        i++;
    }
    
    printf("%d is repeated\n", repeat);
    return 0;
}
