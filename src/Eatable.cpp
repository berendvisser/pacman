/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once
#include "Eatable.h"

/*Default constructor*/
Eatable::Eatable(){}

/*constructor*/
Eatable::Eatable(Type EatableType) :Entity(EatableType)
{
	this->scoreOnCollision = 1; //standard score on collison
}

/*Deconstructor*/
Eatable::~Eatable()
{

}

/*sets score on collision with this object*/
void Eatable::setScoreOnCollision(int newScore)
{
	this->scoreOnCollision = newScore; //set new score
}

/*Returns score when collided with*/
int Eatable::getScoreOncollision()
{
	return this->scoreOnCollision; 
}
