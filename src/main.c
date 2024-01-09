#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

//myfiles game
#include "board/board.h"
#include "game/game.h"
#include "soldier/soldier.h"
//myfiles utils
#include "utils/utils.h"

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650


//init teams
Team team_A = {'A', "GREEN", NULL};
Team team_B = {'B', "RED", NULL};


int game_on=1;


int nb_active_player_move_positions=0;
Position* active_player_move_positions=NULL;
Team active_player_team={'A', "GREEN", NULL};
int move_positions_activated=0;
Soldier active_soldier={{'X', "X", NULL},{0,0}};







void SDL_ExitWithError(const char *message);

int main(int argc, char **argv) {
    
    /*SDL_version nb;
    SDL_VERSION(&nb);

    //printf("Bienvenue sur la SDL %d %d %d\n",nb.major,nb.minor,nb.patch);
    */

   // SDL initialization and main loop code here
   //=>> SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // wela njm tou nhot : SDL_Init(SDL_INIT_EVERYTHING)
   // ken tout va bien bch trj3li 0 

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
       SDL_ExitWithError("Initialisation SDL"); 
    }

//----MAIN CODE HERE----------------------------------------------------------------



    //--create the window and the renderer----------------------------------------------------------------
if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
{
     SDL_ExitWithError("window and rederer creation");
}

// tab matrice nhot fih les rect te3i lkol
    SDL_Rect board_Matrice_sdlRect[10][10];

//step 1 : draw the board 
draw_board(renderer,board_Matrice_sdlRect);

//step 2 : place the soldiers of team A and B 
Soldier soldiers[30];
init_all_soldiers(soldiers,window,renderer,board_Matrice_sdlRect,&team_A,&team_B);

//show teamCamps of every team 

for (int i = 0; i < 15; i++)
{
    printf("teamB position : %d %d\n",team_B.TeamCamp[i].i,team_B.TeamCamp[i].j);
}
for (int i = 0; i < 15; i++)
{
    printf("teamA position : %d %d\n",team_A.TeamCamp[i].i,team_A.TeamCamp[i].j);
}






////// music 






 


