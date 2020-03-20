#pragma once

#include<GameObjectStruct.h>
#include "Board.h"


/*Base class for object on the map*/
class Entity 
{
public:
	/*Constructor of map, takes as argument entityType like pacman or fruit and needs a pointer to the board on which the object will be placed*/
	Entity(Type entityType) 
	{
		this->entityType.type = entityType;	//set type of entity
		this->entityType.x = 0;	//set initial position of entity
		this->entityType.y = 0; // ""
		this->entityType.dir = UP;	//set initial direction	
	}
	
	/*Deconstructor of Entity*/
	~Entity() 
	{
	}

	/*Return position of entity on the map*/
	Position getPosition()
	{
		Position tmpPosition; //return position
		tmpPosition.x = this->entityType.x; //get x postion of entity
		tmpPosition.y = this->entityType.y; //get y position of entity
		return tmpPosition; //return position
	}


	/*Get the objectstruct*/
	GameObjectStruct getEntityType() {
		return entityType; //return entity type
	}

	/*Set position of entity*/
	void setPosition(Position tmpPosition)
	{
		this->entityType.x = tmpPosition.x; //set x position of entity
		this->entityType.y = tmpPosition.y; //set y position of entity
	}



// members can be accessed by subclasses
protected:
	GameObjectStruct entityType; //gameobject type of entity


//only accessable inside of class
private:
	Position posEntity; //Position 
};
