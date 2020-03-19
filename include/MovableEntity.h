#pragma once
#include "Entity.h"

class MovableEntity: public Entity
{
public:
	MovableEntity(Type EntityType, Board* tmpBoard) : Entity(EntityType, tmpBoard) {}

	/*Moves entity in current directio*/
	void moveEntity()
	{
		Position tmpPosition = getNextPosition(this->getPosition(), this->entityType.dir);
		


		if (!this->map->isWall(tmpPosition))
		{
			this->setPosition(tmpPosition);
		}
	}

	void setDirection (Direction dir)
	{
		Position tmpNextPosition = getNextPosition(this->getPosition(), dir);

		if (this->map->isWall(tmpNextPosition))
		{
			
		}
		else
		{
			this->entityType.dir = dir;
		}
		
		
	}

	/*Return current direction*/
	Direction getDirection()
	{
		return this->entityType.dir;
	}

	Position getNextPosition(Position curPos, Direction curDir)
	{
		unsigned boardSizeX = this->map->getBoardSizeX();
		unsigned boardSizeY = this->map->getBoardSizeY();;
		curPos.x += boardSizeX;
		curPos.y += boardSizeY;
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

		curPos.x %= boardSizeX;
		curPos.y %= boardSizeY;

		return curPos;

	}
};
