#ifndef UTILS_H
#define UTILS_H


#define TEAM_A_COLOR "RED"
#define TEAM_B_COLOR "GREEN"
#define TEAM_C_COLOR "PURPLE"
#define TEAM_D_COLOR "GREY"

#include <SDL.h>

 

typedef struct Position{
    int i;
    int j;
} Position;

typedef struct Team{
    char name; // 'A' or 'B' or 'C' or 'D'
    char* color ; // color of the team 'GREEN' or 'RED' or 'PURPLE' or 'GREY'
    Position* TeamCamp; // positions of the team camp
} Team;





//exit with error SDL fct
void SDL_ExitWithError(const char* message);


#endif // UTILS_H