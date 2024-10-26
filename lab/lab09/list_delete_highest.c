// list_delete_highest.c
// by Phot Koseekrainiramon (z5387411)
// 13/04/2022
// A C program deleting the highest values in a given linked list.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_LIST_LEN 100

struct node {
    struct node *next;
    int          data;
};

struct node *delete_highest(struct node *head);
struct node *array_to_list(int len, int array[]);
void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    // scan in quantity of numbers
    printf("Total numbers in list: ");
    int list_size;
    scanf(" %d", &list_size);

    // scan numbers into array
    int n_read = 0;
    int numbers_list[MAX_LIST_LEN] = {0};
    while (n_read < list_size && scanf(" %d", &numbers_list[n_read])) {
        n_read++;
    }

    // create linked list from inputs
    struct node *head = array_to_list(n_read, numbers_list);

    struct node *new_head = delete_highest(head);
    print_list(new_head);

    return 0;
}


//
// Delete the node(s) in the list that contain the highest value
// The deleted node(s) are freed.
// The head of the list is returned.
//
struct node *delete_highest(struct node *head) {

    // PUT YOUR CODE HERE (change the next line!)
    if (head != NULL) {
        struct node *check_highest = head;
        struct node *check_highest2 = head;
        int highest = check_highest->data;
 
        while (check_highest->next != NULL) {
            if (check_highest->data <= check_highest->next->data) {
                highest = check_highest->next->data;
            }
            check_highest = check_highest->next;       
        }
        
        int count = 0;
        while (check_highest2->next != NULL) {
            if (check_highest2->data == highest) {
                count++;
            }
            check_highest2 = check_highest2->next;       
        }
    
        struct node *tmp = head;
        struct node *prev = NULL;
        
        if ((tmp != NULL && tmp->data == highest) || tmp == NULL) {
            head = tmp->next;
            free(tmp);
            count--;
        } 
        int i = 0;
        while (count >= i) {
            struct node *current = head;
            while (current->next != NULL && current->data != highest) {
                prev = current;
                current = current->next;
            }
            prev->next = current->next;
            free(current);
            i++;
        }
    }
    return head;

}


// DO NOT CHANGE THIS FUNCTION
// create linked list from array of ints
struct node *array_to_list(int len, int array[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = array[i];
        head = n;
        i -= 1;
    }   
    return head;
}

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");    
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}
