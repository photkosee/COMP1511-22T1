// Phot Koseekrainiramon (z5387411)

#include <stdio.h>
#include <stdlib.h>
#include "points.h"

struct node {
    double x;
    double y
    struct node *next;
};
struct node *insert_tail(double value_x, double value_y, struct node *head) {

    struct node *new_tail = malloc(sizeof(struct node));
    struct node *current = head;
    int check_null = 0;
    
    new_tail->x = value_x;
    new_tail->y = value_y;    
    new_tail->next = NULL;
    
    if (head == NULL && new_tail != NULL) {
        head = new_tail;
        check_null = 1;
    }
            
    while (check_null == 0 && current->next != NULL) {
        current = current->next;
    }
    
    if (check_null == 0) {
        current->next = new_tail;
    }
    
    return head;

}
int main(void) {    

    // NOTE: The functions in 'points.h' will be essential to completing this task.
    struct point point[1000];
    struct node *head = NULL;
    int i = 0;
    while (scanf("%lf %lf", &point[i].x, &point[i].y) != EOF) {
        i++;
    }
    int j = 0;

        while (j <= i) {
            head = insert_tail(point[j].x, point[j].y, head);
            int k = j + 1;
            while (k <= i) {
                if (points_equal(point[j], point[k]) == 0) {
                    
                }
                k++;
            }
            j++;
        }


    return 0;
}
