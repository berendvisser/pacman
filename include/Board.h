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

    /*Constructure will loads board.def file in map*/
    Board()
    {
        //load map
        this->map = { {
        #include "board.def"
            } };

        //set size of board
        this->sizeBoardY = map.size();
        this->sizeBoardX = map[1].size();
    }

    /*Deconstructor*/
    ~Board(){}

    /*Return map*/
    std::vector<std::vector<int>> getBoard()
    {
        return this->map;
    }

    /*Checks if a certain position on the map is all wall or not, defaults to true if position is outside of map*/
    bool isWall(Position tmpPosition)
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

    /*Return size of the map in x direction*/
    unsigned getBoardSizeX()
    {
        return this->sizeBoardX;
    }
    /*Return size of the map in y direction*/
    unsigned getBoardSizeY()
    {
        return this->sizeBoardY;
    }


private:
    
    unsigned sizeBoardX; //Board size x direction
    unsigned sizeBoardY; //Board size y direction

    std::vector<std::vector<int>> map; //map in vector or vectors
};
