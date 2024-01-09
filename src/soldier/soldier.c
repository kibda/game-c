
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
void init_all_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10],Team* team_A,Team* team_B) {
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

    team_A->TeamCamp = malloc(15 * sizeof(Position));
    if (team_A->TeamCamp == NULL) {
        // Handle memory allocation failure
        SDL_ExitWithError("Failed to allocate memory");
    }
    team_B->TeamCamp = malloc(15 * sizeof(Position));
    if (team_B->TeamCamp == NULL) {
        // Handle memory allocation failure
        SDL_ExitWithError("Failed to allocate memory");
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
             team_B->TeamCamp[nb_soldiers] = position;
             // printf("soldier %d :  position : %d %d\n",nb_soldiers,soldiers[nb_soldiers].position.i,soldiers[nb_soldiers].position.j);
             nb_soldiers++;
                counter2--;  
            }
        }
        counter--;
    }

   
    // Fill the remaining lines starting from the last column with 1 soldier and incrementing by 1 until the board ends
        int teamCampCounter=0;
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
                    team_A->TeamCamp[teamCampCounter] = position;
                    // printf("soldier %d :  position : %d %d\n",nb_soldiers,soldiers[nb_soldiers].position.i,soldiers[nb_soldiers].position.j);
                    teamCampCounter++;
                    nb_soldiers++;
                    counter2--;
                }
            }
            counter--;
        }

    
    


}



// Callback function to play the audio
void audio_callback(void *userdata, Uint8 *stream, int len) {
    // userdata is a pointer to the audio buffer we passed
    Uint8 *audio_pos = (Uint8*)userdata;

    // Copy the audio data into the stream
    SDL_memcpy(stream, audio_pos, len);
}

void play_sound(const char* sound_file) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return;
    }

    // Load the WAV file
    Uint8 *audio_buf;
    Uint32 audio_len;
    SDL_AudioSpec wav_spec;
    if (SDL_LoadWAV(sound_file, &wav_spec, &audio_buf, &audio_len) == NULL) {
        printf("Failed to load WAV file: %s\n", SDL_GetError());
        return;
    }

    // Set the callback function
    wav_spec.callback = audio_callback;
    wav_spec.userdata = audio_buf;

    // Open the audio device
    if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
        printf("Failed to open audio: %s\n", SDL_GetError());
        return;
    }

    // Start playing the sound
    SDL_PauseAudio(0);

    // Wait for the sound to finish playing
    SDL_Delay(1000);  // Wait for 1 second. Adjust this to the length of your sound.

    // Clean up
    SDL_FreeWAV(audio_buf);
    SDL_CloseAudio();
    SDL_Quit();
}

// Check if soldier has moving possibilities
int has_Soldier_Moving_Possibilities(Soldier* soldier,Soldier soldiers[30]) {
    //nchf lblayes li les9in fiha ferghin wale
    int i = soldier->position.i;
    int j = soldier->position.j;
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

    int nb_active_player_move_positions = 0;

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
            nb_active_player_move_positions += 1;
        }
    }

   
    
    if (nb_active_player_move_positions > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
   
}

int check_team_took_other_team_positions(Soldier soldiers[30],Team* team_A,Team* team_B,Team active_team){
  
 
  if (active_team.name == 'B')
  {
    //check if all soldiers from team A are in team B camp
    int teamB_in_teamA_camp=0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (team_A->TeamCamp[i].i == soldiers[j].position.i && team_A->TeamCamp[i].j == soldiers[j].position.j && soldiers[j].team.name == 'B' )
            {
                teamB_in_teamA_camp++;
                break;
            }
        }
    }
    printf("teamB_in_teamA_camp=%d\n",teamB_in_teamA_camp);
    if (teamB_in_teamA_camp == 15)
    {
        return 1;
        
    }else{
        return 0;
    }
  }
  else if (active_team.name == 'A')
  {
    //check if all soldiers from team B are in team A camp
    int teamA_in_teamB_camp=0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (team_B->TeamCamp[i].i == soldiers[j].position.i && team_B->TeamCamp[i].j == soldiers[j].position.j && soldiers[j].team.name == 'A')
            {
                teamA_in_teamB_camp++;
                break;
            }
        }
    }
    printf("teamA_in_teamB_camp=%d\n",teamA_in_teamB_camp);
    if (teamA_in_teamB_camp == 15)
    {
        return 1;
        
    }else{
        return 0;
    }
  }
  
    
    
}


