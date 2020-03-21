#pragma once
#include "Entity.h"

class Eatable : virtual public  Entity
{
public:
	/*Constructor*/
	Eatable(Type EatableType) :Entity(EatableType)
	{
		this->scoreOnCollision = 1; //standard score on collison
	}

	/*Deconstructor*/
	~Eatable()
	{

	}

	/*sets score on collision with this object*/
	void setScoreOnCollision(int newScore)
	{
		scoreOnCollision = newScore; //set new score
	}

	/*Returns score when collided with*/
	int getScoreOncollision()
	{
		return scoreOnCollision; 
	}

private:
	int scoreOnCollision;


};