#pragma once
#include "MovableEntity.h"
#include "Eatable.h"

class Ghost : public MovableEntity, public Eatable
{
public:
	/*Constructor*/
	Ghost(Type ghostType, Board* tmpBoard) :MovableEntity(ghostType, tmpBoard), Eatable(ghostType), Entity(ghostType)
	{
		this->setScoreOnCollision(-200);
	}

	/*Deconstructor*/
	~Ghost(){}

};