int check_other_team_cant_move(Soldier soldiers[30],Team active_team){
    printf("active_team.name=%c\n",active_team.name);
    int other_team_cant_move=0;
    if (active_team.name == 'B')
    {
        for (int i = 0; i < 30; i++)
        {
            if (soldiers[i].team.name == 'A')
            {
                if (has_Soldier_Moving_Possibilities(&soldiers[i],soldiers) == 0)
                {
                    other_team_cant_move++;
                }
                
            }
            
        }
        printf("other_team_cant_move A=%d\n",other_team_cant_move);
        if (other_team_cant_move == 15)
        {
            return 1;
        }else{
            return 0;
        }
        
    }
    else if (active_team.name == 'A')
    {
        for (int i = 0; i < 30; i++)
        {
            if (soldiers[i].team.name == 'B')
            {
                if (has_Soldier_Moving_Possibilities(&soldiers[i],soldiers) == 0)
                {
                    other_team_cant_move++;
                }
                
            }
            
        }
         printf("other_team_cant_move B=%d\n",other_team_cant_move);
        if (other_team_cant_move == 15)
        {
            return 1;
        }else{
            return 0;
        }
        
    }

}



// Move the soldier
void move_Soldier(Soldier* soldier,Position new_position,Soldier soldiers[30],Team* team_A,Team* team_B ,SDL_Renderer *renderer,SDL_Window *window,int* game_on) {
    // soldier->position = new_position;
    //find the soldier in soldiers and move it to new_position
    for (int i = 0; i < 30; i++)
    {
        if (soldiers[i].position.i == soldier->position.i && soldiers[i].position.j == soldier->position.j)
        {
            soldiers[i].position.i = new_position.i;
            soldiers[i].position.j = new_position.j;
            break;
        }
    }
   // play_sound("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/sounds/took_enemy_position.wav");
//see if the soldier occupied one of the other teamCamp positions 
    if (soldier->team.name == 'A')
    {
        for (int i = 0; i < 15; i++)
        {
            if (team_B->TeamCamp[i].i == new_position.i && team_B->TeamCamp[i].j == new_position.j)
            {
                printf(" 1 team B camp position taken\n");
               int A_won= check_team_took_other_team_positions(soldiers,team_A,team_B,*team_A);
               if (A_won == 1)
               {
                //stop the game and show the winner A
                *game_on = 0;
                printf("A won\n");
                draw_end_game(renderer,window,*team_A);
               }
               
                break;
            }
        }
    }
    else if (soldier->team.name == 'B')
    {
        for (int i = 0; i < 15; i++)
        {
            if (team_A->TeamCamp[i].i == new_position.i && team_A->TeamCamp[i].j == new_position.j)
            {
                printf(" 1 team A camp position taken\n");
                int B_won= check_team_took_other_team_positions(soldiers,team_A,team_B,*team_B);
                if (B_won == 1)
               {
                //stop the game and show the winner B
                *game_on = 0;
                printf("B won\n");
                 draw_end_game(renderer,window,*team_B);
               }
                break;
            }
        }
    }


//see if the other team cant move
    if (check_other_team_cant_move(soldiers,soldier->team) == 1)
    {
        if (soldier->team.name == 'A')
        {
            *game_on = 0;
            printf("A won\n");
            draw_end_game(renderer,window,*team_A);
        }
        else if (soldier->team.name == 'B')
        {
            *game_on = 0;
            printf("B won\n");
            draw_end_game(renderer,window,*team_B);
        }
        
    }
    
// for (int i = 0; i < 30; i++)
// {
//     if (soldiers[i].position.i == 4 && soldiers[i].position.j == 0)
//     {
//         printf(" pos 4 0 has mov poss=%d\n",has_Soldier_Moving_Possibilities(&soldiers[i],soldiers));
//     }
    
// }


 
    

}









