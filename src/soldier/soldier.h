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
    void init_all_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10],Team* team_A,Team* team_B);

    // check of soldier has moving possibilities
    int has_Soldier_Moving_Possibilities(Soldier* soldier,Soldier soldiers[30]);

    
    // Function pointer for moving the soldier
    void move_Soldier(struct Soldier* soldier,Position new_position,Soldier soldiers[30],Team* team_A,Team* team_B,SDL_Renderer *renderer,SDL_Window *window,int* game_on);


    void place_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]);

    int check_team_took_other_team_positions(Soldier soldiers[30],Team* team_A,Team* team_B,Team active_team);

    // new check close possibilities
    void see_close_Possibilities(Position soldier_pos,Soldier soldiers[30],Position** active_player_move_positions,int* nb_active_player_move_positions,SDL_Rect board_Matrice_sdlRect[10][10],Soldier* soldier);

    void check_jump_positions(Soldier soldiers[30], Position pos, int directions[8][2], int num_directions, Position** active_player_move_positions, int* nb_active_player_move_positions);

    // check if the soldier can jump in a direction
    void find_all_jump_positions(Soldier soldiers[30], Position pos, Position** active_player_move_positions, int* nb_active_player_move_positions);

#endif // SOLDIER_H