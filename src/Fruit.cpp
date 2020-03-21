/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once
#include "Fruit.h"


Fruit::Fruit(Board * tmpBoard)
{
	std::srand(std::time(NULL)); //Create seed for random function
	this->map = tmpBoard; //set initialize pointer of map
	this->entityType.type = static_cast<Type>(7+ (std::rand()%6)); //Select one of 6 fruit types by random
	this->setRandomPosition(); //Set position of fruit to random spot on the map
	this->setScoreOnCollision(50); //set score of the fruit
		
}


Fruit::~Fruit()
{
}

void Fruit::setRandomPosition()
{
	Position randomPosition = getRandomPosition(); //get random position on map

	while (map->isWall(randomPosition)) //check if random position is wall
	{
		randomPosition = getRandomPosition(); //get new random position
	}
	this->setPosition(randomPosition); //set position of fruit

}

Position Fruit::getRandomPosition()
{
	int boardSizeX = map->getBoardSizeX(); //get size of board
	int boardSizeY = map->getBoardSizeY(); //""
		
	return { std::rand() % boardSizeX,	std::rand() % boardSizeY };//return random position on map

}


