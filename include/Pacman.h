/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once

#include "MovableEntity.h"
#include "Eatable.h"
#include "Ghost.h"


class Pacman : public MovableEntity
{
public:
    Pacman(Board* tmpBoard);

    ~Pacman();


    /*Check if pacman has collided with a ghost, a dot or a energizer and set ghosts to scared if */
    void checkCollision(std::vector<Eatable*>& tmpEatableList, std::vector<Ghost*>& tmpGhosts);

    /*Reset ghosts to ghostpenn*/
    void resetGhosts(std::vector<Ghost*>& tmpGhosts);

    /*Set ghosts to scared*/
    void scareGhosts(std::vector<Ghost*> &tmpGhosts);

    /*Eat ghost and increase points of pacman and put ghost in ghostpenn*/
    void eatGhost(Ghost* tmpGhosts);

    /*Get the amount of lives of pacman*/
    unsigned getLives();

    /*increase score of pacman by a certain amount*/
    void increaseScore(int points);

    /*Get the current score of pacman*/
    int getScore();

protected:
    /*Calling this function reduces the amout of live of pacman by one*/
    void loseLive();

private:
    int score; //The score of pacman
    unsigned lives; //The amount of lives of pacman
};
