// Phot Koseekrainiramon (z5387411)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE -1

struct node {
    struct node *next;
    int          data;
};

int mixed(struct node *head);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = mixed(head);
    printf("%d\n", result);

    return 0;
}

// mixed should return 1 if list contains both even and odd numbers
// mixed should return 0 otherwise
int mixed(struct node *head) {

    // PUT YOUR CODE HERE (change the next line!)
    int check_even = FALSE;
    int check_odd = FALSE;
    struct node *current = head;
    while (current != NULL) {
        if ((current->data) % 2 == 0) {
            check_even = TRUE;
        } else {
            check_odd = TRUE;
        }
        current = current->next;
    }
    
    if (check_odd == TRUE && check_even == TRUE) {
        return 1;
    } else {
        return 0;
    }

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
