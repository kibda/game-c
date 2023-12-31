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


//step 1 : draw the board 
    draw_board(renderer);

//step 2 : place the soldiers






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
        while (SDL_PollEvent(&event)) //bch n9raw les types t3 events li sayrin lkool
        {
            switch(event.type)
            {
                case SDL_QUIT: //kil user yquiti
                program_launched = SDL_FALSE;
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

//gcc src/board/board.c src/player/player.c src/soldier/soldier.c src/game/game.c src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2