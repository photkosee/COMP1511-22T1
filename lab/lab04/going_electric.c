// A program showing the minimum number of stops until the end of your journey
// going_electric.c
// by Phot Koseekrainiramon (5387411)
// 14/03/2022
// COMP1511 Lab 4 Exercise 6

#include <stdio.h>

#define MAX_SIZE 10000

int main(void) {

    int count = 0;
    int num[MAX_SIZE];
    int stop = 0;
    int index = 1;
    int charge = 0;
    int fail = 0;
    int charge2 = 0;
    int stop2 = 0;
    int fail2 = 0;

    while (scanf("%d", &num[count]) != EOF) {
        count++;   
    }
    
    if (num[0] > 0) {
        charge = num[0];
        charge2 = num[0];
        stop++;
        stop2++;
    } else {
        fail = 1;
    }
    
    
    while (index < count && num[0] > 0) {
        charge--;
        charge2--;
        
        if (charge == 0 && num[index] != 0 && index != count - 1) {
            charge = num[index];
            stop++;
        } else if (index + charge + 1 < count && num[index] != 0) {
            if (num[index + charge] == 0 && num[index + charge + 1] == 0) {
                charge = num[index];
                stop++;
            }
        }        
        
        if (num[index] != 0 && charge >= 0) {
            charge2 += num[index];
            stop2++;
        }
        
        if (charge < 0 && num[index] == 0) {
            fail = 1;
        }
        if (charge2 < 0 && num[index] == 0) {
            fail2 = 1;
        }
        
        index++;
    }
           
    if (fail == 0 && fail2 == 0) {
        if (stop2 < stop) {
            printf("%d\n", stop2);
        } else if (stop <= stop2) {
            printf("%d\n", stop);
        }
    } else if (fail == 0) {
        printf("%d\n", stop);
    } else if (fail2 == 0) {
        printf("%d\n", stop2);
    } else {
        printf("0\n");
    }
    
    return 0;
}
