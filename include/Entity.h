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
	Entity(Type entityType);

	~Entity();
	
	GameObjectStruct getGameObjectStruct();
	

private:
	GameObjectStruct entityType;
	Position posEntity;
	






};
