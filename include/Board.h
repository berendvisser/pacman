#pragma once
#include<vector>


class Board
{
    //function and variables that are publically available
public:

    Board();

    ~Board();

    //return map
    std::vector<std::vector<int>> getBoard();

    //return if position contains a wall
    bool isWall(unsigned x, unsigned y);

    //sizes of board
    unsigned sizeBoardX;
    unsigned sizeBoardY;

private:
    //map
    std::vector<std::vector<int>> map;
};
