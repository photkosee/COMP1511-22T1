// CS Airline
// cs_airline.c
//
// This program was written by Phot Koseekrainiramon (z5387411)
// on 15/04/2022 - 22/04/2022
//
// Version 1.0.0 2022-04-02: Initial Release.
//
// A C program of booking system capable of managing a flight with 
// multiple stops.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manifest.h"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  CONSTANTS  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// The buffer length is used for reading a single line
#define MAX_STRING_LEN 100

#define COMMAND_PRINT_HELP "help"
#define COMMAND_PRINT_ROUTE "print"
#define COMMAND_SUBROUTE "subroute"
#define COMMAND_CHANGE_ORIGIN "change_origin"
#define COMMAND_BYPASS "bypass"
#define COMMAND_EMERGENCY "emergency"
#define COMMAND_CANCEL "cancel"
#define COMMAND_REVERSE "reverse"
#define COMMAND_ADD_PERSON "add_person"
#define COMMAND_PRINT_MANIFEST "print_manifest"
#define COMMAND_FLIGHT_STATS "stats"

#define TRUE 1
#define FALSE -1
#define CHANGE_TO_HOURS 100
#define EMERGENCY_CODE "ALT0"
#define EMERGENCY_DEPARTURE_TIME 0

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Airports represent 'stops' along the flight path
// These are the 'nodes' of the linked list
struct airport {
    char code[MAX_STRING_LEN];
    int arrival_time;
    int departure_time;
    struct airport *next_airport;
    struct manifest *manifest;
};

// Root flight structure
// This stores the state of the current flight
// (i.e. the head and tail of the linked list)
struct flight {
    struct airport *origin_airport;
    struct airport *dest_airport;
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Helper Functions
void remove_newline(char input[MAX_STRING_LEN]);
void do_print_help(void);

void interpret_line(
    char buffer[MAX_STRING_LEN],
    int *val0,
    int *val1,
    char word[MAX_STRING_LEN]
);

// Stage 1 Functions
struct flight *setup_flight(void);
void do_print_airports(struct flight *flight);
void print_one_airport(struct airport *ap);
struct airport *create_airport(
    char code[MAX_STRING_LEN],
    int arrival_time,
    int departure
);

// Stage 2 Functions
void do_subroute(struct flight *flight);
void do_change_origin(struct flight *flight);
void do_bypass(struct flight *flight);
void do_free_airport(struct airport *head);
// Stage 3 Functions
void do_emergency(struct flight *flight);
struct flight *do_cancel(struct flight *flight);
void do_reverse(struct flight *flight);
void do_free_flight(struct flight *flight);
// Stage 4 Functions
void do_add_person(struct flight *flight);
void do_print_manifest(struct flight *flight);
void do_stats(struct flight *flight);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION IMPLEMENTATIONS  //////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    // Stage 1.1
    struct flight *flight = setup_flight();                 
    printf("Enter Command: ");
    char command_line[MAX_STRING_LEN];
    while (fgets(command_line, MAX_STRING_LEN, stdin) != NULL) {
        remove_newline(command_line);
        if (strcmp(COMMAND_PRINT_HELP, command_line) == 0) {
            // A help command we have implemented for you.
            do_print_help();
        } else if (strcmp(COMMAND_PRINT_ROUTE, command_line) == 0) {
            // Stage 1.2
            do_print_airports(flight);
        } else if (strcmp(COMMAND_SUBROUTE, command_line) == 0) {
            // Stage 2.1
            do_subroute(flight);
        } else if (strcmp(COMMAND_CHANGE_ORIGIN, command_line) == 0) {
            // Stage 2.2
            do_change_origin(flight);
        } else if (strcmp(COMMAND_BYPASS, command_line) == 0) {
            // Stage 2.3
            do_bypass(flight);
        } else if (strcmp(COMMAND_EMERGENCY, command_line) == 0) {
            // Stage 3.1
            do_emergency(flight);
        } else if (strcmp(COMMAND_CANCEL, command_line) == 0) {
            // Stage 3.2
            flight = do_cancel(flight);           
        } else if (strcmp(COMMAND_REVERSE, command_line) == 0) {
            // Stage 3.3
            do_reverse(flight);
        } else if (strcmp(COMMAND_ADD_PERSON, command_line) == 0) {
            // Stage 4.1
            do_add_person(flight);
        } else if (strcmp(COMMAND_PRINT_MANIFEST, command_line) == 0) {
            // Stage 4.2
            do_print_manifest(flight);
        } else if (strcmp(COMMAND_FLIGHT_STATS, command_line) == 0) {
            // Stage 4.3
            do_stats(flight);
        }       
        printf("Enter Command: ");
    }   
    // Freeing everything brfore ending the program
    do_free_flight(flight);
    printf("Goodbye!\n");   
    return 0;
}

