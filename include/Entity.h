#pragma once

#include<GameObjectStruct.h>

struct Position 
{
	unsigned x;
	unsigned y;	
};

class Entity 
{
public:
	Entity(Type entityType) 
	{
		this->entityType.type = entityType;
		this->entityType.x = 0;
		this->entityType.y = 0;
		this->entityType.dir = UP;
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

	void setPosition(int x, int y)
	{
		this->entityType.x = x;
		this->entityType.y = y;
	}

	GameObjectStruct getEntityType() {
		return entityType;
	}

private:
	Position posEntity;
	GameObjectStruct entityType;
};
