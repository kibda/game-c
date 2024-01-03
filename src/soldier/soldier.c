
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "soldier.h"
#include "../game/game.h"

//myfiles utils
#include "../utils/utils.h"

//declare the teams 
Team teamA = {'A', "GREEN", NULL};
Team teamB = {'B', "RED", NULL};
Team teamC = {'C', "PURPLE", NULL};
Team teamD = {'D', "GREY", NULL};



// Initialize the soldier
void init_soldier(Soldier* soldier, Team team, Position position) {
    soldier->team = team;
    soldier->position = position;

}

// Initialize all soldiers
void init_all_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]) {
    //team A 
    SDL_Surface *image = SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/soldiers/soldier2.bmp");
    if (image == NULL) {
        SDL_ExitWithError("Failed to load image");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == NULL) {
        SDL_ExitWithError("Failed to create texture");
    }

    //team b 
    SDL_Surface *image2 = SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/soldiers/soldier1.bmp");
    if (image2 == NULL) {
        SDL_ExitWithError("Failed to load image");
    }

    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, image2);
    SDL_FreeSurface(image2);
    if (texture2 == NULL) {
        SDL_ExitWithError("Failed to create texture");
    }

 

    
    int nb_soldiers = 0;
    // Fill the first line with 5 soldiers and the second line with 4 soldiers
    int counter = 5;
    for (int i = 0; i < 5; i++) {
        int counter2 = counter;
        for (int j = 0; j < 10; j++) {
            if (counter > 0 && counter2 > 0) {
                Position position = {i, j};
                 if (SDL_RenderCopy(renderer, texture, NULL, &board_Matrice_sdlRect[i][j]) != 0) {
                SDL_DestroyRenderer(renderer);
                 SDL_ExitWithError("Failed to render texture");
             }
             init_soldier((soldiers+nb_soldiers),teamB,position);
             // printf("soldier %d :  position : %d %d\n",nb_soldiers,soldiers[nb_soldiers].position.i,soldiers[nb_soldiers].position.j);
             nb_soldiers++;
                counter2--;  
            }
        }
        counter--;
    }

   
    // Fill the remaining lines starting from the last column with 1 soldier and incrementing by 1 until the board ends
        counter = 5;
        for (int i = 9; i >= 5; i--) {
            int counter2 = counter;
            for (int j = 9; j >= 0; j--) {
                if (counter > 0 && counter2 > 0 && j != 1) { // Exclude j = 2
                    Position position = {i, j};
                    if (SDL_RenderCopy(renderer, texture2, NULL, &board_Matrice_sdlRect[i][j]) != 0) {
                        SDL_DestroyRenderer(renderer);
                        SDL_ExitWithError("Failed to render texture");
                    }
                    init_soldier(&soldiers[nb_soldiers],teamA,position);
                    // printf("soldier %d :  position : %d %d\n",nb_soldiers,soldiers[nb_soldiers].position.i,soldiers[nb_soldiers].position.j);
                    nb_soldiers++;
                    counter2--;
                }
            }
            counter--;
        }

    
    


}

// Check if soldier has moving possibilities
int has_Soldier_Moving_Possibilities(Soldier* soldier) {

    return 0;
}

