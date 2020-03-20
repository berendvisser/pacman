/// \file
/// main.cpp
//Berend Visser
//S1499270
//group:30

#include "GameObjectStruct.h"
#include "UI.h"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#include "Board.h"
#include "Entity.h"
#include "MovableEntity.h"


/// Callback function to update the game state.
///
/// This function is called by an SDL timer at regular intervals.
/// Note that this callback may happen on a different thread than the main thread.
/// You therefore have to be careful in avoiding data races. For example, you
/// should use mutexes to access shared data.
/// Read the documentation of SDL_AddTimer for more information and for tips
/// regarding multithreading issues.
Uint32 gameUpdate(Uint32 interval, void * param)
{
    // Do game loop update here
    void** x = static_cast<void**>(param);

    
    

    
    Direction* tmpdirectionkey = static_cast<Direction*>(x[1]);
    Direction* tmpdirectiontick = static_cast<Direction*>(x[2]);
    *tmpdirectiontick = *tmpdirectionkey;

    unsigned * tmpTick = static_cast<unsigned*>(x[0]);
    (*tmpTick)++;    
    return interval;
}

/// Program entry point.
int main(int /*argc*/, char ** /*argv*/)
{
    
    Board map;
    Direction inputDirKey = RIGHT;
    Direction inputDirTick = RIGHT;

    unsigned previousTicks = 0;
    unsigned currentTicks = 1;
    
    void* parameters[3] = { &currentTicks,&inputDirKey, &inputDirTick};

    // Create a new ui object
    UI ui(map.getBoard()); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(120, gameUpdate, parameters);

    
    MovableEntity pacman(PACMAN, &map);
    pacman.setPosition({ 1, 1 });
    Entity dot_1(DOT);
    dot_1.setPosition({ 1, 2 });

    
    


    // Call game init code here

    int score = 0;
    bool quit = false;
    while (!quit) {
        // set timeout to limit frame rate
        Uint32 timeout = SDL_GetTicks() + 20;

        // Handle the input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // Quit button.
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // All keydown events
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT: 
                    inputDirKey = LEFT;
                    break;
                case SDLK_RIGHT: 
                    inputDirKey = RIGHT;
                    break;
                case SDLK_UP:
                    inputDirKey = UP;
                    break;
                case SDLK_DOWN:
                    inputDirKey = DOWN;
                    break;
                case SDLK_ESCAPE:

                    quit = true;
                    break;
                }
            }
        }



        

        

       
        
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed

            if (currentTicks > previousTicks)
            {
                pacman.setDirection(inputDirTick);
                pacman.moveEntity();

                if (pacman.hasCollided(dot_1)) {
                    score++;                    
                }

                
                
                
                
                
                
                std::vector<GameObjectStruct> objects = { dot_1.getEntityType(), pacman.getEntityType() };
                ui.update(objects);
                ui.setScore(score);
                
                previousTicks = currentTicks;
            }





        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
