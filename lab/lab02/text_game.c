// My Text Game
// text_game.c
//
// This program was written by Phot Koseekrainiramon (z5387411)
// on 24/02/2022
//
// A hangman game.

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int dif;

    printf("This is a hangman game.\n");
    printf("First of all, you have to choose game's difficulties by typing an integer from 1 to 5.\n");
    printf("Enter the difficulty: ");
    scanf("%d", &dif);
    
    if (dif == 1) {
        printf("Now the game begin! You have 10 chances to guess the right word.\n");
    } else if (dif == 2) {
        printf("Now the game begin! You have 9 chances to guess the right word.\n");
    } else if (dif == 3) {
        printf("Now the game begin! You have 8 chances to guess the right word.\n");
    } else if (dif == 4) {
        printf("Now the game begin! You have 7 chances to guess the right word.\n");
    } else if (dif == 5) {
        printf("Now the game begin! You have 6 chances to guess the right word.\n");
    } else {
        printf("You dare to challenge me!?! You have only 2 chances to guess the right word.\n");
    }
    
    while (1) {
        // TODO: Fill this in with the game
    }
    
    return 0;
}
