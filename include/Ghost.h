#pragma once

#include "MovableEntity.h"
#include "Eatable.h"
#include <cstdlib>
#include <ctime>


class Ghost : public MovableEntity, public Eatable
{
public:
	/*Constructor*/
	Ghost(Type ghostType, Board* tmpBoard) :MovableEntity(tmpBoard, ghostType), Eatable(ghostType), Entity(ghostType)
	{
		this->setScoreOnCollision(-1); //set score on collision
		
	}

	/*Deconstructor*/
	~Ghost(){}



	void setNewDirection()
	{
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


	/*Return opposite direction of Ghost*/
	Direction getOppositeDirection()
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
		}
			
				
	}
private:
	/*sets new random position*/
	void setRandomDirection()
	{

		//keep setting new random direction until new direction is valid
		while (!this->setDirection(static_cast<Direction>(std::rand() % 4)))
		{
		}
	}

	 
	

};