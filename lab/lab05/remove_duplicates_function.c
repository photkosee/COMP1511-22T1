// remove_duplicates_function.c
// A function that removes all duplicates in an given array.
// 27/03/2022
// Phot Koseekrainiramon (5387411)

#include<stdio.h>

int remove_duplicates(int length, int source[length], int destination[length]) {
    int i = 0;
    int j = 0;
    int integer = 0;
    int count_same = 0;
    while (i < length) {
        while (integer != 0 && j < integer) {
            if (source[i] == destination[j]) {
                count_same++;
            }
            j++;   
        }
        if (count_same == 0) {
            destination[integer] = source[i];
            integer++;           
        }
        count_same = 0;
        i++;
        j = 0;
    }    
    return integer;
}

int main(void) {

}