// Stage 1.1
// Creates and initialises a flight by asking the user for input.
// Parameters:
//     None
// Returns:
//     Pointer to the malloc'd flight
struct flight *setup_flight(void) {
    // Create a new, empty flight
    struct flight *new_flight = malloc(sizeof(struct flight));
    new_flight->origin_airport = NULL; new_flight->dest_airport = NULL;   
    // Read number of stops using fgets
    printf("How many stops will be enroute? ");
    char input_line[MAX_STRING_LEN] = {0};
    fgets(input_line, MAX_STRING_LEN, stdin);
    // Convert the string to a number
    int num_stops = atoi(input_line);   
    char buffer[MAX_STRING_LEN];
    int arrival_time = 0; int departure_time = 0; int prev_departure = FALSE;
    char airport_code[MAX_STRING_LEN]; int check_head = FALSE;   
    struct airport *current_airport;           
    for (int i = 0; i < num_stops; i++) {
        int check_error = FALSE;
        // Getting all the entire line and store in buffer
        fgets(buffer, MAX_STRING_LEN, stdin);
        // Extract information from the input
        interpret_line(buffer, &arrival_time, &departure_time, airport_code);
        // Checking if the arrival and departure time are in a fine order       
        if (arrival_time > departure_time) {
            printf("Departure time cannot be before the arrival time!\n");
            check_error = TRUE;
        } else if (prev_departure != FALSE && prev_departure > arrival_time) {
            printf("New arrival time cannot be before ");
            printf("the previous departure time\n");
            check_error = TRUE;
        }       
        // Check for error and if the head is NULL
        if (check_head == FALSE && check_error == FALSE) {
            current_airport = 
            create_airport(airport_code, arrival_time, departure_time);
            new_flight->origin_airport = current_airport;
            new_flight->dest_airport = current_airport;
            prev_departure = current_airport->departure_time;
            check_head = TRUE;
        } else if (check_error == FALSE) {
            current_airport = 
            create_airport(airport_code, arrival_time, departure_time);
            prev_departure = current_airport->departure_time;
            struct airport *prev_airport = new_flight->origin_airport;
            while (prev_airport->next_airport != NULL) {
                prev_airport = prev_airport->next_airport;
            }
            prev_airport->next_airport = current_airport;
            new_flight->dest_airport = current_airport;                
        }
    }    
    return new_flight;
}


// Stage 1.2
// Given a pointer to a flight struct, prints all the info about the route
// Parameters:
//     flight = the flight which contains the flight route to print
// Returns:
//     None
void do_print_airports(struct flight *flight) {

    struct airport *current = flight->origin_airport;   
    printf("ROUTE:\n");    
    while (current != NULL) {
        print_one_airport(current);
        current = current->next_airport;
    }   
}

// Stage 1.2
// PROVIDED FUNCTION - DO NOT CHANGE
// Given a pointer to an airport struct,
// prints all the info about the airport
// Parameters:
//     ap = the airport to print
// Returns:
//     None
void print_one_airport(struct airport *ap) {
    printf(
        "%8s:    %04d -> %04d\n",
       ap->code,
       ap->arrival_time,
       ap->departure_time
    );
}

// Stage 1.1
// Given the information about a new airport,
// Uses `malloc` to create memory for it and returns a pointer to
// that memory.
// Parameters:
//     code            = the airport ICAO code
//     arrival_time    = the arrival time of the new airport
//     departure_time  = the departure time of the new airport
// Returns:
//     A pointer to the malloc'd struct airport
struct airport *create_airport(
    char code[MAX_STRING_LEN],
    int arrival_time,
    int departure_time)
{
    // Malloc new struct
    struct airport *new_airport = malloc(sizeof(struct airport));
    // initialise airport fields
    strcpy(new_airport->code, code);
    new_airport->arrival_time = arrival_time;
    new_airport->departure_time = departure_time;
    new_airport->next_airport = NULL;
    new_airport->manifest = NULL;
    return new_airport;
}

