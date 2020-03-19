#pragma once

#include<GameObjectStruct.h>
#include "Board.h"



class Entity 
{
public:
	Entity(Type entityType, Board *tmpBoard) 
	{
		this->entityType.type = entityType;
		this->entityType.x = 0;
		this->entityType.y = 0;
		this->entityType.dir = UP;
		this->map = tmpBoard;
	}
	

	~Entity() 
	{
	}
	
	Position getPosition()
	{
		Position tmpPosition;
		tmpPosition.x = this->entityType.x;
		tmpPosition.y = this->entityType.y;
		return tmpPosition;

	}

	void setPosition(Position tmpPosition)
	{
		this->entityType.x = tmpPosition.x;
		this->entityType.y = tmpPosition.y;
	}

	GameObjectStruct getEntityType() {
		return entityType;
	}

protected:
	Board* map;
	GameObjectStruct entityType;
private:
	Position posEntity;
};
