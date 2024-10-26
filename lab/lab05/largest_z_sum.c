// Find the largest sum of numbers in a z shape.
// largest_z_sum.c
// Phot Koseekrainiramon (5387411)
// 27/03/2022

#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 100

int largest_z_sum(int size, int array[MAX_SIZE][MAX_SIZE]);
void find_larger(int sum, int *sum_largest);
void z_sum(int array[MAX_SIZE][MAX_SIZE], int size_minimum, int *sum, 
            int start_row, int end_col);
void find_sum(int *sum, int count_col, int end_col, 
              int array[MAX_SIZE][MAX_SIZE], int start_row, int end_row);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    int array[MAX_SIZE][MAX_SIZE];

    // Get the array size.
    int size;
    printf("Enter 2D array side length: ");
    scanf("%d", &size);
    assert(size >= 3);

    // Scan in values for the array.
    printf("Enter 2D array values:\n");
    int i = 0;
    while (i < size) {
        int j = 0;
        while (j < size) {
            assert(scanf("%d", &array[i][j]) == 1);
            j++;
        }
        i++;
    }

    printf("The largest z sum is %d.\n", largest_z_sum(size, array));

    return 0;
}

void find_larger(int sum, int *sum_largest) {
    if (sum >= *sum_largest) {
        *sum_largest = sum;
    }
}

void find_sum(int *sum, int count_col, int end_col, 
              int array[MAX_SIZE][MAX_SIZE], int start_row, int end_row) {
    while (count_col <= end_col) {
        *sum += array[start_row][count_col];
        *sum += array[end_row][count_col];                   
        count_col++;                   
    }
}
                
// Return the largest sum of numbers in a z shape.
void z_sum(int array[MAX_SIZE][MAX_SIZE], int size_minimum, int *sum, 
           int start_row, int end_col) {
    int i = 1;
    while (i < size_minimum) {
        *sum += array[start_row + i][end_col - i];
        i++;
    }
}

int largest_z_sum(int size, int array[MAX_SIZE][MAX_SIZE]) {
    // Put your code here.
    int sum = 0;
    int sum_largest = 0;
    int start_row = 0;
    int start_col = 0;
    int size_minimum = 2;
    int count_col;
    int end_row;
    int end_col;
    
    while (start_row < size) {
        while (start_col < size) {

            end_row = size_minimum + start_row;
            end_col = size_minimum + start_col;
            
            while (end_row < size && end_col < size) {
            
                count_col = start_col;
                find_sum(&sum, count_col, end_col, array, start_row, end_row);
                z_sum(array, size_minimum, &sum, start_row, end_col);
                size_minimum++;
                end_row = size_minimum + start_row;
                end_col = size_minimum + start_col;
                find_larger(sum, &sum_largest);
                sum = 0;
                count_col = start_col;
            }
                       
            size_minimum = 2;           
            start_col++;            
        }
        start_col = 0;
        start_row++;   
    }     
    return sum_largest;
}
