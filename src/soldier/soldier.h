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
    void init_soldier(Soldier* soldier, Team team, Position position);

    // init all soldiers
    void init_all_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]);

    // check of soldier has moving possibilities
    int has_Soldier_Moving_Possibilities(Soldier* soldier);

    // les possb li ynjm yt7arakhom
void see_Soldier_Moving_Possibilities(Position soldier_pos,Soldier soldiers[30],Position** active_player_move_positions,int* nb_active_player_move_positions,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10],SDL_Window *window,Soldier* active_soldier);
    
    // Function pointer for moving the soldier
    void move_Soldier(struct Soldier* soldier,Position new_position,Soldier soldiers[30]);


void place_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]);



// new check close possibilities
void see_close_Possibilities(Position soldier_pos,Soldier soldiers[30],Position** active_player_move_positions,int* nb_active_player_move_positions,SDL_Rect board_Matrice_sdlRect[10][10],Soldier* soldier);

    ///test
    int test_move_pos(Position soldier_pos,Soldier soldiers[30],Position* active_player_move_positions,int* nb_active_player_move_positions) ;

    void printTest(Position* active_player_move_positions,int* nb_active_player_move_positions);

#endif // SOLDIER_H