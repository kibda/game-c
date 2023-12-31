#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>

typedef struct Position{
    int i;
    int j;
} Position;

typedef struct Team{
    char name; // 'A' or 'B' or 'C' or 'D'
    Position* TeamCamp; // positions of the team camp
} Team;

void SDL_ExitWithError(const char* message);

#endif // UTILS_H