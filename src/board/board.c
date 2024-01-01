#include "board.h"
#include <SDL.h>
#include "../utils/utils.h"

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650




void draw_board(SDL_Renderer *renderer,SDL_Rect tab[10][10]) {
        // draw a chess board on the window
    // 1st step: set the color of the renderer
    //nbadel loun el renderer (loun li bch ntraci bih)  => alwen bl RGB w lekhrenia opacity eki liktebtha ena m3netha full
        if(SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE) != 0){
             SDL_ExitWithError("changing renderer color");
        }


    // 2nd step: draw the chessboard
        // Define the size of each square on the chessboard
        int squareSize = WINDOW_WIDTH / 10;

        // Set the initial position of the square
        int x = 0;
        int y = 0;

        

        //loop through each row and column to draw the chessboard
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                // Create a rectangle for each square
                SDL_Rect squareRect = {x, y, squareSize, squareSize};
                tab[row][col] = squareRect;

                // Set the color of the square based on its position
                if ((row + col) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White 
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Black 
                }

                // Fill the square with the selected color
                SDL_RenderFillRect(renderer, &squareRect);

                // Update the position of the square
                x += squareSize;
            }

            // Reset the x position and move to the next row
            x = 0;
            y += squareSize;
        }
}



