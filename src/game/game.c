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



void draw_end_game(SDL_Renderer *renderer,SDL_Window *window,Team winning_team){

    SDL_Surface *image=NULL;
    SDL_Texture *texture= NULL;

    image =SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/end/background_end.bmp");
    if(image==NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("background not loading");
    }
    //sn3na texture f SDL
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if(texture==NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("texture not being created");
    }

    //taw bch nchargiwha fel memoire texture hedhi
    SDL_Rect rectangle3;
    
    if(SDL_QueryTexture(texture,NULL,NULL,&rectangle3.w,&rectangle3.h)!=0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("chargement texture");
    }

    //ncenter fil image 
    rectangle3.x = (650 - rectangle3.w) / 2;
    rectangle3.y = (650| - rectangle3.h) / 2;

    //nwari taswira background
   
    if( SDL_RenderCopy(renderer,texture,NULL,&rectangle3)!=0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("impossible d'afficher texture");
    }

    SDL_Surface *image2=NULL;
    SDL_Texture *texture2= NULL;

    image2 =SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/end/player_1_won.bmp");
    if(image2==NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("background not loading");
    }
    //sn3na texture f SDL
    texture2 = SDL_CreateTextureFromSurface(renderer, image2);
    SDL_FreeSurface(image2);
    if(texture2==NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("texture not being created");
    }

    ////b won 
    SDL_Surface *image3=NULL;
    SDL_Texture *texture3= NULL;

    image3 =SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/end/player_2_won.bmp");
    if(image3==NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("background not loading");
    }
    //sn3na texture f SDL
    texture3 = SDL_CreateTextureFromSurface(renderer, image3);
    SDL_FreeSurface(image3);
    if(texture3==NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("texture not being created");
    }

    if (winning_team.name == 'A')
    {
        if( SDL_RenderCopy(renderer,texture2,NULL,&rectangle3)!=0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("impossible d'afficher texture");
    }
    }
    else
    {
        if( SDL_RenderCopy(renderer,texture3,NULL,&rectangle3)!=0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("impossible d'afficher texture");
    }
    }
    

    // Update the screen
SDL_RenderPresent(renderer);
}
