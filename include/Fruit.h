#pragma once

#include "Eatable.h"
#include <cstdlib>
#include <ctime>

class Fruit: public Eatable
{
public:
	Fruit(Board * tmpBoard)
	{
		std::srand(std::time(NULL));

		this->map = tmpBoard;
		this->entityType.type = static_cast<Type>(7+ (std::rand()%6));
		this->setRandomPosition();
		
	}
	/*Deconstructor*/
	~Fruit(){}

	void setRandomPosition()
	{
		Position randomPosition = getRandomPosition();
		while (map->isWall(randomPosition))
		{
			randomPosition = getRandomPosition();
		}
		this->setPosition(randomPosition);

	}



private:
	Position getRandomPosition()
	{
		int boardSizeX = map->getBoardSizeX();
		int boardSizeY = map->getBoardSizeY();
		
		return { std::rand() % boardSizeX,	std::rand() % boardSizeY };

	}
	Board* map;

};

