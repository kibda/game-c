#include "utils.h"
#include <SDL.h>





 void SDL_ExitWithError(const char* message){
    SDL_Log("Error: %s: %s\n",message, SDL_GetError());
    SDL_Quit();
       exit(EXIT_FAILURE);
 } 