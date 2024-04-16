// A calculator program
// cs_calculator.c
// by Phot Koseekrainiramon (5387411)
// 11/03/2022
// COMP1511 Lab 4 Exercise 4

#include <stdio.h>

void square(int square);
void power(int power1, int power2);

int main(void) {
    
    int num1;
    int num2;
    char letter;
    
    printf("Enter instruction: ");
    while (scanf(" %c", &letter) != EOF) {
        
        if (letter == 's') {
            scanf(" %d", &num1);
            square(num1);
        } else if (letter == 'p') {
            scanf(" %d %d", &num1, &num2);
            power(num1, num2);
        }
        
        printf("Enter instruction: ");
    }
    return 0;

}

void square(int square) {
    int ans;
    ans = square * square;
    printf("%d\n", ans);
    return;
}

void power(int power1, int power2) {
    int ans = 1;
    int i = 0;
    while (i < power2) {
        ans *= power1;
        i++;
    }
    printf("%d\n", ans);
    return;
} 
