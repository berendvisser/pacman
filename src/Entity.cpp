/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#include "Entity.h"


Entity::Entity()
{
	this->entityType.type = PACMAN; //default type
	this->entityType.x = 0;	//set initial position of entity
	this->entityType.y = 0; // ""
	this->entityType.dir = LEFT;	//set initial direction	
}
	

Entity::Entity(Type entityType)
{
	this->entityType.type = entityType;	//set type of entity
	this->entityType.x = 0;	//set initial position of entity
	this->entityType.y = 0; // ""
	this->entityType.dir = UP;	//set initial direction	
}
	

Entity::~Entity()
{
}

Position Entity::getPosition()
{
	Position tmpPosition; //return position
	tmpPosition.x = this->entityType.x; //get x postion of entity
	tmpPosition.y = this->entityType.y; //get y position of entity
	return tmpPosition; //return position
}



GameObjectStruct Entity::getEntityType() {
	return entityType; //return entity type
}


void Entity::setPosition(Position tmpPosition)
{
	this->entityType.x = tmpPosition.x; //set x position of entity
	this->entityType.y = tmpPosition.y; //set y position of entity
}




