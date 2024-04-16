// Phot Koseekrainiramon (z5387411)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Do not change these #defines, or your program will fail the autotests!
#define TRUE 1
#define FALSE 0

#define MAX_REGEX_SIZE 128

void delete_string(char *x, int a, int b)
{   
	if ((a+b-1) <= strlen(x))
	{
		strcpy(&x[b-1],&x[a+b-1]);
		puts(x);
	}
}
// matches should return TRUE if the string `text` matches the
// regular expression `regex`, or FALSE otherwise.
int matches(char *regex, char *text) {
    
    int i = 0;
    int braces = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    char group[MAX_REGEX_SIZE];
    char count_group[MAX_REGEX_SIZE];
    char position[MAX_REGEX_SIZE];
    int pre_j = 0;
    while (regex[i] != '\0') {
        if (regex[i] == '[') {
            braces = 1;
            position[m] = i;
            m++;
        } else if (regex[i] == ']') {
            braces = 0;
            count_group[k] = j - pre_j;
            pre_j += j;
            k++;
        } else if (braces == 1) {
            group[j] = regex[i];
            j++;
        }
        
        i++;
    }
    int check = FALSE;
    j = 0;
    int length = strlen(position);
    k = length;
    while (j < length) {
        char new_regex = *regex;
        for (i = length - 1; i >= 0; i -= 2) {
            new_regex = strncat(&regex[position[i] + 1], &group[k], 1);
            delete_string(&new_regex, position[i-1], position[i]);
            k -= count_group[k];
        }
        if (strcmp(&new_regex, text) == 0) {
            check = TRUE;
        }
        j++;
        k = length;
        k -= j;
    }
    
    if (check == TRUE) {          
        return TRUE;
    } else {
        return FALSE;
    }  
    
}


////////////////////////////////////////////////////////////////////////
//               DO NOT CHANGE THE CODE BELOW                         //
////////////////////////////////////////////////////////////////////////

int scan_regex(char *regex);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // Check that we got the right number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s text_to_match\n", argv[0]);
        exit(1);
    }

    char *text = argv[1];
    char regex[MAX_REGEX_SIZE];;

    while (scan_regex(regex)) {
        if (matches(regex, text)) {
            printf("MATCH\n");
        } else {
            printf("NO_MATCH\n");
        }
    }

    return 0;
}


// DO NOT CHANGE THIS FUNCTION
// Scans in a line with fgets, and removes the newline character (if
// there was one).
// Returns 1 if it managed to read a line, and 0 otherwise.
int scan_regex(char *regex) {
    if (fgets(regex, MAX_REGEX_SIZE, stdin) == NULL) {
        return 0;
    }

    // If the line from fgets contains a newline, replace it with a '\0'.
    regex[strcspn(regex, "\n")] = '\0';

    return 1;
}
