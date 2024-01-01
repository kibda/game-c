
#include <SDL.h>
#include "soldier.h"

//myfiles utils
#include "../utils/utils.h"

//declare the teams 
Team teamA;
Team teamB;
Team teamC;
Team teamD;




// Initialize the soldier
void init_soldier(Soldier* soldier, Team team, Position position,SDL_Window *window,SDL_Renderer *renderer ,SDL_Rect board_Matrice_sdlRect[10][10]) {
    soldier->team = team;
    soldier->position = position;
    //nhothom fi les positions te3hom
     // FIHA MCHKLA 
    // SDL_Surface *image=NULL;
    // SDL_Texture *texture= NULL;

    // image =SDL_LoadBMP("C:/Users/benab/OneDrive/Documents/Fac/sesame/1ere/sem1/SD+C/mini proj/projs/test0.2/src/assets/soldiers/soldier1.bmp");
    // if(image==NULL){
    //     SDL_ExitWithError("image not loading");
    // }
    // //sn3na texture f SDL
    // texture = SDL_CreateTextureFromSurface(renderer, image);
    // SDL_FreeSurface(image);
    // if(texture==NULL){
    //    SDL_ExitWithError("texture not being created");
    // }

    // //taw bch nchargiwha fel memoire texture hedhi
    
    // if(SDL_QueryTexture(texture,NULL,NULL,&board_Matrice_sdlRect[position.i][position.j].w,&board_Matrice_sdlRect[position.i][position.j].h)!=0){
    //     SDL_DestroyRenderer(renderer);
    //   SDL_ExitWithError("chargement texture");
    // }

    // //nwari taswira background
   
    // if( SDL_RenderCopy(renderer,texture,NULL,&board_Matrice_sdlRect[position.i][position.j])!=0){
    //     SDL_DestroyRenderer(renderer);
    //      SDL_ExitWithError("impossible d'afficher texture");
    // }


}

// Initialize all soldiers
void init_all_soldiers(Soldier* soldiers,SDL_Window *window,SDL_Renderer *renderer,SDL_Rect board_Matrice_sdlRect[10][10]) {
    //team A 
    int nbSoldiersPerTeam=15;
    int nbSoldiersCounter=0;
    int counter=5;
    for (int i = 0; i < 10; i++)
    {
       int counter2=counter;
      for (int j = 0; j < 10; j++)
      {
        if (counter>0 && counter2>0)
        {
            Position position={i,j};
            init_soldier(&soldiers[nbSoldiersCounter],teamA,position,window,renderer,board_Matrice_sdlRect);
            nbSoldiersCounter++;
        }
        
      }
      
    }
    


}

// Check if soldier has moving possibilities
int has_Soldier_Moving_Possibilities(Soldier* soldier) {

    return 0;
}

// See soldier moving possibilities
void see_Soldier_Moving_Possibilities(Soldier* soldier) {

}

// Move the soldier
void move_Soldier(Soldier* soldier,Position new_position) {
    soldier->position = new_position;
    //nfaragh el rect eli fl position l9dima w ncopy texture w tswira fil pos jdida

}