#ifndef SOLDIER_H
#define SOLDIER_H

#include <SDL.h>

//myfiles utils
#include "../utils/utils.h"


typedef struct Soldier {
    
    Team team; // team of the soldier 
    Position position; // position of the soldier on the board
    
} Soldier;

    // init the soldier
    void init_soldier(struct Soldier* soldier, Team team, Position position,SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]);

    // init all soldiers
    void init_all_soldiers(struct Soldier* soldiers,SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]);

    // check of soldier has moving possibilities
    int has_Soldier_Moving_Possibilities(struct Soldier* soldier);

    // les possb li ynjm yt7arakhom
    void see_Soldier_Moving_Possibilities(struct Soldier* soldier);
    
    // Function pointer for moving the soldier
    void move_Soldier(struct Soldier* soldier,Position new_position);


#endif // SOLDIER_H