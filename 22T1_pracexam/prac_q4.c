// Phot Koseekrainiramon (z5387411)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int product(struct node *head1, struct node *head2);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1]);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1]);

    int result = product(head1, head2);
    printf("%d\n", result);

    return 0;
}

// product should return the sum of the elements in list1 multiplied by 
// the corresponding element in list2
// if one list is longer than the other, the extra list elements are ignored 
int product(struct node *head1, struct node *head2) {

    // PUT YOUR CODE HERE (change the next line!)
    struct node *current1 = head1;
    struct node *current2 = head2;
    int sum = 0; int count_list1 = 0; int count_list2 = 0;
    while (current1 != NULL) {
        count_list1 += 1;
        current1 = current1->next;
    }
    while (current2 != NULL) {
        count_list2 += 1;
        current2 = current2->next;
    }
    current1 = head1;
    current2 = head2;
    if (count_list1 >= count_list2) {
        while (current2 != NULL) {
            sum += (current1->data) * (current2->data);
            current2 = current2->next;
            current1 = current1->next;
        }        
    } else {
        while (current1 != NULL) {
            sum += (current1->data) * (current2->data);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
       
    return sum;

}


// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}
