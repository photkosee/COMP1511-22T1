// caesar.c
// by Phot Koseekrainiramon (z5387411)
// 03/04/2022
// A program C which reads characters from its input and writes the 
// characters to its output encrypted with a Caesar cipher.

#include <stdio.h>

#define MAX_LENGTH 1024
#define TRUE 1
#define FALSE 0

void print_caesar(int i, int shift, char word[MAX_LENGTH]);

int main(void) {

    char word[MAX_LENGTH];
    int shift;
    
    scanf("%d", &shift);
    if (shift > 26 || shift < -26) {
        shift %= 26;
    }
    
	while (fgets(word, MAX_LENGTH, stdin) != NULL) {
	   	    	   	
	    int i = 0;
	    int check_string = FALSE;
	    while (word[i] != '\0' && word[i] != '\n') {	    
	        print_caesar(i, shift, word);
	        i++;
            check_string = TRUE;
	    }
	    if (word[i] == '\n' && check_string == TRUE) {
	        printf("\n");
	    }

    }
    return 0;
}

void print_caesar(int i, int shift, char word[MAX_LENGTH]) {
    if (word[i] >= 'A' && word[i] <= 'Z') {
        word[i] = word[i] + shift;
        if (word[i] > 'Z') {
            word[i] = word[i] - 26;
        } else if (word[i] < 'A') {
            word[i] = word[i] + 26;
        }
    } else if (word[i] >= 'a' && word[i] <= 'z') {
        if (shift >= 0) {
            word[i] = word[i] - (26 - shift);
            if (word[i] < 'a') {
                word[i] = word[i] + 26;
            }
        } else {
            word[i] = word[i] + shift;
            if (word[i] < 'a') {
                word[i] = word[i] + 26;
            }
        }       
    } 
    
    printf("%c", word[i]);
}


