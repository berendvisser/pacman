/*
 *  Created on: March, 2020
 *      Author: Berend Visser
 *       Group: 30
 */
#pragma once
#include<vector>
/*A struct which defines the position of a item*/
struct Position
{
    int x; //X position
    int y; //Y position
    
    bool operator==(const Position& other) const //overload == operator
    {
        return x == other.x && y == other.y;
    }
    
};

/*This class defines how the board looks*/
class Board
{
    //function and variables that are publically available
public:

    /*Constructor will loads board.def file in map*/
    Board();

    /*Deconstructor*/
    ~Board();

    /*Return map*/
    std::vector<std::vector<int>> getBoard();

    /*Checks if a certain position on the map is all wall or not, defaults to true if position is outside of map*/
    bool isWall(Position tmpPosition);

    /*Return size of the map in x direction*/
    unsigned getBoardSizeX();
    
    /*Return size of the map in y direction*/
    unsigned getBoardSizeY();

private:
    
    unsigned sizeBoardX; //Board size x direction
    unsigned sizeBoardY; //Board size y direction

    std::vector<std::vector<int>> map; //map in vector or vectors
};
