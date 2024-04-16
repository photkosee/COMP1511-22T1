// CS Explorer
// cs_explorer.c
//
// This program was written by Phot Koseekrainiramon (z5387411)
// on 22/03/2022 - 28/03/2022
//
// Version 1.0.0 (2022-03-08): Assignment Released.
//
// TODO: Description of your program.
// An advanture game with given healing potion, monster and boulder. 
// Try beating all the monsters to win the game. But careful of your health!

#include <stdio.h>

// Additional libraries here


// Provided constants 
#define SIZE 8
#define PLAYER_STARTING_ROW (SIZE - 1)
#define PLAYER_STARTING_COL 0
#define EMPTY_POINTS 0
#define EMPTY_TYPE 'E'
#define PLAYER_TYPE 'P'
#define MONSTER_TYPE 'M'
#define HEALING_TYPE 'H'
#define BOULDER_TYPE 'B'

// Your constants here
#define ZERO 0
#define HORIZON 1
#define VERTICAL 2

// Provided struct
struct location {
    char occupier;
    int points;
};

// Your structs here

// Provided functions use for game setup
// You do not need to use these functions yourself.
void init_map(struct location map[SIZE][SIZE]);
void place_player_on_starting_location(struct location map[SIZE][SIZE]);

// You will need to use these functions for stage 1.
void print_cheat_map(struct location map[SIZE][SIZE]);
void print_game_play_map(struct location map[SIZE][SIZE]);

// Your functions prototypes here (comments are on top of each state function)
void player_stuck(int ROW, int COL, int *health, 
    struct location map[SIZE][SIZE]);
void state_pieces(struct location map[SIZE][SIZE], int row, int col, 
    int point);
void monster_attack(int i, int j, int *health, int row_current, 
    int col_current, struct location map[SIZE][SIZE], int pre_move);
int risk(int start_row, int end_row, int start_col, int end_col,
        int sum_monster, int sum_potion, int num_boulder, 
        int num_area, struct location map[SIZE][SIZE]);
void print_result(char type, int square_points);
void calculate_square_points(char type, int *square_points, int row, int col, 
        int sum_row, int sum_col, struct location map[SIZE][SIZE]);
void check_monsters_location(int row_mons[(SIZE*SIZE) - 1], 
     int col_mons[(SIZE*SIZE) - 1], struct location map[SIZE][SIZE]);
void move_player(char direction, int *row_current, int *col_current, 
                int *health, struct location map[SIZE][SIZE], int *pre_move);
void count_monster(int *num_monster, struct location map[SIZE][SIZE]);
void compare_danger_12(float danger1, float danger2);
void compare_danger_13(float danger1, float danger3);
void compare_danger_23(float danger2, float danger3);
void compare_danger_24(float danger2, float danger4); 
void compare_danger_34(float danger3, float danger4);
void compare_danger_all(float danger1, float danger2, float danger3, 
                        float danger4);
void monster_hit(int i, int j, struct location map[SIZE][SIZE]);
    
