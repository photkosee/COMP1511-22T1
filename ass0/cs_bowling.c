// CS Bowling
// cs_bowling.c
//
// This program was written by Phot Koseekrainiramon (z5387411)
// on 19/02/2022 - 28/02/2022
//
// A program calculating scores in bowling.

#include <stdio.h>

int main(void){

    // the score of each frame
    int score_frame;
    // the score of bowl 1
    int score1;
    // the score of bowl 2
    int score2;
    int count = 1;
    // the total score of 10 frames
    int score_total = 0;
    // a variable for calculating spare and strike
    int bonus = 0;
    // the score of bonus bowl
    int score_bonus;
    
    printf("Welcome to CS Bowling!\n");
    
    // use while loop with count to run and recieve integers for 10 frames
    while (count < 11) {
        
        printf("Frame %d, Bowl 1: ", count);
        scanf("%d", &score1);
        
        // use else if statement to separate valid and invalid 
        // score from bowl 1 and 2
        if (score1 < 0 || score1 > 10) {
        
            printf("Bowl 1 invalid!\n");
            printf("Frame %d, Bowl 2: ", count);
            scanf("%d", &score2);
            
            // inside if statement of bowl 1 will be a valid and 
            // invalid score for bowl 2
            if (score2 < 0 || score2 > 10) {
                printf("Bowl 2 invalid!\n");
                printf("Score for Frame: 0\n");
                bonus = 0;
                // keep the score in score_total and use bonus 
                // to consider bonus score from spare & strike
            } else if (bonus == 2 && score2 == 10) {
                printf("Score for Frame: %d\n", score2);
                score_total += 2 * score2;
                printf("Spare! Bonus for this frame is next roll.\n");
                bonus = 1;
            } else if (bonus == 2) {
                printf("Score for Frame: %d\n", score2);
                score_total += 2 * score2;
                bonus = 0;
            } else if (score2 == 10) {
                printf("Score for Frame: %d\n", score2);
                score_total += score2;
                printf("Spare! Bonus for this frame is next roll.\n");
                bonus = 1;
            } else {
                printf("Score for Frame: %d\n", score2);
                score_total += score2;
                bonus = 0;
            }              
            
        } else if (score1 < 10) {
        
            printf("Frame %d, Bowl 2: ", count);
            scanf("%d", &score2);
            
            if (bonus == 1) {
                score_total += 2 * score1;
                bonus = 0;
            } else if (bonus == 2) {
                score_total += 2 * score1;
            } else {
                score_total += score1;
            }
            
            score_frame = score1 + score2;

            if (score2 < 0 || score2 > 10 || score_frame > 10) {
                printf("Bowl 2 invalid!\n");
                printf("Score for Frame: %d\n", score1);
                bonus = 0;
            } else if (bonus == 2 && score_frame == 10) {
                printf("Score for Frame: %d\n", score_frame);
                score_total += 2 * score2;
                printf("Spare! Bonus for this frame is next roll.\n");
                bonus = 1;
            } else if (bonus == 2) {
                printf("Score for Frame: %d\n", score_frame);
                score_total += 2 * score2;
                bonus = 0;
            } else if (score_frame == 10) {
                printf("Score for Frame: %d\n", score_frame);
                score_total += score2;
                printf("Spare! Bonus for this frame is next roll.\n");
                bonus = 1;
            } else {
                printf("Score for Frame: %d\n", score_frame);
                score_total += score2;
                bonus = 0;
            } 
            
        } else if (score1 == 10) {
        
            printf("Score for Frame: %d\n", score1);
            printf("Strike! Bonus for this frame is next two rolls.\n");
            
            if (bonus > 0) {
                score_total += 2 * score1;
            } else {
                score_total += score1;
            }
            
            bonus = 2;
            
        } 
        
        count++;
        
    }
    
    // another if statement to consider when we spare or 
    // strike on the last frame to get a bonus bowl
    if (count == 11 && bonus != 0) {
        printf("Bonus Bowl 1: ");
        scanf("%d", &score_bonus);
        // separate valid and invalid score by using 
        // if statement and keep the score for total score
        if (score_bonus < 0 || score_bonus > 10) {
            printf("Bonus Bowl Invalid!\n");
        } else {
            score_total += 2 * score_bonus;
        }
    }
    
    printf("Total Score: %d\n", score_total);
    return 0;
    
}
