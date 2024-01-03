#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

//myfiles game
#include "board/board.h"
#include "player/player.h"
#include "game/game.h"
#include "soldier/soldier.h"
//myfiles utils
#include "utils/utils.h"

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650

/*
    SDL_RENDERER_SOFTWARE      => bch ykhdem m3a el processor mch GC
    SDL_RENDERER_ACCELERATED   => material acceleration kn nheb nst3ml graphic card wela haja
    SDL_RENDERER_PRESENTVSYNC  => vertical synchronization
    SDL_RENDERER_TARGETTEXTURE => nrendri hasb texture mou3ayna
*/


int nb_active_player_move_positions=0;
Position* active_player_move_positions=NULL;

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


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVERYTHING) != 0) {
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
init_all_soldiers(soldiers,window,renderer,board_Matrice_sdlRect);

// for (int i = 0; i < 30; i++)
// {
//     printf("soldier %d :  position : %d %d\n",i,soldiers[i].position.i,soldiers[i].position.j);
    
// }





 //draw a red circle with a low opacity inside of the sdl rect board_Matrice_sdlRect[8][1] 
 
//      if (SDL_RenderCopy(renderer, texture, NULL, &board_Matrice_sdlRect[8][8]) != 0) {
//                 SDL_DestroyRenderer(renderer);
//                  SDL_ExitWithError("Failed to render texture");
//                  free(soldiers);
//              }


//step 3 : check if the soldier clicked on has moving possibilities

// see_Soldier_Moving_Possibilities(soldier,soldiers,active_player_move_positions,nb_active_player_move_positions)


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
                                //clear renderer
                                // SDL_RenderClear(renderer);
                                
                                //printTest(active_player_move_positions,nb_active_player_move_positions);
                                see_Soldier_Moving_Possibilities(position_activated,soldiers,&active_player_move_positions,&nb_active_player_move_positions,renderer,board_Matrice_sdlRect,window);
                                // for (int i = 0; i < *nb_active_player_move_positions; i++)
                                // {
                                //     printf("active_player_move_positions[%d] : %d %d\n",i,active_player_move_positions[i].i,active_player_move_positions[i].j);
                                // }
                                // printf("nb_active_player_move_positions : %d\n",*nb_active_player_move_positions);
                            //    printf("nb_active_player_move_positions 2 : %d\n", nb_active_player_move_positions);
                            //     printf("i active_player_move_positions 1=%d\n", (active_player_move_positions)->i);
                            
                          
                        //   free(active_player_move_positions);  
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

//gcc src/utils/utils.c src/board/board.c src/player/player.c src/soldier/soldier.c src/game/game.c src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2