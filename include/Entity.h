/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once

#include<GameObjectStruct.h>
#include "Board.h"


/*Base class for object on the map*/
class Entity 
{
public:
	/*Constructor of map, takes as argument entityType like pacman or fruit and needs a pointer to the board on which the object will be placed*/
	
	/*default constructor*/
	Entity();
	
	/*constructor with type*/
	Entity(Type entityType);
	
	/*Deconstructor of Entity*/
	~Entity();

	/*Return position of entity on the map*/
	Position getPosition();


	/*Get the objectstruct*/
	GameObjectStruct getEntityType();

	/*Set position of entity*/
	void setPosition(Position tmpPosition);


// members can be accessed by subclasses
protected:
	GameObjectStruct entityType; //gameobject type of entity


//only accessable inside of class
private:
	Position posEntity; //Position 
};
