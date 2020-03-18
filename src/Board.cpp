#include "Board.h"

Board::Board()
{
    //load map
    this->map = {{
    #include "board.def"
        }};

    //set size of board
    this->sizeBoardY = map.size();
    this->sizeBoardX = map[1].size();
}

Board::~Board()
{
}

std::vector<std::vector<int>> Board::getBoard()
{
    return this->map;
}

bool Board::isWall(unsigned x, unsigned y) 
{
    //check if called value is within bounds
    if (x <= sizeBoardX && y < sizeBoardY) {
        
        //check if wall exists
        if (map[y][x]) 
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


