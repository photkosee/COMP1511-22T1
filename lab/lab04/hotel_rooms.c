// A program receiving details of hotel rooms and print them out
// hotel_rooms.c
// by Phot Koseekrainiramon (5387411)
// 11/03/2022
// COMP1511 Lab 4 Exercise 3

#include <stdio.h>

#define MAX_ROOMS 50

struct hotel_room {
    // TODO: fill this in with the details of each hotel room
    int name;
    double cost;
};

// Prints the room in the correct format when given the room_number
// and price of it.
void print_room(int room_number, double price);

int main(void) {
    
    struct hotel_room hotel_room[MAX_ROOMS];
    int num;
    int i = 0;
    int j = 0;
    
    printf("How many rooms? ");
    // TODO: scan in how many rooms in the hotel
    scanf("%d", &num);
    
    printf("Enter hotel rooms:\n");
    
    while (i < num) {
        // TODO: scan in the details of each hotel room
        scanf("%d", &hotel_room[i].name);
        scanf("%lf", &hotel_room[i].cost);
        i++;
    }
    
    printf("Room List:\n");
    // TODO: print all the rooms scanned in
    
    while (j < num) {
        print_room(hotel_room[j].name, hotel_room[j].cost);
        j++;
    }
    
    return 0;
}

// Prints the room in the correct format when given the room_number
// and price of it.
//
// Takes in:
// - `room_number` -- The hotel room's room number.
// - `price` -- How much the hotel room costs.
//
// Returns: nothing.
void print_room(int room_number, double price) {

    printf("Room %d @ $%.2lf\n", room_number, price);

    return;
}
