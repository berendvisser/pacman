#pragma once

#include "Eatable.h"
#include <cstdlib>
#include <ctime>

class Fruit: public Eatable
{
public:
	/*Constructor*/
	Fruit(Board* tmpBoard);

	/*Deconstructor*/
	~Fruit();

	/*Function sets position of fruit to random non wall position on the map*/
	void setRandomPosition();

private:
	/*gets a random position on the entire map*/
	Position getRandomPosition();

	Board* map;

};

