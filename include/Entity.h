#pragma once

#include<GameObjectStruct.h>
#include "Board.h"


/*Base class for object on the map*/
class Entity 
{
public:
	/*Constructor of map, takes as argument entityType like pacman or fruit and needs a pointer to the board on which the object will be placed*/
	Entity(Type entityType, Board *tmpBoard) 
	{
		this->entityType.type = entityType;
		this->entityType.x = 0;
		this->entityType.y = 0;
		this->entityType.dir = UP;
		this->map = tmpBoard;
	}
	
	/*Deconstructor of Entity*/
	~Entity() 
	{
	}

	/*Return position of entity on the map*/
	Position getPosition()
	{
		Position tmpPosition;
		tmpPosition.x = this->entityType.x;
		tmpPosition.y = this->entityType.y;
		return tmpPosition;

	}


	/*Get the objectstruct*/
	GameObjectStruct getEntityType() {
		return entityType;
	}

protected:
	/*Set position of entity*/
	void setPosition(Position tmpPosition)
	{
		this->entityType.x = tmpPosition.x;
		this->entityType.y = tmpPosition.y;
	}

	Board* map;
	GameObjectStruct entityType;
private:
	Position posEntity;
};
