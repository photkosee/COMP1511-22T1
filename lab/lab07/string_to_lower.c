// String to Lower
// string_to_lower.c
//
// This program was written by Phot Koseekrainiramon (z5387411)
// on 29/03/2022
//
// A program C which takes a string and converts it to lower case
//
#include <stdio.h>
#include <string.h>

void string_to_lower(char *string);

int main(int argc, char *argv[]) {

    char str[1024] = "Hi, mY nAmE iS sPonGEbOb sQuArePanTS.";
    string_to_lower(str);
    printf("%s\n", str);

    return 0;
}

// Convert the characters in `buffer` to lower case
void string_to_lower(char *string) {
    // YOUR CODE GOES HERE!
    int length = strlen(string);
    int i = 0;
    while (i < length) {
        
        if (string[i] == 'A') {
            string[i] = 'a';
        } else if (string[i] == 'B') {
            string[i] = 'b';
        } else if (string[i] == 'C') {
            string[i] = 'c';
        } else if (string[i] == 'D') {
            string[i] = 'd';
        } else if (string[i] == 'E') {
            string[i] = 'e';
        } else if (string[i] == 'F') {
            string[i] = 'f';
        } else if (string[i] == 'G') {
            string[i] = 'g';
        } else if (string[i] == 'H') {
            string[i] = 'h';
        } else if (string[i] == 'I') {
            string[i] = 'i';
        } else if (string[i] == 'J') {
            string[i] = 'j';
        } else if (string[i] == 'K') {
            string[i] = 'k';
        } else if (string[i] == 'L') {
            string[i] = 'l';
        } else if (string[i] == 'M') {
            string[i] = 'm';
        } else if (string[i] == 'N') {
            string[i] = 'n';
        } else if (string[i] == 'O') {
            string[i] = 'o';
        } else if (string[i] == 'P') {
            string[i] = 'p';
        } else if (string[i] == 'Q') {
            string[i] = 'q';
        } else if (string[i] == 'R') {
            string[i] = 'r';
        } else if (string[i] == 'S') {
            string[i] = 's';
        } else if (string[i] == 'T') {
            string[i] = 't';
        } else if (string[i] == 'U') {
            string[i] = 'u';
        } else if (string[i] == 'V') {
            string[i] = 'v';
        } else if (string[i] == 'W') {
            string[i] = 'w';
        } else if (string[i] == 'X') {
            string[i] = 'x';
        } else if (string[i] == 'Y') {
            string[i] = 'y';
        } else if (string[i] == 'Z') {
            string[i] = 'z';
        }
        i++; 
    }
    
}
