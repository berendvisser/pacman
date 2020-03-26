/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once
#include "Ghost.h"

Ghost::Ghost(Type ghostType, Board* tmpBoard) :MovableEntity(tmpBoard, ghostType), Eatable(ghostType), Entity(ghostType)
{
	this->setScoreOnCollision(-1); //set score on collision
	this->isScared = false; //set initial scared state
	this->normalType = ghostType; //set type to return to after scared state
	std::srand((unsigned int)std::time(NULL)); //set seed for random movement behaviour	
}

/*Deconstructor*/
Ghost::~Ghost()
{
}

void Ghost::setNewDirection()
{		
	this->updateScaredState();


	Position freePosition; //free position with respect to current spot
	unsigned freeDirections = 0; //number of directions to choose from

	for (unsigned i= 0; i < 4; i++)//loop to check all four direciton around current spot
	{
		freePosition = this->getNextPosition(static_cast<Direction>(i)); //check first direction
			
		if (!map->isWall(freePosition))//check if there is not a wall in current position
		{
			freeDirections++; //increase number of free positions if no wall is found
				
		}
	}

	if (freeDirections != 2) //if 1, 3 or 4 directions are possible 
	{
		this->setRandomDirection(); //pick a random direction out of the possible directions
	}
	else //if only two directions are possible
	{	
		Direction OppositeDir = this->getOppositeDirection(); //get direction opposite to current direction
		this->setRandomDirection(); //pick random direction

		while (this->getDirection() == OppositeDir) //keep checking for a new direction that is not opposite to current direction
		{
			this->setRandomDirection(); //set new random direction
		}
			
	}


}

void Ghost::setScared(bool scared)
{
	
	this->isScared = scared; //set state of ghost
	this->ticksLeftScared = 50; //set time of being scared
	this->setScoreOnCollision(20); //set score for eating ghost



}

bool Ghost::getGhostScared()
{
	return this->isScared; //return scared state of ghost
}

void Ghost::updateScaredState()
{
		
	if (this->isScared && this->ticksLeftScared > 0) //check if ghost is scared and time of being scared has not run out yet
	{
		this->ticksLeftScared--; //decrement timer for being scared
		this->entityType.type = SCARED; //set ghosttype to scared
	}
	else
	{
		this->setScared(false); //Set state of ghost to not scared when timer has run out or ghost have been reset
		this->entityType.type = this->normalType;//set ghost back to initial type
		this->setScoreOnCollision(-1); //set score on collision back to normal
			
	}

}

Direction Ghost::getOppositeDirection()
{
	switch (this->getDirection()) //switch on current direction
	{
		//return inverse
	case UP:
		return DOWN;
		break;
	case DOWN:
		return UP;
		break;
	case LEFT:
		return RIGHT;
		break;
	case RIGHT:
		return LEFT;
		break;
	default:
		return LEFT;
	}
			
				
}

void Ghost::setRandomDirection()
{

	//keep setting new random direction until new direction is valid
	while (!this->setDirection(static_cast<Direction>(std::rand() % 4)))
	{
	}
}

