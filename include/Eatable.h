#pragma once
#include "Entity.h"

class Eatable : public Entity
{
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

	int getScoreOncollision()
	{
		return scoreOnCollision;
	}

private:
	int scoreOnCollision;


};