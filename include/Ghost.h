/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once

#include "MovableEntity.h"
#include "Eatable.h"
#include <cstdlib>
#include <ctime>


class Ghost : public MovableEntity, public Eatable
{
public:
	/*Constructor*/
	Ghost(Type ghostType, Board* tmpBoard);

	/*Deconstructor*/
	~Ghost();

	/*Set new direction for ghost*/
	void setNewDirection();

	/*Make ghost scared ticks*/
	void setScared(bool scared);

	/*check if ghost is currently scared*/
	bool getGhostScared();
	


protected:

	/*Update scared state*/
	void updateScaredState();

	/*Return opposite direction of Ghost*/
	Direction getOppositeDirection();

private:

	/*sets new random position*/
	void setRandomDirection();

	bool isScared; //state of whether the ghost is scared
	unsigned ticksLeftScared; //How many game ticks the ghost will be scared
	Type normalType; //What the type of the ghost is when it is not scared(ie inky)
	

};