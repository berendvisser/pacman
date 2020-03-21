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
#include "Eatable.h"
#include "Ghost.h"






void checkCollion(MovableEntity& tmpMovable, std::vector<Eatable*>& tmpEatableList, int& score, unsigned &tmpLives);


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

    unsigned lives = 5;

    unsigned previousTicks = 0;
    unsigned currentTicks = 1;
    
    void* parameters[3] = { &currentTicks,&inputDirKey, &inputDirTick};

    // Create a new ui object
    UI ui(map.getBoard()); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(200, gameUpdate, parameters);



    //add pacman 
    MovableEntity pacman(PACMAN, &map);
    pacman.setPosition({ 1, 1 });

    std::vector<Eatable*> dots;

    //Fills board with dots
    for (int y = 0; y < map.getBoardSizeY(); y++)
    {
        for (int x = 0; x < map.getBoardSizeX(); x++)
        {
            if (!map.isWall({ x,y }))
            {
                dots.push_back(new Eatable(DOT)); // allocate on heap, to make compatibale with ghost and fruit
                dots.back()->setPosition({ x,y });
            }
            
        }
    }

    //init ghosts
    Ghost inky(INKY, &map);
    Ghost pinky(PINKY, &map);
    Ghost blinky(BLINKY, &map);
    Ghost clyde(CLYDE, &map);

    std::vector<Eatable*> ghosts = { &inky, &pinky, &blinky, &clyde };

    inky.setPosition({ 12,13 });
    pinky.setPosition({ 13,13 });
    blinky.setPosition({ 14,13 });
    clyde.setPosition({ 15,13 });

    

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
            std::vector<GameObjectStruct> objects;
            
            
            

            if (currentTicks > previousTicks)
            {
                


                pacman.setDirection(inputDirTick);//set new input direction
                pacman.moveEntity(); //move pacman
                checkCollion(pacman, dots, score, lives); //check if pacman collided with dots
                checkCollion(pacman, ghosts, score, lives); //check if pacman collided with ghosts


                
                //move ghosts
                pinky.setNewRandomDirection();
                pinky.moveEntity();
                blinky.setNewRandomDirection();
                blinky.moveEntity();
                inky.setNewRandomDirection();
                inky.moveEntity();
                clyde.setNewRandomDirection();
                clyde.moveEntity();

                checkCollion(pacman, dots, score, lives); //check if pacman collided with dots
                checkCollion(pacman, ghosts, score, lives); //check if pacman collided with ghosts


                //add dots to render list
                if (dots.size() == 0)
                {
                    std::cout << "Won game!\n";
                    quit = true;
                }
                for (int i = 0; i < dots.size(); i++)
                {
                    objects.push_back(dots[i]->getEntityType());
                }
                //add ghosts to render list
                for (int i = 0; i <ghosts.size(); i++)
                {
                    objects.push_back(ghosts[i]->getEntityType());
                }

                //add pacman to render list
                objects.push_back(pacman.getEntityType());
                
                //set score and lives
                ui.setLives(lives);                
                ui.setScore(score);
                
                //update map
                ui.update(objects);
                
                previousTicks = currentTicks; //update amount of previous ticks
            }

            if (!lives)
            {
                quit = true; //exit game
                std::cout << "Game lost, scored " << score << " points!\n"; //print score
            }



        }

    }

    SDL_RemoveTimer(timer_id);

    return 0;
}

/*Function checks if movable entity collided with eatables*/
void checkCollion(MovableEntity &tmpMovable, std::vector<Eatable*> &tmpEatableList, int& score, unsigned &tmpLives)
{
    for (int i = 0; i < tmpEatableList.size(); i++)
    {
        if (tmpMovable.hasCollided(tmpEatableList[i]))
        {
            int scoreOnCollion = tmpEatableList[i]->getScoreOncollision();
            if (scoreOnCollion > 0)
            {
                score += scoreOnCollion;
                delete tmpEatableList[i];
                tmpEatableList.erase(tmpEatableList.begin() + i);
            }
            else
            {
                tmpLives--;
                tmpMovable.setPosition({ 1,1 });
                for (int j = 0; j < tmpEatableList.size(); j++)
                {
                    static_cast<Ghost*>(tmpEatableList[j])->setPosition({ 12 + j,13 });
                }
            }
        }

    }
}