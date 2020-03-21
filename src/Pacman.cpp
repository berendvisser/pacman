#pragma once

#include "MovableEntity.h"


class Pacman : public MovableEntity
{
public:
	Pacman(Board* tmpBoard) :MovableEntity(tmpBoard),Entity()
	{
		this->entityType.type = PACMAN; //initial type
        this->score = 0;//initial score
        this->lives = 5;//initial lives
	}
	~Pacman(){}

    void checkCollision(std::vector<Eatable*>& tmpEatableList, std::vector<Ghost*> &tmpGhosts)
    {
        for (int i = 0; i < tmpEatableList.size(); i++)
        {
            if (this->hasCollided(tmpEatableList[i]))
            {
                int scoreOnCollion = tmpEatableList[i]->getScoreOncollision();
                if (scoreOnCollion > 0)
                {
                    this->increaseScore(tmpEatableList[i]->getScoreOncollision());

                    delete tmpEatableList[i];
                    tmpEatableList.erase(tmpEatableList.begin() + i); 
                }

                else if (scoreOnCollion == 0)
                {
                    delete tmpEatableList[i]; 
                    tmpEatableList.erase(tmpEatableList.begin() + i); 

                    for (int j = 0; j < tmpGhosts.size(); j++)
                    {
                        tmpGhosts[j]->setScared(true);
                    }
                }

            }

        }

        for (int i = 0; i < tmpGhosts.size(); i++)
        {
            if (this->hasCollided(tmpGhosts[i]))
            {
                if (tmpGhosts[i]->getGhostScared())
                {
                    this->increaseScore(tmpGhosts[i]->getScoreOncollision());
                    tmpGhosts[i]->setPosition({ 12 + i,13 });
                    tmpGhosts[i]->setScared(false);
                }
                else
                {
                    this->loseLive();
                    this->setPosition({ 1,1 });
                    for (int j = 0; j < tmpGhosts.size(); j++)
                    {
                        tmpGhosts[j]->setPosition({ 12 + j,13 });
                        tmpGhosts[j]->setScared(false);
                    }
                }
            }
        }
    }

    unsigned getLives()
    {
        return this->lives;
    }

    void increaseScore(int points)
    {
        this->score += points;
    }

    int getScore()
    {
        return this->score;
    }

    void loseLive()
    {
        this->lives--;
    }

private:
    int score;
    unsigned lives;
};