int main(void) {

    struct location map[SIZE][SIZE];
    init_map(map);

    printf("Welcome Explorer!!\n");
    printf("How many game pieces are on the map?\n");
    
    // TODO: Add code to scan in the number of game pieces here.
    
    int num_pieces;
    scanf("%d", &num_pieces);
    
    // TODO: Add code to scan in the details of each game piece and place them
    //       on the map
    
    int count = 0;
    int row = -9;
    int col = -9;
    int point;
    int num_monster = 1;
    int row_current = PLAYER_STARTING_ROW;
    int col_current = PLAYER_STARTING_COL;
    int health = 10;
    int pre_move = VERTICAL;
    
    printf("Enter the details of game pieces:\n");
    while (count < num_pieces) {
        scanf("%d %d %d", &point, &row, &col);
        state_pieces(map, row, col, point);
        count++;
    }

    // After the game pieces have been added to the map print out the map.
    place_player_on_starting_location(map);
    print_game_play_map(map);
    printf("\nEXPLORE!\n");
    printf("Enter command: ");

    // TODO: keep scanning in commands from the user until the user presses
    // ctrl + d
    
    char commands = 'z';
    char direction;
    int i;
    int j;
    char type;
    // take command until got a 'q' or EOF
    while (health > 0 && commands != 'q' && num_monster > 0 &&
          (scanf("%d %d %d", &point, &row, &col) != EOF ||
           scanf(" %c", &commands) != EOF) && scanf(" %c", &commands) != 'q') {
        // check if the player is stuck or got hit by a falling boulder    
        player_stuck(row_current, col_current, &health, map);
        if (commands == 'a') {
            int row_mons[(SIZE*SIZE) - 1] = {0};
            int col_mons[(SIZE*SIZE) - 1] = {0};      
            // check monsters' locations      
            check_monsters_location(row_mons, col_mons, map);    
            int x = 0;
            while (x <= count) {
                i = row_mons[x];
                j = col_mons[x];
                // moves all monsters closer to the player
                monster_attack(i, j, &health, row_current, 
                col_current, map, pre_move);
                x++;
            }
        }
        if (commands == 'n') {           
            int size = 0;
            scanf("%d", &size);
            i = 0;
            j = 0;           
            float sum_monster1 = 0;
            float sum_monster2 = 0;
            float sum_monster3 = 0;
            float sum_monster4 = 0;
            float sum_potion1 = 0;
            float sum_potion2 = 0;
            float sum_potion3 = 0;
            float sum_potion4 = 0;
            float num_area1 = 0;
            float num_area2 = 0;
            float num_area3 = 0;
            float num_area4 = 0;
            float num_boulder1 = 0;
            float num_boulder2 = 0;
            float num_boulder3 = 0;
            float num_boulder4 = 0;    
            float danger1;
            float danger2;
            float danger3;
            float danger4;  
            int end_row1 = row_current - 1;
            int end_col1 = col_current - 1;
            int start_row1 = row_current - size;
            int start_col1 = col_current - size;           
            if (start_row1 < ZERO) {
                start_row1 = ZERO;
            } 
            if (start_col1 < ZERO) {
                start_col1 = ZERO;
            }
            if (end_row1 < ZERO) {
                end_row1 = ZERO;
            } 
            if (end_col1 < ZERO) {
                end_col1 = ZERO;
            }                       
            int end_row2 = row_current - 1;
            int end_col2 = col_current + size;
            int start_row2 = row_current - size;
            int start_col2 = col_current + 1;           
            if (start_row2 < ZERO) {
                start_row2 = ZERO;
            } 
            if (end_col2 > SIZE - 1) {
                end_col2 = SIZE - 1;
            }
            if (end_row2 < ZERO) {
                end_row2 = ZERO;
            } 
            if (start_col2 > SIZE - 1) {
                start_col2 = SIZE - 1;
            }           
            int end_row3 = row_current + size;
            int end_col3 = col_current - 1;
            int start_row3 = row_current + 1;
            int start_col3 = col_current - size;           
            if (start_row3 > SIZE - 1) {
                start_row3 = SIZE - 1;
            } 
            if (start_col3 < ZERO) {
                start_col3 = ZERO;
            }
            if (end_row3 > SIZE - 1) {
                end_row3 = SIZE - 1;
            } 
            if (end_col3 < ZERO) {
                end_col3 = ZERO;
            }         
            int end_row4 = row_current + size;
            int end_col4 = col_current + size;
            int start_row4 = row_current + 1;
            int start_col4 = col_current + 1;
            
            if (start_row4 > SIZE - 1) {
                start_row4 = SIZE - 1;
            } 
            if (start_col4 > SIZE - 1) {
                start_col4 = SIZE - 1;
            }
            if (end_row4 > SIZE - 1) {
                end_row4 = SIZE - 1;
            } 
            if (end_col4 > SIZE - 1) {
                end_col4 = SIZE - 1;
            }
            // all the functions are to calculate risks
            if (row_current == ZERO && col_current == ZERO) {
                printf("The recommended move is: Right Down\n");
            } else if (row_current == ZERO && col_current == SIZE - 1) {
                printf("The recommended move is: Left Down\n");
            } else if (row_current == SIZE - 1 && col_current == ZERO) {
                printf("The recommended move is: Right Up\n");
            } else if (row_current == SIZE - 1 && col_current == SIZE - 1) {
                printf("The recommended move is: Left Up\n");
            } else if (row_current == ZERO) {           
                danger3 = risk(start_row3, end_row3, start_col3, end_col3,
                    sum_monster3, sum_potion3, num_boulder3, num_area3, map);
                danger4 = risk(start_row4, end_row4, start_col4, end_col4,
                    sum_monster4, sum_potion4, num_boulder4, num_area4, map);
                compare_danger_34(danger3, danger4);
            } else if (row_current == SIZE - 1) {
                danger1 = risk(start_row1, end_row1, start_col1, end_col1,
                    sum_monster1, sum_potion1, num_boulder1, num_area1, map);
                danger2 = risk(start_row2, end_row2, start_col2, end_col2,
                    sum_monster2, sum_potion2, num_boulder2, num_area2, map);              
                compare_danger_12(danger1, danger2);
            } else if (col_current == ZERO) {
                danger4 = risk(start_row4, end_row4, start_col4, end_col4,
                    sum_monster4, sum_potion4, num_boulder4, num_area4, map);
                danger2 = risk(start_row2, end_row2, start_col2, end_col2,
                    sum_monster2, sum_potion2, num_boulder2, num_area2, map);
                compare_danger_24(danger2, danger4); 
            } else if (col_current == SIZE - 1) {
                danger3 = risk(start_row3, end_row3, start_col3, end_col3,
                    sum_monster3, sum_potion3, num_boulder3, num_area3, map);
                danger1 = risk(start_row1, end_row1, start_col1, end_col1,
                    sum_monster1, sum_potion1, num_boulder1, num_area1, map);
                compare_danger_13(danger1, danger3);
            } else {
                danger3 = risk(start_row3, end_row3, start_col3, end_col3,
                    sum_monster3, sum_potion3, num_boulder3, num_area3, map);
                danger1 = risk(start_row1, end_row1, start_col1, end_col1,
                    sum_monster1, sum_potion1, num_boulder1, num_area1, map);
                danger4 = risk(start_row4, end_row4, start_col4, end_col4,
                    sum_monster4, sum_potion4, num_boulder4, num_area4, map);
                danger2 = risk(start_row2, end_row2, start_col2, end_col2,
                    sum_monster2, sum_potion2, num_boulder2, num_area2, map);
                compare_danger_all(danger1, danger2, danger3, danger4);
            }
        }
        if (commands == 'c') {
            print_cheat_map(map);
        }       
        row = -1;
        col = -1;
        // check if the player is stuck or got hit by a falling boulder 
        player_stuck(row_current, col_current, &health, map);
        
        if (commands == 'm') {
            scanf(" %c", &direction);
            move_player(direction, &row_current, &col_current, 
                &health, map, &pre_move);
        }
        // check if the player is stuck or got hit by a falling boulder 
        player_stuck(row_current, col_current, &health, map);       
        if (commands == 'h') {
            printf("Your player is at (%d, %d) with a health of %d.\n", 
                    row_current, col_current, health);
        }       
        if (commands == 'r') {
            int start_row;
            int start_col;
            int end_row;
            int end_col;
            int square_points = 0;
            scanf("%d %d %d %d %c", &start_row, &start_col, &end_row, 
            &end_col, &type);
            if (start_row < ZERO) {
                start_row = ZERO;
            }
            if (start_row > SIZE - 1) {
                start_row = SIZE - 1;
            }
            if (start_col < ZERO) {
                start_col = ZERO;
            }
            if (start_col > SIZE - 1) {
                start_col = SIZE - 1;
            }
            if (end_row < ZERO) {
                end_row = ZERO;
            }
            if (end_row > SIZE - 1) {
                end_row = SIZE - 1;
            }
            if (end_col < ZERO) {
                end_col = ZERO;
            }
            if (end_col > SIZE - 1) {
                end_col = SIZE - 1;
            }
            if (end_row < start_row) {
                count = start_row;
                start_row = end_row;
                end_row = count;
            }
            if (end_col < start_col) {
                count = start_col;
                start_col = end_col;
                end_col = count;
            }
            calculate_square_points(type, &square_points, start_row, 
                                    start_col, end_row, end_col, map);           
            print_result(type, square_points);
        }
        if (commands == 's') {
            int size;           
            scanf("%d %d %d %c", &row, &col, &size, &type);
            int sum_row;
            int sum_col;
            sum_row = row + size - 1;
            sum_col = col + size - 1;
            int square_points = 0;
            if (row < ZERO) {
                row = ZERO;
                sum_row = row + size - 1;
            }
            if (sum_row > SIZE - 1) {
                sum_row = SIZE - 1;
            }
            if (col < ZERO) {
                col = ZERO;
                sum_col = col + size - 1;
            }
            if (sum_col > SIZE - 1) {
                sum_col = SIZE - 1;
            }
            calculate_square_points(type, &square_points, row, col, sum_row,
                                    sum_col, map);
            print_result(type, square_points);           
        }
        row = -1;
        col = -1;
        num_monster = 0;
        // count number of monsters
        count_monster(&num_monster, map);
        // check if the player is stuck or got hit by a falling boulder 
        player_stuck(row_current, col_current, &health, map);
        
        if (commands == 'b') {
            scanf("%d %d", &row, &col);
            if (row < ZERO) {
                row = ZERO;
            }
            if (row > SIZE - 1) {
                row = SIZE - 1;
            }
            if (col < ZERO) {
                col = ZERO;
            }
            if (col > SIZE - 1) {
                col = SIZE - 1;
            }
            if (row == row_current && col == col_current) {
                health = 0;
            } else {
                map[row][col].occupier = BOULDER_TYPE;
                map[row][col].points = EMPTY_POINTS;
            }
            col = -1;
            row = -1;
            // check if the player is stuck or got hit by a falling boulder 
            player_stuck(row_current, col_current, &health, map);
        }        
        
        if (health <= 0) {
            print_game_play_map(map);
            commands = 'q';
        }
        
        if (commands != 'q' && num_monster > 0 && health > 0) {
            print_game_play_map(map);
            printf("Enter command: ");
        } 
    } 
    
    if (health <= 0) {
        printf("GAME LOST!\n");
    } else if (commands == 'q') {
        printf("Exiting Program!\n");
    } else if (num_monster == 0) {
        print_game_play_map(map);
        printf("GAME WON!\n");
    }
    
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: you may need to add additional functions here

// count number of monsters
void count_monster(int *num_monster, struct location map[SIZE][SIZE]) {
    int i = 0;
    int j = 0;
    while (i <= SIZE - 1) {
        while (j <= SIZE - 1) {
            if (map[i][j].points < 0) {
                *num_monster = 1;
            }
            j++;   
        }
        i++;
        j = 0;
    }
}

// move player to the given direction if possible
void move_player(char direction, int *row_current, int *col_current, 
                int *health, struct location map[SIZE][SIZE], 
                int *pre_move) {
    if (direction == 'u' && *row_current > ZERO) {
        if (map[*row_current - 1][*col_current].occupier != 
            BOULDER_TYPE) { 
            map[*row_current][*col_current].occupier = EMPTY_TYPE;
            *row_current -= 1;
            *health += map[*row_current][*col_current].points;
            map[*row_current][*col_current].points = EMPTY_POINTS;
            map[*row_current][*col_current].occupier = PLAYER_TYPE;
        }
        *pre_move = VERTICAL;
    } else if (direction == 'd' && *row_current < SIZE - 1) {
        if (map[*row_current + 1][*col_current].occupier != 
            BOULDER_TYPE) {
            map[*row_current][*col_current].occupier = EMPTY_TYPE;
            *row_current += 1;
            *health += map[*row_current][*col_current].points;
            map[*row_current][*col_current].points = EMPTY_POINTS;
            map[*row_current][*col_current].occupier = PLAYER_TYPE;                    
        }
        *pre_move = VERTICAL;
    } else if (direction == 'l' && *col_current > ZERO) {
        if (map[*row_current][*col_current - 1].occupier != 
        BOULDER_TYPE) {
            map[*row_current][*col_current].occupier = EMPTY_TYPE;
            *col_current -= 1;
            *health += map[*row_current][*col_current].points;
            map[*row_current][*col_current].points = EMPTY_POINTS;
            map[*row_current][*col_current].occupier = PLAYER_TYPE;
        }
        *pre_move = HORIZON;
    } else if (direction == 'r' && *col_current < SIZE - 1) {
        if (map[*row_current][*col_current + 1].occupier != 
        BOULDER_TYPE) {
            map[*row_current][*col_current].occupier = EMPTY_TYPE;
            *col_current += 1;
            *health += map[*row_current][*col_current].points;
            map[*row_current][*col_current].points = EMPTY_POINTS;
            map[*row_current][*col_current].occupier = PLAYER_TYPE;                   
        }
        *pre_move = HORIZON;
    } 
}

// comparing risks of dager 3 and 4
void compare_danger_34(float danger3, float danger4) {
    if (danger3 < danger4) {
        printf("The recommended move is: Left Down\n");
    } else {
        printf("The recommended move is: Right Down\n");
    }
}
// comparing risks of dager 1 and 2
void compare_danger_12(float danger1, float danger2) {
    if (danger1 < danger2) {
        printf("The recommended move is: Left Up\n");
    } else {
        printf("The recommended move is: Right Up\n");
    }
}
// comparing risks of dager 2 and 4
void compare_danger_24(float danger2, float danger4) {
    if (danger4 < danger2) {
        printf("The recommended move is: Right Down\n");
    } else {
        printf("The recommended move is: Right Up\n");
    }
}
// comparing risks of dager 1 and 3
void compare_danger_13(float danger1, float danger3) {
    if (danger1 < danger3) {
        printf("The recommended move is: Left Up\n");
    } else {
        printf("The recommended move is: Left Down\n");
    }
}
// comparing risks of all dangers
void compare_danger_all(float danger1, float danger2, float danger3,
                         float danger4) {
    if (danger1 <= danger3 && danger1 <= danger2 && danger1 <= danger4) {
        printf("The recommended move is: Left Up\n");
    } else if (danger2 <= danger3 && danger2 <= danger4) {
        printf("The recommended move is: Right Up\n");
    } else if (danger3 <= danger4) {
        printf("The recommended move is: Left Down\n");
    } else {
        printf("The recommended move is: Right Down\n");
    }
}

// a functions calculates square_points
void calculate_square_points(char type, int *square_points, int row, int col, 
        int sum_row, int sum_col, struct location map[SIZE][SIZE]) {
    int i = row;
    int j = col;
    while (i <= sum_row) {
        while (j <= sum_col) {
            if (type == 'M' && map[i][j].points < 0) {
                *square_points += map[i][j].points;
            } else if (type == 'H' && map[i][j].points > 0) {
                *square_points += map[i][j].points;
            }
            j++;   
        }
        i++;
        j = col;
    }
}


// calculate risks in given areas
int risk(int start_row, int end_row, int start_col, int end_col,
        int sum_monster, int sum_potion, int num_boulder, 
        int num_area, struct location map[SIZE][SIZE]) {
    int count = start_col;
    float danger;
    while (start_row <= end_row) {
        while (start_col <= end_col) {
            if (map[start_row][start_col].occupier == MONSTER_TYPE) {
                sum_monster += map[start_row][start_col].points;
            } else if (map[start_row][start_col].occupier == HEALING_TYPE) {
                sum_potion += map[start_row][start_col].points;
            } else if (map[start_row][start_col].occupier == BOULDER_TYPE) {
                num_boulder += map[start_row][start_col].points;
            }
            num_area++;
            start_col++;   
        }   
        start_row++;
        start_col = count;
    }
    danger = (sum_potion + sum_monster) / (num_boulder - num_area);
    return danger;
}               

// change the place where the monster hit into an according type
void monster_hit(int i, int j, struct location map[SIZE][SIZE]) {
    if (map[i][j].points < ZERO) {
        map[i][j].occupier = MONSTER_TYPE;
    } else if (map[i][j].points == ZERO) {
        map[i][j].occupier = BOULDER_TYPE;
    } else {
        map[i][j].occupier = HEALING_TYPE;
    }
}

// moves all monsters closer to the player
void monster_attack(int i, int j, int *health, int row_current, 
                    int col_current, struct location map[SIZE][SIZE],
                    int pre_move) {
                    
    int row_dif;
    int col_dif;
    int row_dif_neg = row_current - i;
    int col_dif_neg = col_current - j;
    if (map[i][j].occupier == MONSTER_TYPE) {
        row_dif = i - row_current;
        col_dif = j - col_current;
        if ((row_dif >= ZERO && col_dif >= ZERO && row_dif > col_dif) || 
        (col_dif <= ZERO && row_dif >= ZERO && row_dif > col_dif_neg)) {
            if (i > ZERO && map[i - 1][j].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == MONSTER_TYPE) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == HEALING_TYPE) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit((i - 1), j, map);
            } else if (i > ZERO && map[i - 1][j].occupier == EMPTY_TYPE) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i - 1][j].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == BOULDER_TYPE &&
             (j > ZERO && map[i][j - 1].occupier != BOULDER_TYPE)) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i][j - 1].occupier = MONSTER_TYPE;
            }              
        } else if ((row_dif >= ZERO && col_dif >= ZERO && row_dif < col_dif) ||
         (col_dif >= ZERO && row_dif <= ZERO && row_dif_neg < col_dif)) {
            if (j > ZERO && map[i][j - 1].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (j > ZERO && map[i][j - 1].occupier == MONSTER_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (j > ZERO && map[i][j - 1].occupier == HEALING_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit(i, (j - 1), map);
            } else if (j > ZERO && map[i][j - 1].occupier == EMPTY_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j - 1].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (j > ZERO && map[i][j - 1].occupier == BOULDER_TYPE &&
             (i > ZERO && map[i - 1][j].occupier != BOULDER_TYPE)) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i - 1][j].occupier = MONSTER_TYPE;
            }
        } else if (row_dif <= ZERO && col_dif >= ZERO && 
        row_dif_neg == col_dif) {
            if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == MONSTER_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == HEALING_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit(i, (j - 1), map);
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == EMPTY_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j - 1].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == BOULDER_TYPE &&
             (i < 7 && map[i - 1][j].occupier != BOULDER_TYPE)) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i + 1][j].occupier = MONSTER_TYPE;
            } else if (i < 7 && map[i + 1][j].occupier == PLAYER_TYPE) {
                health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == MONSTER_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == HEALING_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit((i + 1), j, map);
            } else if (i < 7 && map[i + 1][j].occupier == EMPTY_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i + 1][j].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == BOULDER_TYPE &&
             (j > ZERO && map[i][j - 1].occupier != BOULDER_TYPE)) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i][j - 1].occupier = MONSTER_TYPE;
            } 
        } else if ((row_dif <= ZERO && col_dif <= ZERO && 
        row_dif_neg > col_dif_neg) || (col_dif >= ZERO && row_dif <= ZERO && 
        row_dif_neg > col_dif)) {
            if (i < 7 && map[i + 1][j].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == MONSTER_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == HEALING_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit((i + 1), j, map);
            } else if (i < 7 && map[i + 1][j].occupier == EMPTY_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i + 1][j].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (map[i + 1][j].occupier == BOULDER_TYPE &&
             (j < 7 && map[i][j + 1].occupier != BOULDER_TYPE)) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i][j + 1].occupier = MONSTER_TYPE;
            }
        } else if ((row_dif <= ZERO && col_dif <= ZERO && 
        row_dif_neg < col_dif_neg) || (col_dif <= ZERO && 
        row_dif >= ZERO && row_dif_neg < col_dif)) {
            if (j < 7 && map[i][j + 1].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (j < 7 && map[i][j + 1].occupier == MONSTER_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (j < 7 && map[i][j + 1].occupier == HEALING_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit(i, (j + 1), map);
            } else if (j < 7 && map[i][j + 1].occupier == EMPTY_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j + 1].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (j < 7 && map[i][j + 1].occupier == BOULDER_TYPE &&
             (i < 7 && map[i + 1][j].occupier != BOULDER_TYPE)) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i + 1][j].occupier = MONSTER_TYPE;
            }
        } else if (row_dif <= ZERO && col_dif <= ZERO && 
        row_dif_neg == col_dif_neg) {
            if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == MONSTER_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == HEALING_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit(i, (j + 1), map);
            } else if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == EMPTY_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j + 1].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == BOULDER_TYPE &&
             (i < 7 && map[i + 1][j].occupier != BOULDER_TYPE)) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i + 1][j].occupier = MONSTER_TYPE;
            } else if (i < 7 && map[i + 1][j].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == MONSTER_TYPE) {
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == HEALING_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit((i + 1), j, map);
            } else if (i < 7 && map[i + 1][j].occupier == EMPTY_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i + 1][j].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i < 7 && map[i + 1][j].occupier == BOULDER_TYPE &&
             (j < 7 && map[i][j + 1].occupier != BOULDER_TYPE)) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i][j + 1].occupier = MONSTER_TYPE;
            } 
        } else if (row_dif >= ZERO && col_dif <= ZERO && 
        row_dif == col_dif_neg) {
            if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == MONSTER_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (j < 7 && map[i][j + 1].occupier == HEALING_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit(i, (j + 1), map);
            } else if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == EMPTY_TYPE) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j + 1].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j < 7 && 
            map[i][j + 1].occupier == BOULDER_TYPE && 
            (i > ZERO && map[i - 1][j].occupier != BOULDER_TYPE)) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i - 1][j].occupier = MONSTER_TYPE;
            } else if (i > ZERO && map[i - 1][j].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == MONSTER_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == HEALING_TYPE) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit((i - 1), j, map);
            } else if (i > ZERO && map[i - 1][j].occupier == EMPTY_TYPE) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i - 1][j].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == BOULDER_TYPE &&
             (j < 7 && map[i][j].occupier != BOULDER_TYPE)) {
                map[i][j + 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i][j + 1].occupier = MONSTER_TYPE;
            } 
        } else if (row_dif >= ZERO && col_dif >= ZERO && row_dif == col_dif) {
            if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == MONSTER_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == HEALING_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit(i, (j - 1), map);
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == EMPTY_TYPE) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j - 1].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (pre_move == HORIZON && j > ZERO && 
            map[i][j - 1].occupier == BOULDER_TYPE && 
            (i > ZERO && map[i - 1][j].occupier != BOULDER_TYPE)) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i - 1][j].occupier = MONSTER_TYPE;
            } else if (i > ZERO && map[i - 1][j].occupier == PLAYER_TYPE) {
                *health += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == MONSTER_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if (i > ZERO && map[i - 1][j].occupier == HEALING_TYPE) {
                map[i + 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS;
                monster_hit((i - 1), j, map);
            } else if (i > ZERO && map[i - 1][j].occupier == EMPTY_TYPE) {
                map[i - 1][j].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i - 1][j].occupier = MONSTER_TYPE;
                map[i][j].points = EMPTY_POINTS;
            } else if ((i > ZERO && map[i - 1][j].occupier == BOULDER_TYPE) && 
                        (j > ZERO && map[i][j - 1].occupier != BOULDER_TYPE)) {
                map[i][j - 1].points += map[i][j].points;
                map[i][j].occupier = EMPTY_TYPE;
                map[i][j].points = EMPTY_POINTS; 
                map[i][j - 1].occupier = MONSTER_TYPE;
            } 
        }
    }
}

