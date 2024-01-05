#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "../soldier/soldier.h"
#include "../board/board.h"


//myfiles utils
#include "../utils/utils.h"


void redraw_game(Soldier soldiers[30], SDL_Rect board_Matrice_sdlRect[10][10], SDL_Renderer *renderer, SDL_Window* window) {

    //step 1 : draw the board
    draw_board(renderer, board_Matrice_sdlRect);
    //step2 : place the soldiers of team A and B with their current positions
    place_soldiers(soldiers,window, renderer, board_Matrice_sdlRect);
    //step3 : draw the game
   SDL_RenderPresent(renderer);
    
}

void draw_possibilities(Position** active_player_move_positions,int* nb_active_player_move_positions,SDL_Rect board_Matrice_sdlRect[10][10],SDL_Renderer *renderer,SDL_Window *window,Soldier* soldier){
    SDL_Surface *image = SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/moves/move1.bmp");
    if (image == NULL) {
        SDL_ExitWithError("Failed to load image");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == NULL) {
        SDL_ExitWithError("Failed to create texture");
    }
    ////////////////////////////////////////////////////////////////////////
    SDL_Surface *image2 = SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/moves/move2.bmp");
    if (image2 == NULL) {
        SDL_ExitWithError("Failed to load image");
    }

    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, image2);
    SDL_FreeSurface(image2);
    if (texture2 == NULL) {
        SDL_ExitWithError("Failed to create texture");
    }


    for (int x = 0; x < *nb_active_player_move_positions; x++)
    {
        int pos_i = (*active_player_move_positions+x)->i;
        int pos_j = (*active_player_move_positions+x)->j;
       if (soldier->team.name == 'A')
    {
        // printf("soldier team: %c\n",soldier->team.name);
        if (SDL_RenderCopy(renderer, texture, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                                    SDL_DestroyRenderer(renderer);
                                    SDL_ExitWithError("Failed to render texture");
                                }
    }
    else if (soldier->team.name == 'B')
    {
        printf("soldier team: %c\n",soldier->team.name);
        if (SDL_RenderCopy(renderer, texture2, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                                    SDL_DestroyRenderer(renderer);
                                    SDL_ExitWithError("Failed to render texture");
                                }
    }
}   

// Update the screen
SDL_RenderPresent(renderer);

}
