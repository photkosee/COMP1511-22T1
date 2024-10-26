// CS Airline Manifest
// manifest.c
//
// This program was written by Phot Koseekrainiramon (z5387411)
// on 19/04/2022-21/04/2022
//
// Version 1.0.0 2022-04-02: Initial Release.
//
// A Seperate C file containing struct person and manifest related functions
// in order to combine with cs_airline.c to be able to rearrange manifests'
// information in the flight


#include "manifest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE -1

struct person {
    char name[MAX_NAME_LEN];
    double weight;
    struct person *next;
};

// Internal Function Prototypes
struct person *create_person(char name[MAX_NAME_LEN], double weight);

// Call malloc for new manifest
struct manifest *create_manifest() {
    struct manifest *manifest = malloc(sizeof(struct manifest));
    manifest->people = NULL;
    return manifest;
}

// Printing every people inside given manifest
void print_manifest(struct manifest *manifest) {
    printf("Manifest:\n");

    if (manifest == NULL) {
        return;
    }

    // Loop through list
    struct person *curr = manifest->people;
    while (curr != NULL) {
        printf("    %03.2lf - %s\n", curr->weight, curr->name);
        curr = curr->next;
    }
}

// PROVIDED FUNCTION
// Given person info, mallocs space for the person
// Parameters:
//     name        = name of the new person
//     weight      = weight of the new person
// Returns:
//     pointer to the malloc'd person
struct person *create_person(char name[MAX_NAME_LEN], double weight) {
    // Malloc the new person
    struct person *new_person = malloc(sizeof(struct person));

    // Copy data
    strcpy(new_person->name, name);
    new_person->weight = weight;
    new_person->next = NULL;

    return new_person;
}

// Adding new person's information to given manifest
void add_person(struct manifest *manifest, char name[MAX_NAME_LEN],
                double weight) {
    // Create a new person
    struct person *new_person = create_person(name, weight);

    // Check if list is empty
    if (manifest->people == NULL) {
        manifest->people = new_person;
        return;
    }

    // Find the end of the list
    struct person *curr = manifest->people;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    // Curr now points to the last person in the list
    // Add the new person to the end of the list
    curr->next = new_person;
}

// Freeing all called malloc inside manifest and itself
void delete_manifest(struct manifest *manifest) {

    if (manifest == NULL) {
        return;
    }

    // Free the list of people
    struct person *curr = manifest->people;
    while (curr != NULL) {
        
        struct person *temp = curr->next;
        free(curr);
        curr = temp;
    }

    // Free the malloc
    free(manifest);
}

// Calculate total weight of all people inside a given manifest
double manifest_weight(struct manifest *manifest) {
    
    double total_weight = 0;   
    if (manifest != NULL) {
        struct person *curr = manifest->people;    
        while (curr != NULL) {
            total_weight += curr->weight;
            curr = curr->next;
        }
    }
     
    return total_weight;
}

// Joining information of people inside one manifest to one another
struct manifest *join_manifest(struct manifest *manifest_1, struct manifest *manifest_2) {
     
    int check_null = FALSE; 
    if (manifest_1->people == NULL) {        
        check_null = TRUE;
    }
    
    struct person *curr_2 = manifest_2->people;
    while (curr_2 != NULL) {
        struct person *new_person = create_person(curr_2->name, curr_2->weight);
        if (check_null == TRUE) {
            manifest_1->people = new_person;
            check_null = FALSE;          
        } else {         
            struct person *curr_1 = manifest_1->people;
            // Find the end of the list
            while (curr_1->next != NULL) {
                curr_1 = curr_1->next;
            }    
            curr_1->next = new_person;
            curr_1 = curr_1->next;           
        }
        curr_2 = curr_2->next;
    }
           
    return manifest_1;
}
