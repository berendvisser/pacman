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


/// Callback function to update the game state.
///
/// This function is called by an SDL timer at regular intervals.
/// Note that this callback may happen on a different thread than the main thread.
/// You therefore have to be careful in avoiding data races. For example, you
/// should use mutexes to access shared data.
/// Read the documentation of SDL_AddTimer for more information and for tips
/// regarding multithreading issues.
Uint32 gameUpdate(Uint32 interval, void * /*param*/)
{
    // Do game loop update here
    std::cout << interval << std::endl;
    return interval;
}

/// Program entry point.
int main(int /*argc*/, char ** /*argv*/)
{
    
    Board map;



    

    // Create a new ui object
    UI ui(map.getBoard()); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

    // Example object, this can be removed later
    GameObjectStruct pacman;
    pacman.x = 0;
    pacman.y = 8;
    pacman.type = PACMAN;
    pacman.dir = UP;

    GameObjectStruct ghost;
    ghost.x = 2;
    ghost.y = 1;
    ghost.dir = DOWN;
    ghost.type = BLINKY;

    // Call game init code here


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
                    pacman.dir = LEFT;
                    break;
                case SDLK_RIGHT: 
                    pacman.dir = RIGHT;
                    break;
                case SDLK_UP:
                    pacman.dir = UP;
                    break;
                case SDLK_DOWN:
                    pacman.dir = DOWN;
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }

        // Set the score
        ui.setScore(1); // <-- Pass correct value to the setter

        // Set the amount of lives
        ui.setLives(1); // <-- Pass correct value to the setter

        // Render the scene
        std::vector<GameObjectStruct> objects = {pacman};

        objects.push_back(ghost);



        ui.update(objects);

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
            ui.update(objects);



        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
