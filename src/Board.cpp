/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#include"Board.h"

Board::Board()
{
    //load map
    this->map = { {
    #include "board.def"
        } };

    //set size of board
    this->sizeBoardY = map.size();
    this->sizeBoardX = map[1].size();
}

Board::~Board(){}

std::vector<std::vector<int>> Board::getBoard()
{
    return this->map;
}


bool Board::isWall(Position tmpPosition)
{
    //check if called value is within bounds
    if (tmpPosition.x < sizeBoardX && tmpPosition.y < sizeBoardY) {

        //check if wall exists
        if (map[tmpPosition.y][tmpPosition.x])
        {
            return true; //return true if wall found
        }
        else
        {
            return false; //return false if no wall found
        }
    }
    else
    {
        return true; //default to wall found
    }

}

int Board::getBoardSizeX()
{
    return this->sizeBoardX;
}


int Board::getBoardSizeY()
{
    return this->sizeBoardY;
}


