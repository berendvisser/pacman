#pragma once
#include "Entity.h"

class MovableEntity: virtual public  Entity
{
public:
	/*Constructor takes entity type and board as parameters*/
	MovableEntity(Board* tmpBoard, Type EntityType = PACMAN);

	/*Deconstructor*/
	~MovableEntity();

	/*Moves entity in current direction*/
	void moveEntity();

	/*Attempts to set direction of movable entity in new direction, returns true if succesfull*/
	bool setDirection(Direction dir);

	/*Return current direction*/
	Direction getDirection();
	
	/*Get next position*/
	Position getNextPosition(Direction curDir);

	/*Checks if current entity has a collision with another entity*/
	bool hasCollided(Entity* tmpEntity);


protected:
	Board* map;
};