// See soldier moving possibilities
void see_Soldier_Moving_Possibilities(Position soldier_pos,Soldier soldiers[30],Position** active_player_move_positions,int* nb_active_player_move_positions,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10],SDL_Window *window) {
    //nchf lblayes li les9in fiha ferghin wale 
    int i=soldier_pos.i;
    int j=soldier_pos.j;
    Position initPos = {0,0};
    Team initTeam = {'X',"X",NULL};
    Soldier soldier={initTeam,initPos} ;
    for (int ii = 0; ii < 30; ii++)
        {
            
            if (soldiers[ii].position.i == i && soldiers[ii].position.j == j)
            {
                printf("soldier team: %c\n",soldiers[ii].team.name);
                soldier = soldiers[ii];
                break;
                                }}
    if (soldier.team.name != 'X')
    {
        
    
    
    Position Near_Positions[8];
    int near_positions_count = 0;

    if (i - 1 >= 0 && j >= 0 && j <= 9) {
        Near_Positions[near_positions_count].i = i - 1;
        Near_Positions[near_positions_count].j = j;
        near_positions_count++;
    }

    if (i + 1 <= 9 && j >= 0 && j <= 9) {
        Near_Positions[near_positions_count].i = i + 1;
        Near_Positions[near_positions_count].j = j;
        near_positions_count++;
    }

    if (i >= 0 && i <= 9 && j - 1 >= 0) {
        Near_Positions[near_positions_count].i = i;
        Near_Positions[near_positions_count].j = j - 1;
        near_positions_count++;
    }

    if (i >= 0 && i <= 9 && j + 1 <= 9) {
        Near_Positions[near_positions_count].i = i;
        Near_Positions[near_positions_count].j = j + 1;
        near_positions_count++;
    }

    if (i + 1 <= 9 && j + 1 <= 9) {
        Near_Positions[near_positions_count].i = i + 1;
        Near_Positions[near_positions_count].j = j + 1;
        near_positions_count++;
    }

    if (i - 1 >= 0 && j + 1 <= 9) {
        Near_Positions[near_positions_count].i = i - 1;
        Near_Positions[near_positions_count].j = j + 1;
        near_positions_count++;
    }

    if (i + 1 <= 9 && j - 1 >= 0) {
        Near_Positions[near_positions_count].i = i + 1;
        Near_Positions[near_positions_count].j = j - 1;
        near_positions_count++;
    }

    if (i - 1 >= 0 && j - 1 >= 0) {
        Near_Positions[near_positions_count].i = i - 1;
        Near_Positions[near_positions_count].j = j - 1;
        near_positions_count++;
    }
    printf("soldier pos : %d %d\n",i,j);
    for (int x = 0; x < near_positions_count; x++)
    {
         printf("near pos : %d %d\n",Near_Positions[x].i,Near_Positions[x].j);
    }
    // nb_active_player_move_positions = malloc(sizeof(int));
    // if (nb_active_player_move_positions == NULL) {
    //     // Handle memory allocation failure
    //     SDL_ExitWithError("Failed to allocate memory");
    // }
    // *nb_active_player_move_positions = near_positions_count;
    // printf("nb_active_player_move_positions 1 : %d\n", *nb_active_player_move_positions);


*nb_active_player_move_positions = 0;
    *active_player_move_positions = malloc(sizeof(Position));
    if (*active_player_move_positions == NULL) {
        // Handle memory allocation failure
        SDL_ExitWithError("Failed to allocate memory");
    }

    (*active_player_move_positions)->i = 5;
    (*active_player_move_positions)->j = 5;

    printf("i active_player_move_positions 1=%d\n", (*active_player_move_positions)->i);


    for (int y = 0; y < near_positions_count; y++)
    {
        int isOccupied = 0;
        for (int x = 0; x < 30; x++)
        {
            if (soldiers[x].position.i == Near_Positions[y].i && soldiers[x].position.j == Near_Positions[y].j)
            {
                isOccupied = 1;
                break;
            }
        }
        if (!isOccupied)
        {
            (*active_player_move_positions + *nb_active_player_move_positions)->i = Near_Positions[y].i;
            (*active_player_move_positions + *nb_active_player_move_positions)->j = Near_Positions[y].j;
            *nb_active_player_move_positions += 1;
        }
    }
    redraw_game(soldiers,board_Matrice_sdlRect,renderer,window);
    //draw 
       SDL_Surface *image = SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/moves/move1.bmp");
                                if (image == NULL) {
                                    SDL_ExitWithError("Failed to load image");
                                }

                                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
                                SDL_FreeSurface(image);
                                if (texture == NULL) {
                                    SDL_ExitWithError("Failed to create texture");
                                }

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
                                printf("pos_i=%d pos_j=%d \n", pos_i,pos_j);
                               
                            //find the soldier that has the position pos_i,pos_j
                    
                                    if (soldier.team.name == 'A')
                                    {
                                        printf("soldier team: %c\n",soldier.team.name);
                                        if (SDL_RenderCopy(renderer, texture, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                                                                    SDL_DestroyRenderer(renderer);
                                                                    SDL_ExitWithError("Failed to render texture");
                                                                }
                                    }
                                    else if (soldier.team.name == 'B')
                                    {
                                        if (SDL_RenderCopy(renderer, texture2, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                                                                    SDL_DestroyRenderer(renderer);
                                                                    SDL_ExitWithError("Failed to render texture");
                                                                }
                                    }
                                


                                // if (soldiers[i].team.name == 'A')
                                // {
                                //     if (SDL_RenderCopy(renderer, texture, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                                //                                     SDL_DestroyRenderer(renderer);
                                //                                     SDL_ExitWithError("Failed to render texture");
                                //                                 }
                                // }
                                // else if (soldiers[i].team.name == 'B')
                                // {
                                //     if (SDL_RenderCopy(renderer, texture, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                                //                                     SDL_DestroyRenderer(renderer);
                                //                                     SDL_ExitWithError("Failed to render texture");
                                //                                 }
                                // }

                            }
                            // Update the screen
                            SDL_RenderPresent(renderer);
    
  }  }




// Move the soldier
void move_Soldier(Soldier* soldier,Position new_position) {
    soldier->position = new_position;
    //nfaragh el rect eli fl position l9dima w ncopy texture w tswira fil pos jdida

}



void place_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]){
   
        for (int i = 0; i < 30; i++) {
            int pos_i = soldiers[i].position.i;
            int pos_j = soldiers[i].position.j;
            printf("pos_i=%d pos_j=%d \n", pos_i,pos_j);
            SDL_Surface *image = SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/soldiers/soldier1.bmp");
            if (image == NULL) {
                SDL_ExitWithError("Failed to load image");
            }

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
            if (texture == NULL) {
                SDL_ExitWithError("Failed to create texture");
            }

             SDL_Surface *image2 = SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/soldiers/soldier2.bmp");
            if (image2 == NULL) {
                SDL_ExitWithError("Failed to load image");
            }

            SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, image2);
            SDL_FreeSurface(image2);
            if (texture2 == NULL) {
                SDL_ExitWithError("Failed to create texture");
            }
if (soldiers[i].team.name == 'A')
{
   if (SDL_RenderCopy(renderer, texture, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                SDL_DestroyRenderer(renderer);
                SDL_ExitWithError("Failed to render texture");
            }
}
else if (soldiers[i].team.name == 'B')
{
    if (SDL_RenderCopy(renderer, texture2, NULL, &board_Matrice_sdlRect[pos_i][pos_j]) != 0) {
                SDL_DestroyRenderer(renderer);
                SDL_ExitWithError("Failed to render texture");
            }
}

            
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }
    



/////////::: test ::::////////////
// See soldier moving possibilities
int test_move_pos(Position soldier_pos,Soldier soldiers[30],Position* active_player_move_positions,int* nb_active_player_move_positions) {
    //nchf lblayes li les9in fiha ferghin wale 
    int i=soldier_pos.i;
    int j=soldier_pos.j;
    Position Near_Positions[8];
    Near_Positions[0].i=i-1;
    Near_Positions[0].j=j;

    Near_Positions[1].i=i+1;
    Near_Positions[1].j=j;

    Near_Positions[2].i=i;
    Near_Positions[2].j=j-1;

    Near_Positions[3].i=i;
    Near_Positions[3].j=j+1;

    Near_Positions[4].i=i+1;
    Near_Positions[4].j=j+1;

    Near_Positions[5].i=i-1;
    Near_Positions[5].j=j+1;

    Near_Positions[6].i=i+1;
    Near_Positions[6].j=j-1;

    Near_Positions[7].i=i-1;
    Near_Positions[7].j=j-1;

    *nb_active_player_move_positions=0;
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (soldiers[i].position.i!=Near_Positions[j].i && soldiers[i].position.j!=Near_Positions[j].j)
            {
                active_player_move_positions = malloc(sizeof(Position));
                active_player_move_positions[*nb_active_player_move_positions]=Near_Positions[j];
                *nb_active_player_move_positions+=1;
            }
        }
        
    }
    
  return *nb_active_player_move_positions;  
}


 void printTest(Position* active_player_move_positions,int* nb_active_player_move_positions){
     active_player_move_positions = malloc(sizeof(Position));
                                if (active_player_move_positions == NULL)
                                {
                                    // Handle memory allocation failure
                                    SDL_ExitWithError("Failed to allocate memory");
                                }

                                active_player_move_positions->i = 5;
                                active_player_move_positions->j = 5;

                                (active_player_move_positions+1)->i=4;
                                (active_player_move_positions+1)->j=4;

                                printf("i active_player_move_positions=%d\n", (active_player_move_positions+1)->i);

                                // Remember to free the allocated memory when you're done using it
                                free(active_player_move_positions);
 }