// For command subroute, print time differences between origin departure and 
// given flight code's arrival if exists
void do_subroute(struct flight *flight) {   

    char airport_code[MAX_STRING_LEN];
    printf("Enter airport code: ");
    fgets(airport_code, MAX_STRING_LEN, stdin); 
    remove_newline(airport_code);  
    struct airport *current = flight->origin_airport;
    int origin_departure = current->departure_time;
    // Given airport arrival time
    int dest_arrival;
    int check_code = FALSE;
    while (current != NULL) {
        if (strcmp(airport_code, current->code) == 0) {
            dest_arrival = current->arrival_time;
            check_code = TRUE;
        }
        current = current->next_airport;
    }
    // Check if given code exists
    if (check_code == FALSE) {
        printf("Desired subroute destination does not exist!\n");
    } else {
        // Calculate in hours and mins
        int hours = (dest_arrival / 100) - (origin_departure / 100); 
        int mins = (dest_arrival % 100) - (origin_departure % 100);
        int minute_diff = hours * 60 + mins;
        if (minute_diff < 0) {
            minute_diff *= -1;
        }
        hours = minute_diff / 60;
        mins = minute_diff % 60;        
        printf("Time for subroute: %d hrs & %d mins\n", hours, mins);
    }  
    return;
}

// For command change_origin, insert new origin to the head of the linked list
// if no errors in term of arrival and departure time occur
void do_change_origin(struct flight *flight) {

    char buffer[MAX_STRING_LEN];
    int arrival_time = 0;
    int departure_time = 0;
    char airport_code[MAX_STRING_LEN];
    printf("Enter new origin info: ");
    fgets(buffer, MAX_STRING_LEN, stdin);
    interpret_line(buffer, &arrival_time, &departure_time, airport_code);   
    struct airport *current = flight->origin_airport;
    // Checking if the arrival and departure time and also the code are valid
    int check_error = FALSE;
    if (departure_time < arrival_time) {
        printf("Departure time cannot be before the arrival time!\n");
        check_error = TRUE;
    } else if (departure_time > current->arrival_time) {
        printf("Departure of new origin cannot be after the arrival time"); 
        printf(" of the next airport!\n");
        check_error = TRUE;
    } else {
        while (current != NULL) {
            if (strcmp(airport_code, current->code) == 0) {
                printf("New airport code is not unique!\n");
                check_error = TRUE;
                break;
            }
            current = current->next_airport;
        }
    }    
    if (check_error == FALSE) {
        // Insert new_origin to the head of the linked list
        struct airport *new_origin =
        create_airport(airport_code, arrival_time, departure_time);
        new_origin->next_airport = flight->origin_airport;
        flight->origin_airport = new_origin;
        printf("Added: %4s\n", new_origin->code);
    }     
    return;
}

// For command bypass, deleting a flight in linked list according to given 
// flight code if it exists
void do_bypass(struct flight *flight) {

    char airport_code[MAX_STRING_LEN];
    printf("Enter airport code: ");
    fgets(airport_code, MAX_STRING_LEN, stdin); 
    remove_newline(airport_code);    
    struct airport *current = flight->origin_airport;  
    // A variable checking which list we want to delete
    int count_list = 0;
    // Checking if the code exists
    int check_code = FALSE;
    // Checking if there is only 1 flight avaiable or not, if so, returns
    if (current->next_airport == NULL) {
        return;
    }
    while (current != NULL) {
        if (strcmp(airport_code, current->code) == 0) {
            check_code = TRUE;
            break;
        }
        current = current->next_airport;
        count_list++;
    }  
    current = flight->origin_airport;
    struct airport *prev = NULL;
    if (check_code == FALSE) {
        printf("No airport of that code exists!\n");
    } else {
        if (count_list == 0) {
            flight->origin_airport = current->next_airport;
            delete_manifest(current->manifest);
            free(current);
        } else {
            for (int i = 0; i < count_list; i++) {
                prev = current;
                current = current->next_airport;
            }
            prev->next_airport = current->next_airport;
            delete_manifest(current->manifest);
            free(current);
        }
    }
    current = flight->origin_airport;
    while (current->next_airport != NULL) {
        current = current->next_airport;
    }
    flight->dest_airport = current;
         
    return;
}

