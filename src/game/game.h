#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "../soldier/soldier.h"

//myfiles utils
#include "../utils/utils.h"


void redraw_game(Soldier soldiers[30],SDL_Rect board_Matrice_sdlRect[10][10],SDL_Renderer *renderer, SDL_Window* window);




#endif // GAME_H