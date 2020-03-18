#include "Entity.h"




Entity::Entity(Type entityType)
{
	this->entityType.type = entityType;
	this->entityType.x = 0;
	this->entityType.y = 0;
	this->entityType.dir = UP;
}

Entity::~Entity()
{

}

GameObjectStruct Entity::getGameObjectStruct()
{
	return entityType;
}
