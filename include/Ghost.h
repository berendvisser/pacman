#pragma once
#include "MovableEntity.h"
#include "Eatable.h"
#include <cstdlib>
#include <ctime>


class Ghost : public MovableEntity, public Eatable
{
public:
	


	/*Constructor*/
	Ghost(Type ghostType, Board* tmpBoard) :MovableEntity(ghostType, tmpBoard), Eatable(ghostType), Entity(ghostType)
	{
		this->setScoreOnCollision(-1);
		
	}

	/*Deconstructor*/
	~Ghost(){}



	void setNewRandomDirection()
	{
		Position testPosition;
		unsigned freeDirections = 0;

		for (unsigned i= 0; i < 4; i++)
		{
			testPosition = this->getNextPosition(static_cast<Direction>(i));
			if (!map->isWall(testPosition))
			{
				freeDirections++;
				
			}
		}

		if (freeDirections != 2)
		{
			this->setRandomDirection();
		}
		else
		{	
			Direction OppositeDir = this->getOppositeDirection();
			this->setRandomDirection();

			while (this->getDirection() == OppositeDir)
			{
				this->setRandomDirection();
			}
			
		}


	}
	/*returns true is new direction is opposite to current direction*/
	void setRandomDirection()
	{	
		
		bool x = this->setDirection(static_cast<Direction>(std::rand() % 4));
		while (!x)
		{
			x = this->setDirection(static_cast<Direction>(std::rand() % 4));
			void;
		}
	}

	/*Return opposite direction of Ghost*/
	Direction getOppositeDirection()
	{
		switch (this->getDirection()) {
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
	 
	

};