// For command emergency, find the closet arrival time of a flight to given
// emergency period and insert a new emergency flight and delete all flight
// after the emergency flight
// Also set the emergency flight's departure time as 0
void do_emergency(struct flight *flight) {
    
    printf("How long until emergency: ");
    char hours_char[MAX_STRING_LEN];
    fgets(hours_char, MAX_STRING_LEN, stdin);
    // Changing hours_char to be an integer and multiply with 100 to match 
    // the 24 hours timing (01 : 00) as an hour
    int hours = atoi(hours_char) * CHANGE_TO_HOURS;    
    struct airport *current = flight->origin_airport;
    struct airport *emergency_flight;
    int emergency_arrival_time = current->departure_time + hours;
    if (hours == 0) {
        current->departure_time = EMERGENCY_DEPARTURE_TIME;
        flight->dest_airport = current;
        current = current->next_airport; 
        // Free all airport after current      
        do_free_airport(current);
        current = flight->origin_airport;
        current->next_airport = NULL;
    } else if (emergency_arrival_time > (flight->dest_airport)->arrival_time) {
        printf("Flight was safe!\n");
    } else {
        while (current->next_airport != NULL && (emergency_arrival_time > 
        (current->next_airport)->arrival_time)) {           
            current = current->next_airport;
        }
        emergency_flight = create_airport(EMERGENCY_CODE, 
        emergency_arrival_time, EMERGENCY_DEPARTURE_TIME); 
             
        emergency_flight->next_airport = current->next_airport;
        current->next_airport = emergency_flight;      
        current = current->next_airport->next_airport;
        // Free all airport after current
        do_free_airport(current);  
        emergency_flight->next_airport = NULL; 
        flight->dest_airport = emergency_flight;       
    }
    return;
}

// For command cancel, freeing all of the flight and recieve new flight datas
struct flight *do_cancel(struct flight *flight) {

    do_free_flight(flight);
    printf("Flight cancelled. Now accepting a new flight:\n");
    struct flight *new_flight = setup_flight();   
    return new_flight;
}

// For command reverse, reverse all flight in the list eventhough arrival and 
// departure times are not matching
void do_reverse(struct flight *flight) {
     
    struct airport *current = flight->origin_airport;
    struct airport *prev = NULL;
    struct airport *next = NULL;
    
    while (current != NULL) {
        next = current->next_airport;
        current->next_airport = prev;
        prev = current;
        current = next;
    }   
    current = flight->origin_airport;
    flight->dest_airport = current;
    flight->origin_airport = prev;   
    
    return;
}

// Freeing every malloc being called in flight
void do_free_flight(struct flight *flight) {

    struct airport *current_airport = flight->origin_airport;
    struct airport *next;     
    while (current_airport != NULL) { 
        delete_manifest(current_airport->manifest);      
        next = current_airport->next_airport;
        free(current_airport);
        current_airport = next;
    }
    
    free(flight);
    return;
}

// Freeing every malloc being called in airport after a given head
void do_free_airport(struct airport *head) {

    struct airport *current_airport = head;
    struct airport *next;     
    while (current_airport != NULL) { 
        delete_manifest(current_airport->manifest);      
        next = current_airport->next_airport;
        free(current_airport);
        current_airport = next;
    }
    
    return;
}
// For command add person, receiving passenger name and weight, then keep them
// in a struct person which being pointed by struct manifest that
// stuct airport pointing at, if the given airport code exists
void do_add_person(struct flight *flight) {
       
    struct airport *current = flight->origin_airport;
    int check_code = FALSE;
    char airport_code[MAX_STRING_LEN];
    char passenger_name[MAX_STRING_LEN];
    char weight_char[MAX_STRING_LEN];
    
    printf("Enter the airport code: ");
    fgets(airport_code, MAX_STRING_LEN, stdin);
    remove_newline(airport_code);
    
    printf("Enter the passenger name: ");
    fgets(passenger_name, MAX_STRING_LEN, stdin);
    remove_newline(passenger_name);
    
    printf("Enter the passenger weight: ");
    fgets(weight_char, MAX_STRING_LEN, stdin);
    remove_newline(weight_char);
    double weight = atof(weight_char);
    
    while (current != NULL) {
        if (strcmp(airport_code, current->code) == 0) {
                   
            if (current->manifest == NULL) {  
                struct manifest *new_manifest = create_manifest();        
                add_person(new_manifest, passenger_name, weight);
                current->manifest = new_manifest;
            } else {
                add_person(current->manifest, passenger_name, weight);
            }
                        
            check_code = TRUE;
            break;
        }
        current = current->next_airport;
    }
    if (check_code == FALSE) {
        printf("No airport of that code exists!\n");
    }
    return;
}

// For command print_manifest, printing the name and weight of all passengers
// in a flight of given airport code if the code exists
void do_print_manifest(struct flight *flight) {
    
    struct airport *current = flight->origin_airport;
    char airport_code[MAX_STRING_LEN];
    int check_code = FALSE;
    printf("Enter the airport code: ");
    fgets(airport_code, MAX_STRING_LEN, stdin);
    remove_newline(airport_code);
    
    while (current != NULL) {
        if (strcmp(airport_code, current->code) == 0) {
            check_code = TRUE;
            break;
        }
        current = current->next_airport;
    }
    
    if (check_code == FALSE) {
        printf("No airport of that code exists!\n");
    } else {
        print_manifest(current->manifest);
    }
    
    return;
}

