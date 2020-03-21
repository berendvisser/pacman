#pragma once

#include "MovableEntity.h"
class Pacman : public MovableEntity
{
public:
	Pacman(Board* tmpBoard) :MovableEntity(tmpBoard)
	{
		this->entityType.type = PACMAN;
	}
	~Pacman(){}
};
