#include <SDL.h>
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
