// Phot Koseekrainiramon (z5387411)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 100

int main(void) {
           
    int sum = 0;
    char buffer1[MAX_STRING_LEN];
    char buffer2[MAX_STRING_LEN];
    scanf("%s%s", buffer1, buffer2);
    for (int i = 0; i < strlen(buffer1); i++) { 
        int count = 0;
        for (int j = 0; j < strlen(buffer2); j++) {
            if (buffer1[i] == buffer2[j]) {
                buffer2[j] = 'A';
                count++;
            } else if (buffer2[j] != 'A' && buffer1[i] > '[') {
                if (buffer1[i] - 32 == buffer2[j]) {
                    buffer2[j] = 'A';
                    count++;
                }
            } else if (buffer2[j] != 'A' && buffer1[i] + 32 == buffer2[j]) {
                    buffer2[j] = 'A';
                    count++;

            }

        }
        if (count > 0) {
            sum++;
        }
    }

    printf("\n%d\n", sum);
    
}