void place_soldiers(Soldier soldiers[30],SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]){
   
        for (int i = 0; i < 30; i++) {
            int pos_i = soldiers[i].position.i;
            int pos_j = soldiers[i].position.j;
            //printf("pos_i=%d pos_j=%d \n", pos_i,pos_j);
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
    


///////// new move possiblities /////////////
void see_close_Possibilities(Position soldier_pos,Soldier soldiers[30],Position** active_player_move_positions,int* nb_active_player_move_positions,SDL_Rect board_Matrice_sdlRect[10][10],Soldier* soldier) {
    //nchf lblayes li les9in fiha ferghin wale 
    int i=soldier_pos.i;
    int j=soldier_pos.j;

    //find the soldier that has the position pos_i,pos_j and change ACTIVE_SOLDIER so i can move it later 
    for (int ii = 0; ii < 30; ii++)
        {
            
            if (soldiers[ii].position.i == i && soldiers[ii].position.j == j)
            {
                // printf("soldier team: %c\n",soldiers[ii].team.name);
                *soldier = soldiers[ii];
                break;
                                }}

    //close positions 
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
    free(*active_player_move_positions);
    *active_player_move_positions = NULL;
    *nb_active_player_move_positions = 0;
    *active_player_move_positions = malloc(1 *sizeof(Position));
    if (*active_player_move_positions == NULL) {
        // Handle memory allocation failure
        SDL_ExitWithError("Failed to allocate memory");
    }

//nchf eli possible nbadel fihom w nbadel values ta3 lpointers
    for (int y = 0; y < near_positions_count; y++)
    {
        int isOccupied = 0;
        for (int x = 0; x < 30; x++)
        {
            if (soldiers[x].position.i == Near_Positions[y].i && soldiers[x].position.j == Near_Positions[y].j)
            {
                isOccupied = 1;
                //check_jump_positions(soldiers, soldier->position, Near_Positions[y].i - soldier->position.i, Near_Positions[y].j - soldier->position.j,active_player_move_positions,nb_active_player_move_positions);
                break;
            }
        }
        if (!isOccupied)
        {
            *active_player_move_positions = realloc(*active_player_move_positions, (*nb_active_player_move_positions + 1) * sizeof(Position));
            
            (*active_player_move_positions + *nb_active_player_move_positions)->i = Near_Positions[y].i;
            (*active_player_move_positions + *nb_active_player_move_positions)->j = Near_Positions[y].j;
            *nb_active_player_move_positions += 1;
            // printf( "active_player_move_positions %d %d\n",(*active_player_move_positions + *nb_active_player_move_positions)->i,(*active_player_move_positions + *nb_active_player_move_positions)->j);
        }
    }


}





///////// new jump possiblities /////////////
int is_valid_position(int i, int j) {
    return i >= 0 && i < 10 && j >= 0 && j < 10;
}

int is_position_empty(Soldier soldiers[], int num_soldiers, Position pos) {
    for (int i = 0; i < num_soldiers; i++) {
        if (soldiers[i].position.i == pos.i && soldiers[i].position.j == pos.j) {
            return 0;
        }
    }
    return 1;
}



void check_jump_positions(Soldier soldiers[30], Position pos, int directions[8][2], int num_directions, Position** active_player_move_positions, int* nb_active_player_move_positions) {
    int nb_soldiers = 30;

    for (int d = 0; d < num_directions; d++) {
        int di = directions[d][0];
        int dj = directions[d][1];

        Position next_pos = {pos.i + di, pos.j + dj};

        // pos mawjouda f west el board wala la
        if (!is_valid_position(next_pos.i, next_pos.j)) {
            continue;
        }

        //ken mawjoud fiha soldier
        if (!is_position_empty(soldiers, nb_soldiers, next_pos)) {
            Position next_next_pos = {next_pos.i + di, next_pos.j + dj}; //pos li ba3d next_pos fi direction t3 tanguiza li 9balha
            if (is_valid_position(next_next_pos.i, next_next_pos.j) && is_position_empty(soldiers, nb_soldiers, next_next_pos)) {
                //the next position is occupied bsoldier ama lposition after that is empty
                //naddi next_next_pos to the array of active player move positions

                //check if the position already exists in the array activeplayermove...
                int position_exists = 0;
                for (int i = 0; i < *nb_active_player_move_positions; i++)
                {
                    if ((*active_player_move_positions)[i].i == next_next_pos.i && (*active_player_move_positions)[i].j == next_next_pos.j)
                    {
                        position_exists = 1;
                        break;
                    }
                }

                if (!position_exists) {
                    *active_player_move_positions = realloc(*active_player_move_positions, (*nb_active_player_move_positions + 1) * sizeof(Position));

                    (*active_player_move_positions)[*nb_active_player_move_positions].i = next_next_pos.i;
                    (*active_player_move_positions)[*nb_active_player_move_positions].j = next_next_pos.j;

                    
                    (*nb_active_player_move_positions)++;

                    // y3awed test 3l position ejdida 
                    check_jump_positions(soldiers, next_next_pos, directions, num_directions, active_player_move_positions, nb_active_player_move_positions);
                }
            }
        }
    }
}

void find_all_jump_positions(Soldier soldiers[30], Position pos, Position** active_player_move_positions, int* nb_active_player_move_positions) {
    int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
    int num_directions = 8;


    // Call the recursive function with all possible directions
    check_jump_positions(soldiers, pos, directions, num_directions, active_player_move_positions, nb_active_player_move_positions);
}










//////////// comments old code could be useful if smth happened //////////////
// void check_jump_positions(Soldier soldiers[30], Position pos, int di, int dj,Position** active_player_move_positions,int* nb_active_player_move_positions) {
//     int nb_soldiers = 30;
//     Position next_pos = {pos.i + di, pos.j + dj};

//     if (!is_valid_position(next_pos.i, next_pos.j)) {
//         return;
//     }

//     if (!is_position_empty(soldiers, nb_soldiers, next_pos)) {
//         Position next_next_pos = {next_pos.i + di, next_pos.j + dj};
//         if (is_valid_position(next_next_pos.i, next_next_pos.j) && is_position_empty(soldiers, nb_soldiers, next_next_pos)) {
//             // The next position is occupied, but the position after that is empty.
//             // Do something here.
//             *active_player_move_positions = realloc(*active_player_move_positions, (*nb_active_player_move_positions + 1) * sizeof(Position));
            
//             (*active_player_move_positions)[*nb_active_player_move_positions].i = next_next_pos.i;
//             (*active_player_move_positions)[*nb_active_player_move_positions].j = next_next_pos.j;

//             // Increment the number of positions
//             (*nb_active_player_move_positions)++;

//             // Then, check the positions near next_next_pos.
//             check_jump_positions(soldiers, next_next_pos, di, dj,active_player_move_positions,nb_active_player_move_positions);
//         } 
//     }
// }




// void find_all_jump_positions(Soldier soldiers[30], Position pos, Position** active_player_move_positions, int* nb_active_player_move_positions) {
//     // Call the recursive function
//     check_jump_positions(soldiers, pos, -1, -1, active_player_move_positions, nb_active_player_move_positions);
//     check_jump_positions(soldiers, pos, -1, 0, active_player_move_positions, nb_active_player_move_positions);
//     check_jump_positions(soldiers, pos, -1, 1, active_player_move_positions, nb_active_player_move_positions);
//     check_jump_positions(soldiers, pos, 0, -1, active_player_move_positions, nb_active_player_move_positions);
//     check_jump_positions(soldiers, pos, 0, 1, active_player_move_positions, nb_active_player_move_positions);
//     check_jump_positions(soldiers, pos, 1, -1, active_player_move_positions, nb_active_player_move_positions);
//     check_jump_positions(soldiers, pos, 1, 0, active_player_move_positions, nb_active_player_move_positions);
//     check_jump_positions(soldiers, pos, 1, 1, active_player_move_positions, nb_active_player_move_positions);
   
// }