// For command stats, all the manifests will be merged together at 
// the destination airport. Then displays the list of all people at 
// the destination airport and the total weight of everyone
void do_stats(struct flight *flight) {
    
    struct airport *current = flight->origin_airport;
    while (current != NULL) {
        if (current->manifest == NULL) {
            struct manifest *new_manifest = create_manifest();
            current->manifest = new_manifest;
        }
        current = current->next_airport;
    }
    
    current = flight->origin_airport;
    while (current != flight->dest_airport) {
    
        if (current->manifest != NULL) {
            current->next_airport->manifest = 
            join_manifest(current->next_airport->manifest, current->manifest);
            delete_manifest(current->manifest);
            current->manifest = NULL;
        }
        current = current->next_airport;
    }
    
    printf("Final manifest:\n");
    print_manifest(flight->dest_airport->manifest);
    
    double total_weight = manifest_weight(flight->dest_airport->manifest);
    printf("Total Weight: %lf\n", total_weight);
    
    return;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////  HELPER FUNCTIONS  //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will remove and first newline it sees.
// The newline character wil be replaced with a null terminator ('\0')
// Parameters:
//     flight  = the flight to move people along of
// Returns:
//     None
void remove_newline(char input[MAX_STRING_LEN]) {

    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}


// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the following foramt: [integer0] [integer1] [string]
// This function will extract the relevant values into the given pointer variables.
// The function will also remove any newline characters.
//
// For example, if given: "0135 0545 YSSY"
// The function will put the integer values
//     135 into the val1 pointer
//     545 into the val2 pointer
// And will copy a null terminated string
//     "YSSY" into the 'word' array
//
// If you are interested, `strtok` is a function which takes a string,
// and splits it up into before and after a "token" (the second argument)
//
// Parameters:
//     buffer  = A null terminated string in the following format
//               [integer0] [integer1] [string]
//     val0    = A pointer to where [integer0] should be stored
//     val1    = A pointer to where [integer1] should be stored
//     word    = An array for the [string] to be copied into
// Returns:
//     None
void interpret_line(
    char buffer[MAX_STRING_LEN],
    int *val0,
    int *val1,
    char word[MAX_STRING_LEN]
) {

    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as int
    char *val0_str = strtok(buffer, " ");
    if (val0_str != NULL) {
        *val0 = atoi(val0_str);
    } else {
        *val0 = -1;
    }

    // Extract value 2 as int
    char *val1_str = strtok(NULL, " ");
    if (val1_str != NULL) {
        *val1 = atoi(val1_str);
    } else {
        *val1 = -1;
    }

    char *word_str = strtok(NULL, " ");
    if (word_str != NULL) {
        // Extract word
        strcpy(word, word_str);
    }

    if (val0_str == NULL || val1_str == NULL || word_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }

}

void do_print_help(void) {
    printf("+-----------------+-------------------------------------------+\n");
    printf("|Command Name     | How to Use                                |\n");
    printf("+=================+===========================================+\n");
    printf("|PRINT ROUTE      | Enter command: print                      |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|SUBROUTE         | Enter command: subroute                   |\n");
    printf("|                 | Enter airport code: [AIRPORT CODE]        |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|CHANGE ORIGIN    | Enter command: change_origin              |\n");
    printf("|                 | Enter new origin info: [ARRIVAL TIME]...  |\n");
    printf("|                 |     ... [DEPARTURE TIME] [AIRPORT CODE]   |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|BYPASS           | Enter command: bypass                     |\n");
    printf("|                 | Enter airport code: [AIRPORT CODE]        |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|EMERGENCY        | Enter command: emergency                  |\n");
    printf("|                 | How long until emergency: [TIME IN HOURS] |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|CANCEL           | Enter command: cancel                     |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|REVERSE          | Enter command: reverse                    |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|                 | Enter command: add_person                 |\n");
    printf("|ADD PERSON       | Enter the airport code: [AIRPORT CODE]    |\n");
    printf("|                 | Enter the passenger name: [NAME]          |\n");
    printf("|                 | Enter the passenger weight: [WEIGHT]      |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|PRINT MANIFEST   | Enter command: print_manifest             |\n");
    printf("|                 | Enter the airport code: [AIRPORT CODE]    |\n");
    printf("+-----------------+-------------------------------------------+\n");
    printf("|FLIGHT STATISTICS| Enter command: stats                      |\n");
    printf("+-----------------+-------------------------------------------+\n");
}