//-------------------------------------------------------------------------
    //renderer ykhalini najm nsawer 3l window 3ibara saboura bl pixelet
    //nektebha hedhi b3d mankaml taswir bch yzidha 
    SDL_RenderPresent(renderer);

    // SDL_RenderClear(renderer);
    //       if(SDL_RenderClear(renderer)!=0) {
    //     SDL_ExitWithError("renderer deletion");
    // }

   


    //nkhali lwindow ma7loul 5sec
    //  SDL_Delay(5000);
    // nhot loop bch prog maytsaker ela mansakrou
    SDL_bool program_launched = SDL_TRUE;
    while (program_launched)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    free(active_player_move_positions);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    printf("mouse button down\n");
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            SDL_Rect rect = board_Matrice_sdlRect[i][j];
                            if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
                            {
                                Position position_activated = {i, j};
                                printf("Clicked on rectangle at board_Matrice_sdlRect[%d][%d]\n", i, j);

                                //step 1 : test if possibilites are activated or not => move to test if soldier or nothing 
                                if (move_positions_activated==1)
                                {
                                    //possibilities activated
                                    printf("possibilities activated\n");
                                    //step 1.1 : test if the position clicked is one a soldier position or a possible moving position
                                int position_activated_is_a_soldier_position=0;
                                for (int i = 0; i < 30; i++)
                                {
                                    if(position_activated.i==soldiers[i].position.i && position_activated.j==soldiers[i].position.j){
                                        position_activated_is_a_soldier_position=1;
                                        break;
                                    }
                                }
                                //step 1.2 : test if the position clicked is one a soldier position or a possible moving position
                                int position_activated_is_a_possible_moving_position=0;
                                for (int i = 0; i < nb_active_player_move_positions; i++)
                                {
                                    if(position_activated.i==active_player_move_positions[i].i && position_activated.j==active_player_move_positions[i].j){
                                        position_activated_is_a_possible_moving_position=1;
                                        break;
                                    }
                                }

                                
                            //main if 
                                if (position_activated_is_a_soldier_position==1)
                                {
                                    printf("a soldier position\n"); 
                                    //step 2 : check if the soldier is from the active player team
                                    int position_activated_is_from_active_player_team=0;
                                    for (int i = 0; i < 30; i++)
                                    {
                                        if(position_activated.i==soldiers[i].position.i && position_activated.j==soldiers[i].position.j){
                                            if(soldiers[i].team.name==active_player_team.name){
                                                position_activated_is_from_active_player_team=1;
                                                active_soldier=soldiers[i];
                                                break;
                                            }
                                        }
                                    }
                                    //main if 2 
                                    if (position_activated_is_from_active_player_team==1)
                                    {
                                        printf("active player team\n");
                                        //see close possibilities
                                         //see close possibilities
                                         free(active_player_move_positions);
                                            active_player_move_positions=NULL;
                                            see_close_Possibilities(position_activated,soldiers,&active_player_move_positions,&nb_active_player_move_positions,board_Matrice_sdlRect,&active_soldier);
                                           find_all_jump_positions(soldiers,position_activated,&active_player_move_positions,&nb_active_player_move_positions);
                                            //print all possibilities
                                                    for (int zzz = 0; zzz < nb_active_player_move_positions; zzz++)
                                                    {
                                                        printf("active_player_move_positions[%d] : %d %d\n",zzz,active_player_move_positions[zzz].i,active_player_move_positions[zzz].j);
                                                    }
                                        if (game_on==1)
                                        {
                                            //clear renderer
                                            SDL_RenderClear(renderer);
                                            //redraw game
                                            redraw_game(soldiers,board_Matrice_sdlRect,renderer,window);
                                            //draw possibilities
                                            draw_possibilities(&active_player_move_positions,&nb_active_player_move_positions,board_Matrice_sdlRect,renderer,window,&active_soldier);
                                        }
                                        
                                            

                                    }
            
                                }
                                else if(position_activated_is_a_possible_moving_position==1) {
                                   printf("possible moving possition\n"); 
                                   //move soldier
                                      move_Soldier(&active_soldier,position_activated,soldiers,&team_A,&team_B,renderer,window,&game_on);
                                      if (game_on==1)
                                        {
                                    //clear renderer
                                    SDL_RenderClear(renderer);
                                   //redraw game
                                    redraw_game(soldiers,board_Matrice_sdlRect,renderer,window);
                                   move_positions_activated=0;
                                   //change the active team 
                                   if (active_soldier.team.name=='A')
                                   {
                                    active_player_team.name = 'B';
                                    active_player_team.color = "RED";
                                    active_player_team.TeamCamp = NULL;
                                   }
                                   else
                                   {
                                    active_player_team.name = 'A';
                                    active_player_team.color = "GREEN";
                                    active_player_team.TeamCamp = NULL;
                                   }
                                   

                                }}

                                }else{
                                    printf("possibilities not activated\n");
                                    //possibilities not activated
                                    //test if the active position is a soldier or not 
                                    int position_activated_is_a_soldier_position=0;
                                    for (int i = 0; i < 30; i++)
                                    {
                                        if(position_activated.i==soldiers[i].position.i && position_activated.j==soldiers[i].position.j){
                                            position_activated_is_a_soldier_position=1;
                                            break;
                                        }}
                                    if (position_activated_is_a_soldier_position==1)
                                    {
                                        printf("a soldier position\n");
                                        //step 2 : check if the soldier is from the active player team
                                        int position_activated_is_from_active_player_team=0;
                                        for (int i = 0; i < 30; i++)
                                        {
                                            if(position_activated.i==soldiers[i].position.i && position_activated.j==soldiers[i].position.j){
                                                if(soldiers[i].team.name==active_player_team.name){
                                                    position_activated_is_from_active_player_team=1;
                                                    active_soldier=soldiers[i];
                                                    break;
                                                }
                                            }
                                        }

                                        if (position_activated_is_from_active_player_team==1)
                                        {

                                            //see close possibilities
                                            free(active_player_move_positions);
                                            active_player_move_positions=NULL;
                                            see_close_Possibilities(position_activated,soldiers,&active_player_move_positions,&nb_active_player_move_positions,board_Matrice_sdlRect,&active_soldier);
                                            find_all_jump_positions(soldiers,position_activated,&active_player_move_positions,&nb_active_player_move_positions);                                             
                                                    //print all possibilities
                                                    for (int zzz = 0; zzz < nb_active_player_move_positions; zzz++)
                                                    {
                                                        printf("active_player_move_positions[%d] : %d %d\n",zzz,active_player_move_positions[zzz].i,active_player_move_positions[zzz].j);
                                                    }
                                    if (game_on==1)
                                        {
                                            //clear renderer
                                            SDL_RenderClear(renderer);
                                            //redraw game
                                            redraw_game(soldiers,board_Matrice_sdlRect,renderer,window);
                                            //draw possibilities
                                            draw_possibilities(&active_player_move_positions,&nb_active_player_move_positions,board_Matrice_sdlRect,renderer,window,&active_soldier);
                                            move_positions_activated=1;
                                        } }
                                        
                                    }
                                    else{
                                        printf("not a soldier position 2\n");
                                    }
                                    
                                    

                                 }  
                                break;
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }



//-------------------------------------------------------------
    // SDL_CloseAudioDevice(audioDevice);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // free allocated memory in the SDL PROJECT file
    return EXIT_SUCCESS;
}





    



//compile w nhot el fich compile fel bin w nsamih prog ywalili prog.exe
// gcc src/main.c -o bin/prog -I  include -L lib -lmingw32 -lSDL2main -lSDL2
//n7elou b3d ma compilitou 
// bin/prog.exe

//lezm nincludi l .c lkol 
//gcc src/utils/utils.c src/board/board.c  src/soldier/soldier.c src/game/game.c src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2