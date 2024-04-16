// decode.c
// by Phot Koseekrainiramon (z5387411)
// 04/04/2022
// A program C which reads characters from its input and writes the characters 
// to its output encrypted with a Substitution cipher but in backward way.

#include <stdio.h>

#define MAX_LENGTH 1024
#define MAP_LENGTH 27 
#define TRUE 1 
#define FALSE 0 

void print_caesar(int i, char map[MAP_LENGTH], char word[MAX_LENGTH]);

int main(void) {
    
    char map[MAP_LENGTH];
    char word[MAX_LENGTH];
    
    printf("Enter mapping: \n");
    fgets(map, MAP_LENGTH, stdin);

        
    printf("Enter text: \n");
    
	while (fgets(word, MAX_LENGTH, stdin) != NULL) {
	   	    	   	
	    int check_string = FALSE;
	    int i = 0;
	    while (word[i] != '\n' && word[i] != '\0') {	    
	        print_caesar(i, map, word);
	        i++;
	        check_string = TRUE;
	    }
	    if (word[i] == '\n' && check_string == TRUE) {
	        printf("\n");
	    }
    }
    return 0;
}

void print_caesar(int i, char map[MAP_LENGTH], char word[MAX_LENGTH]) {

    int j = 0;
    char index = 'a';
    int check_string = FALSE;
      
    while (j < 26 && check_string == FALSE) {
        index = 'a' + j;
        if (word[i] == map[j]) {
            word[i] = index;
            check_string = TRUE;
        }
        j++;
    }
    
    j = 0;
    while (j < 26 && check_string == FALSE) {
        index = 'A' + j;
        if (word[i] == map[j] - 32) {
            word[i] = index;
            check_string = TRUE;
        }
        j++;
    }

    printf("%c", word[i]);
}


