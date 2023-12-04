#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        bool loseFlag;

        int score;

        int boardSizeX;
        int boardSizeY;

        objPosArrayList* foodList;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        //destructor
        ~GameMechs();
        
        bool getExitFlagStatus();
        bool getLoseFlagStatus();
        int getScore();

        void incrementScore();
        void setExitTrue();
        void setLoseTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();
      
        void generateFood(objPosArrayList *snakeBody);
        void getFoodInfo(objPosArrayList &returnList);
};

#endif