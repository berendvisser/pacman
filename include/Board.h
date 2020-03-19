#pragma once
#include<vector>

struct Position
{
    int x;
    int y;
};


class Board
{
    //function and variables that are publically available
public:

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

    ~Board(){}

    //return map
    std::vector<std::vector<int>> getBoard()
    {
        return this->map;
    }

    //return if position contains a wall
    bool isWall(Position tmpPosition)
    {
        //check if called value is within bounds
        if (tmpPosition.x < sizeBoardX && tmpPosition.y < sizeBoardY) {

            //check if wall exists
            if (map[tmpPosition.y][tmpPosition.x])
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }

    }

    //sizes of board
    unsigned getBoardSizeX()
    {
        return this->sizeBoardX;
    }
    unsigned getBoardSizeY()
    {
        return this->sizeBoardY;
    }


private:
    //map
    unsigned sizeBoardX;
    unsigned sizeBoardY;
    std::vector<std::vector<int>> map;
};