// set the position of given pieces
void state_pieces(struct location map[SIZE][SIZE], int row, int col, int point) {
    if ((row < SIZE && row >= 0) && (col < SIZE && col >= 0)) {
        if (point < 0 && point >= -9) {
            map[row][col].occupier = MONSTER_TYPE;
        } else if (point == 0) {
            map[row][col].occupier = BOULDER_TYPE;
        } else if (point <= 9 && point >= 0) {
            map[row][col].occupier = HEALING_TYPE;
        }
        if (row != 7 || col != 0) {
            map[row][col].points = point;
        }
    }
}

// check if the player is stuck or got hit by a falling boulder 
void player_stuck(int ROW, int COL, int *health, struct location map[SIZE][SIZE]) {
    if (ROW > ZERO && ROW < SIZE - 1 && COL > ZERO &&
            COL < SIZE - 1) {
        if (map[ROW + 1][COL].occupier == BOULDER_TYPE &&
            map[ROW - 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL + 1].occupier == BOULDER_TYPE &&
            map[ROW][COL - 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW == ZERO && ROW < SIZE - 1 && COL > ZERO
                   && COL < SIZE - 1) {
        if (map[ROW + 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL + 1].occupier == BOULDER_TYPE &&
            map[ROW][COL - 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW > ZERO && ROW == SIZE - 1 && COL > ZERO
                   && COL < SIZE - 1) {
        if (map[ROW - 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL + 1].occupier == BOULDER_TYPE &&
            map[ROW][COL - 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW > ZERO && ROW < SIZE - 1 && COL == ZERO
                   && COL < SIZE - 1) {
        if (map[ROW + 1][COL].occupier == BOULDER_TYPE &&
            map[ROW - 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL + 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW > ZERO && ROW < SIZE - 1 && COL > ZERO
                   && COL == SIZE - 1) {
        if (map[ROW + 1][COL].occupier == BOULDER_TYPE &&
            map[ROW - 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL - 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW == ZERO && ROW < SIZE - 1 && COL == ZERO
                   && COL < SIZE - 1) {
        if (map[ROW + 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL + 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW == ZERO && ROW < SIZE - 1 && COL > ZERO
                   && COL == SIZE - 1) {
        if (map[ROW + 1][COL].occupier == BOULDER_TYPE &&              
            map[ROW][COL - 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW > ZERO && ROW == SIZE - 1 && COL == ZERO
                   && COL < SIZE - 1) {
        if (map[ROW - 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL + 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    } else if (ROW > ZERO && ROW == SIZE - 1 && COL > ZERO
                   && COL == SIZE - 1) {
        if (map[ROW - 1][COL].occupier == BOULDER_TYPE &&
            map[ROW][COL - 1].occupier == BOULDER_TYPE) {
            *health = -1;
        }
    }
}

// print result
void print_result(char type, int square_points) {
    if (type == 'M') {
        printf("Monsters in this section could apply %d health points.\n"
               , square_points);    
    } else if (type == 'H') {
        printf("Healing Potions in this section could apply %d health points.\n"
               , square_points);   
    }
}

// check all locations of monsters
void check_monsters_location(int row_mons[(SIZE*SIZE) - 1], 
     int col_mons[(SIZE*SIZE) - 1], struct location map[SIZE][SIZE]) {
    int i = 0;
    int j = 0;
    int count = 0;
    while (i < SIZE) {
        while (j < SIZE) {
            if (map[i][j].occupier == MONSTER_TYPE) {
                row_mons[count] = i;
                col_mons[count] = j;
                count++;
            }
            j++;
        }
        i++;
        j = 0;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
/////////////////////////// (DO NOT EDIT BELOW HERE) ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided Function
// Initalises all elements on the map to be empty to prevent access errors.
void init_map(struct location map[SIZE][SIZE]) {
    int row = 0;
    while (row < SIZE) {
        int col = 0;
        while (col < SIZE) {
            struct location curr_loc;
            curr_loc.occupier = EMPTY_TYPE;
            curr_loc.points = EMPTY_POINTS;
            map[row][col] = curr_loc;
            col++;
        }
        row++;
    }

    place_player_on_starting_location(map);
}

// Provided Function
// Places the player in the bottom left most location.
void place_player_on_starting_location(struct location map[SIZE][SIZE]) {
    map[PLAYER_STARTING_ROW][PLAYER_STARTING_COL].occupier = PLAYER_TYPE;
}

// Provided Function
// Prints out map with alphabetic values. Monsters are represented with 'M',
// healing potions in 'H', boulders with 'B' and the player with 'P'.
void print_game_play_map(struct location map[SIZE][SIZE]) {
    printf(" -----------------\n");
    int row = 0;
    while (row < SIZE) {
        printf("| ");
        int col = 0;
        while (col < SIZE) {
            if (map[row][col].occupier == EMPTY_TYPE) {
                printf("- ");
            } else {
                printf("%c ", map[row][col].occupier);
            }
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(" -----------------\n");
}

// Provided Function
// Prints out map with numerical values. Monsters are represented in red,
// healing potions in blue, boulder in green and the player in yellow.
//
// We use some functionality you have not been taught to make sure that
// colours do not appear during testing.
void print_cheat_map(struct location map[SIZE][SIZE]) {

    printf(" -----------------\n");
    int row = 0;
    while (row < SIZE) {
        printf("| ");
        int col = 0;
        while (col < SIZE) {
            if (map[row][col].occupier == PLAYER_TYPE) {
                // print the player in purple
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
                #ifndef NO_COLORS
                printf("\033[1;35m");
                #endif
                // ----------------------------------------
                printf("%c ", PLAYER_TYPE);
            } else if (map[row][col].occupier == HEALING_TYPE) {
                // print healing potion in green
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
                #ifndef NO_COLORS
                printf("\033[1;32m");
                #endif
                // ----------------------------------------
                printf("%d ", map[row][col].points);
            } else if (map[row][col].occupier == MONSTER_TYPE) {
                // print monsters in red
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
                #ifndef NO_COLORS
                printf("\033[1;31m");
                #endif
                // ----------------------------------------
                printf("%d ", -map[row][col].points);
            } else if (map[row][col].occupier == BOULDER_TYPE) {
                // print boulder in blue
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
                #ifndef NO_COLORS
                printf("\033[1;34m");
                #endif
                // ----------------------------------------
                printf("%d ", map[row][col].points);
            } else {
                // print empty squares in the default colour
                printf("- ");
            }
            // ----------------------------------------
            // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
            // reset the colour back to default
            #ifndef NO_COLORS
            printf("\033[0m");
            #endif
            // ----------------------------------------
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(" -----------------\n");
}
