#pragma once
#include "Entity.h"

class MovableEntity: virtual public  Entity
{
//accessable outside of class
public:
	/*Constructor takes entity type and board as parameters*/
	MovableEntity(Type EntityType, Board* tmpBoard) : Entity(EntityType)
	{
		
		this->map = tmpBoard; //Set map pointer to tmpBoard
	}

	/*Moves entity in current direction*/
	void moveEntity()
	{
		Position tmpPosition = getNextPosition(this->getPosition(), this->entityType.dir); //Get next position using current direction
		


		if (this->map->isWall(tmpPosition)) //check if new position is a wall
		{
			
		}
		else //set new position
		{
			this->setPosition(tmpPosition);// set new position
		}
	}

	/*Sets direction of movable entity if possible*/
	void setDirection (Direction dir)
	{
		Position tmpNextPosition = getNextPosition(this->getPosition(), dir); //get next position with the new direction

		if (this->map->isWall(tmpNextPosition)) //check if new position is wall
		{
			
		}
		else //set new direction
		{
			this->entityType.dir = dir;
		}
		
		
	}

	/*Return current direction*/
	Direction getDirection()
	{
		return this->entityType.dir;//return current direction
	}
	
	/*Get next position*/
	Position getNextPosition(Position curPos, Direction curDir)
	{
		
		unsigned boardSizeX = this->map->getBoardSizeX();//get boardsize X
		unsigned boardSizeY = this->map->getBoardSizeY();//get boardsize y

		/*offset current position by boardsize */
		curPos.x += boardSizeX; 
		curPos.y += boardSizeY;
		
		/*get next position using current position and direction*/
		switch (curDir)
		{
		case UP:
			curPos.y--;
			break;

		case DOWN:
			curPos.y++;
			break;

		case LEFT:
			curPos.x--;
			break;

		case RIGHT:
			curPos.x++;
			break;
		}

		/*remove offset to allow for teleport from onside to the other on map*/
		curPos.x %= boardSizeX;
		curPos.y %= boardSizeY;

		return curPos;

	}

	/*Checks if current entity has a collision with an other entity*/
	bool hasCollided(Entity *tmpEntity)
	{
		if (tmpEntity == NULL)
		{
			return false;
		}
		if (this->getPosition() == tmpEntity->getPosition())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
//should only be accessed by derived classes
protected:
	Board* map;
};
