#ifndef SOLDIER_H
#define SOLDIER_H

#include <SDL.h>

//myfiles utils
#include "../utils/utils.h"


typedef struct Soldier {
    
    char team; // 'A' or 'B'  
    Position position; // position of the soldier on the board
    
} Soldier;

    // les possb li ynjm yt7arakhom
    void see_Soldier_Moving_Possibilities(struct Soldier* soldier);
    
    // Function pointer for moving the soldier
    void move_Soldier(struct Soldier* soldier);


#endif // SOLDIER_H