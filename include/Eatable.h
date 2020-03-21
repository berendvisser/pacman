/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once
#include "Entity.h"

class Eatable : virtual public  Entity 
{
public:
	/*Constructor*/
	Eatable(){}

	/*constructor*/
	Eatable(Type EatableType);

	/*Deconstructor*/
	~Eatable();

	/*sets score on collision with this object*/
	void setScoreOnCollision(int newScore);

	/*Returns score when collided with this object*/
	int getScoreOncollision();

private:
	int scoreOnCollision;


};