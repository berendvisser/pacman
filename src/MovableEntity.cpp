/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#include "MovableEntity.h"



MovableEntity::MovableEntity(Board* tmpBoard, Type EntityType) : MovableEntity::Entity(EntityType)
{
		
	this->map = tmpBoard; //Set map pointer to tmpBoard
}


MovableEntity::~MovableEntity()
{
}


void MovableEntity::moveEntity()
{
	Position tmpPosition = getNextPosition(this->entityType.dir); //Get next position using current direction
		


	if (this->map->isWall(tmpPosition)) //check if new position is a wall
	{
			
	}
	else //set new position
	{
		this->setPosition(tmpPosition);// set new position
	}
}


bool MovableEntity::setDirection (Direction dir)
{
	Position tmpNextPosition = this->getNextPosition(dir); //get next position with the new direction

	if (this->map->isWall(tmpNextPosition)) //check if new position is wall
	{
		return false;
	}
	else //set new direction
	{
		this->entityType.dir = dir;
		return true;
	}
		
		
}


Direction MovableEntity::getDirection()
{
	return this->entityType.dir;//return current direction
}
	

Position MovableEntity::getNextPosition( Direction curDir)
{
	Position curPos = this->getPosition();
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


bool MovableEntity::hasCollided(Entity *tmpEntity)
{
	if (tmpEntity == NULL) //check if pointer is null pointer
	{
		return false;
	}
	if (this->getPosition() == tmpEntity->getPosition()) //if current position is same is position of tmpEntity
	{
		return true; 
	}
	else //if current position is not the same
	{
		return false;
	}
}

