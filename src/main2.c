#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

/*  nsn3 kol wehed wahdou el window w renderer
    //create window----------------------------------------------------------------
    window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    
    //ken matsan3etch nlanci error
    if(window == NULL) {
        SDL_ExitWithError("window creation");
    }

    //---------------------------------------------------------

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

        if(renderer == NULL) {
        SDL_ExitWithError("renderer creation");
    }

*/

//-------------------------------------------------------------
/*
    //nbadel loun el renderer (loun li bch ntraci bih)  => alwen bl RGB w lekhrenia opacity eki liktebtha ena m3netha full
    if(SDL_SetRenderDrawColor(renderer,112,168,237,SDL_ALPHA_OPAQUE)!=0){
        SDL_ExitWithError("changing renderer color");
    }

    //nswaer point  => X, Y
    if(SDL_RenderDrawPoint(renderer,100,450)!=0){
        SDL_ExitWithError("drawing a point");
    }

    //nswaer line  => X, Y -> X, Y 
    if(SDL_RenderDrawLine(renderer,100,450,300,460)!=0){
        SDL_ExitWithError("drawing a line");
    }

     //nswaer rectangle  => 
     SDL_Rect rectangle;
     rectangle.x=300;
     rectangle.y=300;
     rectangle.w=200;
     rectangle.h=120;
      //njm nbadel color
        if(SDL_SetRenderDrawColor(renderer,255,168,237,SDL_ALPHA_OPAQUE)!=0){
        SDL_ExitWithError("changing renderer color");
        }

    if(SDL_RenderDrawRect(renderer, &rectangle) != 0){
        SDL_ExitWithError("drawing a line");
    }

    //nsware recatngle m3ebbi
    SDL_Rect rectangle2;
     rectangle2.x=50;
     rectangle2.y=50;
     rectangle2.w=100;
     rectangle2.h=90;
      //njm nbadel color
        if(SDL_SetRenderDrawColor(renderer,255,201,237,SDL_ALPHA_OPAQUE)!=0){
        SDL_ExitWithError("changing renderer color");
        }

    if(SDL_RenderFillRect(renderer, &rectangle2) != 0){
        SDL_ExitWithError("drawing a line");
    }
*/
//--TEXTURE----------------------------------------------------------------
    SDL_Surface *image=NULL;
    SDL_Texture *texture= NULL;

    image =SDL_LoadBMP("src/Cropped_Background.bmp");
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
    rectangle3.x = (WINDOW_WIDTH - rectangle3.w) / 2;
    rectangle3.y = (WINDOW_HEIGHT| - rectangle3.h) / 2;

    //nwari taswira background
   
    if( SDL_RenderCopy(renderer,texture,NULL,&rectangle3)!=0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("impossible d'afficher texture");
    }


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

 void SDL_ExitWithError(const char* message){
    SDL_Log("Error: %s: %s\n",message, SDL_GetError());
    SDL_Quit();
       exit(EXIT_FAILURE);
 } 
    



//compile w nhot el fich compile fel bin w nsamih prog ywalili prog.exe
// gcc src/main.c -o bin/prog -I  include -L lib -lmingw32 -lSDL2main -lSDL2
//n7elou b3d ma compilitou 
// bin/prog.exe