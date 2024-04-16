// Phot Koseekrainiramon (z5387411)

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int array[10000];
    int j = 0;
    while (scanf("%d", &array[j]) && array[j] != 0) {
        j++;
    }

    for (int i = 0; i < j; i += 2) {
        printf("%d ", array[i]);
    }
    for (int i = 1; i < j; i += 2) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
