// devowel.c
// By Phot Koseekrainiramon (z5387411)
// 29/03/2022
// A C program which reads characters from its input and writes the same 
// characters to its output, except it does not write lower case vowels 
// ('a', 'e', 'i', 'o', 'u').

#include<stdio.h>

#define MAX_LENGTH 50
#define VOWEL 5

void remove_vowel(int i, char vowel[VOWEL], char word[MAX_LENGTH]);

int main(void) {
	char vowel[VOWEL] = {'a', 'e', 'i', 'o', 'u'};
	char word[MAX_LENGTH];
	while (fgets(word, MAX_LENGTH, stdin) != NULL) {
	    int i = 0;
	    while (word[i] != '\0') {	    
	        remove_vowel(i, vowel, word);
	        i++;
	    }
    }
	return 0;
}

void remove_vowel(int i, char vowel[VOWEL], char word[MAX_LENGTH]) {
    int j = 0;
    int check_vowel = 0;
    while (j < VOWEL) {
        if (word[i] != vowel[j]) {
            check_vowel++;
        }
        j++;
    }
    if (check_vowel == 5) {
        printf("%c", word[i]);
    }
}

