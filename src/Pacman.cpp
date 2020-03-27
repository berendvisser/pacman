/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#include "Pacman.h"


Pacman::Pacman(Board* tmpBoard) :MovableEntity(tmpBoard),Entity()
{
	this->entityType.type = PACMAN; //initial type
    this->score = 0;//initial score
    this->lives = 5;//initial lives
}
Pacman::~Pacman()
{
}


void Pacman::checkCollision(std::vector<Eatable*>& tmpEatableList, std::vector<Ghost*> &tmpGhosts)
{
    for (size_t i = 0; i < tmpEatableList.size(); i++) //loop over all eatables
    {
        if (this->hasCollided(tmpEatableList[i])) //check if pacman collided with eatable in list
        {
            int scoreOnCollion = tmpEatableList[i]->getScoreOncollision(); //get score on collision

            if (scoreOnCollion > 0) //if score is more than one
            {
                this->increaseScore(tmpEatableList[i]->getScoreOncollision()); //increase score of pacman

                delete tmpEatableList[i]; //Delete object from memory
                tmpEatableList.erase(tmpEatableList.begin() + i); //erase pointer from list
            }
            else //energizer gives 0 points so this statement is triggered
            {
                delete tmpEatableList[i]; //Delete energizer from memory
                tmpEatableList.erase(tmpEatableList.begin() + i); //erase pointer from list

                this->scareGhosts(tmpGhosts); //scare all ghosts
            }

        }

    }

    for (size_t i = 0; i < tmpGhosts.size(); i++) //loop over all ghosts
    {
        if (this->hasCollided(tmpGhosts[i])) //check for collison with ghost
        {
            if (tmpGhosts[i]->getGhostScared())  //if ghost is scared
            {
                this->eatGhost(tmpGhosts[i]); //eat ghost
            }
            else //if not scared
            {
                this->loseLive(); 
                this->setPosition({ 1,1 }); //reset pacmans position
                this->resetGhosts(tmpGhosts); //reset position of ghosts
            }
        }
    }
}

void Pacman::eatGhost(Ghost* tmpGhosts)
{
    this->increaseScore(tmpGhosts->getScoreOncollision()); //increase score of pacman
    tmpGhosts->setPosition({ 12 , 13 }); //set position of ghost
    tmpGhosts->setScared(false); //set scared state of ghost
}

void Pacman::resetGhosts(std::vector<Ghost*>& tmpGhosts)
{
    for (size_t j = 0; j < tmpGhosts.size(); j++) //Loop over all ghosts
    {
        tmpGhosts[j]->setPosition({ 12 + (int)j,13 }); //Set position of ghosts
        tmpGhosts[j]->setScared(false); //set scared state of ghosts
    }
}

void Pacman::scareGhosts(std::vector<Ghost*>& tmpGhosts)
{
    for (size_t j = 0; j < tmpGhosts.size(); j++) //loop over all ghosts
    {
        
        tmpGhosts[j]->setScared(true);//scare ghosts
    }
}

unsigned Pacman::getLives()
{
    return this->lives; //return amount of lives of pacman
}

void Pacman::increaseScore(int points)
{
    this->score += points; //increase score of pacman by number of points
}

int Pacman::getScore()
{
    return this->score; //return score of pacman
}

void Pacman::loseLive()
{
    this->lives--; //reduce amount of lives of pacman by one
}

