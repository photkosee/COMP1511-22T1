// word_square.c
// by Phot Koseekrainiramon (z5387411)
// 29/03/2022
// A program C that prompts the user to enter a word, and afterwards, 
// prints that word out n amount of times, where n is the length of the word.

#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 1024

int main(void) {

    char word[MAX_LENGTH];
    
    printf("Input word: ");
    fgets(word, MAX_LENGTH, stdin);
    
    int length = strlen(word);
    printf("\nWord square is:\n");
    int i = 1;
    while (i < length) {
        printf("%s", word);
        i++;
    }
    return 0;
    
}
