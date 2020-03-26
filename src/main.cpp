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
#include "Eatable.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Fruit.h"


//function prototypes
void fillMap(std::vector<Eatable*>& tmpEatables, Board& map);




Uint32 gameUpdate(Uint32 interval, void * param)
{
    // Do game loop update here
    void** x = static_cast<void**>(param);  //turn void* into array of pointers
    Direction* tmpdirectionkey = static_cast<Direction*>(x[1]); //turn void *  into direction *
    Direction* tmpdirectiontick = static_cast<Direction*>(x[2]); // ""
    *tmpdirectiontick = *tmpdirectionkey;  //set directionkey to current direction

    unsigned * tmpTick = static_cast<unsigned*>(x[0]); //cast void* to unsigned *
    (*tmpTick)++; //increase amount of ticks
    return interval;
}


int main(int /*argc*/, char ** /*argv*/)
{
    //initialization code
    Board map; 
    Direction inputDirKey = LEFT;
    Direction inputDirTick = LEFT;



    unsigned previousTicks = 0; //used to check if game can go to next tick
    unsigned currentTicks = 1; //keeps tracks of how many ticks have passed
    
    void* parameters[3] = { &currentTicks,&inputDirKey, &inputDirTick};

    // Create a new ui object
    UI ui(map.getBoard()); // <-- use map from your game objects.

   
    SDL_TimerID timer_id = SDL_AddTimer(200, gameUpdate, parameters); //updates the amount of ticks and keyboardinput


    /*_______________________________________________________*/
    //add pacman 
    Pacman pacman(&map);
    pacman.setPosition({ 1, 2 });//set position of pacman on the map


    /*_______________________________________________________*/
    //add dots
    std::vector<Eatable*> dots;



    //Fills board with dots
    fillMap(dots, map);


    /*_______________________________________________________*/
    //Add energizers
    std::vector<Eatable*> energizers; //vector of all energizers

    /*init energizers*/
    for (int i = 0; i < 4; i++)
    {
        energizers.push_back(new Eatable(ENERGIZER));
        energizers.back()->setScoreOnCollision(0);
    }
    /*Set position of energizers on map*/
    energizers[0]->setPosition({ 1, 1 });
    energizers[1]->setPosition({ 1, 25 });
    energizers[2]->setPosition({ 26, 1 });
    energizers[3]->setPosition({ 26, 25 });

    /*_______________________________________________________*/
    /*init ghosts*/
    Ghost inky(INKY, &map);
    Ghost pinky(PINKY, &map);
    Ghost blinky(BLINKY, &map);
    Ghost clyde(CLYDE, &map);

    std::vector<Ghost*> ghosts = { &inky, &pinky, &blinky, &clyde }; //vector of ghosts on map

    /*set initial position of ghosts*/
    inky.setPosition({ 12,13 });
    pinky.setPosition({ 13,13 });
    blinky.setPosition({ 14,13 });
    clyde.setPosition({ 15,13 });

    /*_______________________________________________________*/
    //add fruit
    std::vector<Eatable*> fruits; //vector of fruits on map
    
    int fruitCounter = 100; //score before first fruit is dropped




    /*_______________________________________________________*/
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
                case SDLK_SPACE:
                    if (previousTicks == 1000000) {
                        previousTicks = currentTicks;
                    }
                    else
                    {
                        previousTicks = 1000000;
                    }
                    
                }
            }
        }

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
            std::vector<GameObjectStruct> objects; //objects to be rendered

            if (currentTicks > previousTicks)
            {
                

                //Move pacman
                pacman.setDirection(inputDirTick);//set new input direction
                pacman.moveEntity();

                //Check collision after pacman has moved
                pacman.checkCollision(dots, ghosts);
                pacman.checkCollision(energizers, ghosts);
               
                //move ghosts
                pinky.setNewDirection();
                pinky.moveEntity();
                blinky.setNewDirection();
                blinky.moveEntity();
                inky.setNewDirection();
                inky.moveEntity();
                clyde.setNewDirection();
                clyde.moveEntity();

                /*Check collision with fruit and ghosts needs to be check after ghosts have moved in order not to mis collisions*/
                pacman.checkCollision(fruits, ghosts); 

                //Spawn fruit if certain score has been achieved
                if (fruitCounter < pacman.getScore())
                {
                    fruitCounter += 100;
                    fruits.push_back(new Fruit(&map));
                }


                //add dots to render list
                if (dots.size() == 0)
                {
                    std::cout << "Won game, scored:" << pacman.getScore()<< " points!";
                    quit = true;
                }

                size_t i;
                //add dots to renderlist
                for (i = 0; i < dots.size(); i++)
                {
                    objects.push_back(dots[i]->getEntityType());
                }

                //add energizers to renderlist
                for (i = 0; i < energizers.size(); i++)
                {
                    objects.push_back(energizers[i]->getEntityType());
                }
                    
                //Add fruits to render list

                for (i = 0; i < fruits.size(); i++)
                {
                    objects.push_back(fruits[i]->getEntityType());
                }
            
                //add ghosts to render list
                for (i = 0; i <ghosts.size(); i++)
                {
                    objects.push_back(ghosts[i]->getEntityType());
                }

                //add pacman to render list
                objects.push_back(pacman.getEntityType());
                
                //set score and lives
                ui.setLives(pacman.getLives());                
                ui.setScore(pacman.getScore());
                                
                //update map
                ui.update(objects);
                
                previousTicks = currentTicks; //update amount of previous ticks
            }

            if (!pacman.getLives())
            {
                quit = true; //exit game
                std::cout << "Game lost, scored " << pacman.getScore() << " points!\n"; //print score
            }



        }

    }

    SDL_RemoveTimer(timer_id);

    return 0;
}

/*fills all paths on the map with dots*/
void fillMap(std::vector<Eatable*> &tmpEatables, Board &map) 
{
    for (int y = 0; y < map.getBoardSizeY(); y++) //loop over all rows
    {
        for (int x = 0; x < map.getBoardSizeX(); x++) //loop over all rows
        {
            if (!map.isWall({ x,y })) //if no wall is found
            {
                tmpEatables.push_back(new Eatable(DOT)); // allocate on heap, to make compatibale with ghost and fruit
                tmpEatables.back()->setPosition({ x,y }); //set position of dot
            }

        }
    }

};


