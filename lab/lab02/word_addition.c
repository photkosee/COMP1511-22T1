// A simple C program to change numbers into words.
// word_addition.c
// Written 23/2/2022
// by Phot Koseekrainiramon (z5387411)
// for COMP1511 Lab 02 Exercise 6

#include <stdio.h>

int main(void){
    
    int number1;
    int number2;
    int sum;
    
    printf("Please enter two integers: ");
    scanf("%d %d", &number1, &number2);
    
    sum = number1 + number2;
    
    if (number1 == -10) {
        printf("negative ten");
    } else if (number1 == -9) {
        printf("negative nine");
    } else if (number1 == -8) {
        printf("negative eight");
    } else if (number1 == -7) {
        printf("negative seven");
    } else if (number1 == -6) {
        printf("negative six");
    } else if (number1 == -5) {
        printf("negative five");
    } else if (number1 == -4) {
        printf("negative four");
    } else if (number1 == -3) {
        printf("negative three");
    } else if (number1 == -2) {
        printf("negative two");
    } else if (number1 == -1) {
        printf("negative one");
    } else if (number1 == 0) {
        printf("zero");
    } else if (number1 == 1) {
        printf("one");
    } else if (number1 == 2) {
        printf("two");
    } else if (number1 == 3) {
        printf("three");
    } else if (number1 == 4) {
        printf("four");
    } else if (number1 == 5) {
        printf("five");
    } else if (number1 == 6) {
        printf("six");
    } else if (number1 == 7) {
        printf("seven");
    } else if (number1 == 8) {
        printf("eight");
    } else if (number1 == 9) {
        printf("nine");
    } else if (number1 == 10) {
        printf("ten");
    } else {
        printf("%d", number1);
    }
           
    if (number2 == -10) {
        printf(" + negative ten");
    } else if (number2 == -9) {
        printf(" + negative nine");
    } else if (number2 == -8) {
        printf(" + negative eight");
    } else if (number2 == -7) {
        printf(" + negative seven");
    } else if (number2 == -6) {
        printf(" + negative six");
    } else if (number2 == -5) {
        printf(" + negative five");
    } else if (number2 == -4) {
        printf(" + negative four");
    } else if (number2 == -3) {
        printf(" + negative three");
    } else if (number2 == -2) {
        printf(" + negative two");
    } else if (number2 == -1) {
        printf(" + negative one");
    } else if (number2 == 0) {
        printf(" + zero");
    } else if (number2 == 1) {
        printf(" + one");
    } else if (number2 == 2) {
        printf(" + two");
    } else if (number2 == 3) {
        printf(" + three");
    } else if (number2 == 4) {
        printf(" + four");
    } else if (number2 == 5) {
        printf(" + five");
    } else if (number2 == 6) {
        printf(" + six");
    } else if (number2 == 7) {
        printf(" + seven");
    } else if (number2 == 8) {
        printf(" + eight");
    } else if (number2 == 9) {
        printf(" + nine");
    } else if (number2 == 10) {
        printf(" + ten");
    } else {
        printf(" + %d", number2);
    }
              
    if (sum == -10) {
        printf(" = negative ten\n");
    } else if (sum == -9) {
        printf(" = negative nine\n");
    } else if (sum == -8) {
        printf(" = negative eight\n");
    } else if (sum == -7) {
        printf(" = negative seven\n");
    } else if (sum == -6) {
        printf(" = negative six\n");
    } else if (sum == -5) {
        printf(" = negative five\n");
    } else if (sum == -4) {
        printf(" = negative four\n");
    } else if (sum == -3) {
        printf(" = negative three\n");
    } else if (sum == -2) {
        printf(" = negative two\n");
    } else if (sum == -1) {
        printf(" = negative one\n");
    } else if (sum == 0) {
        printf(" = zero\n");
    } else if (sum == 1) {
        printf(" = one\n");
    } else if (sum == 2) {
        printf(" = two\n");
    } else if (sum == 3) {
        printf(" = three\n");
    } else if (sum == 4) {
        printf(" = four\n");
    } else if (sum == 5) {
        printf(" = five\n");
    } else if (sum == 6) {
        printf(" = six\n");
    } else if (sum == 7) {
        printf(" = seven\n");
    } else if (sum == 8) {
        printf(" = eight\n");
    } else if (sum == 9) {
        printf(" = nine\n");
    } else if (sum == 10) {
        printf(" = ten\n");
    } else {
        printf(" = %d\n", sum);
    }
        
}
