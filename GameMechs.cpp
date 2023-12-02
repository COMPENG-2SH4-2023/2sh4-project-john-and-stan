#include "GameMechs.h"

GameMechs::GameMechs()
{

}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;


}

// do you need a destructor?

GameMechs::~GameMechs()
{
    boardSizeX = 30
    boardSizeY = 15
    
    exitFlag = false;
    loseFlag = false;
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}
bool GameMechs::getLoseFlagStatus(){
    return loseFlag;
}
char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{  
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}
void GameMechs::setLoseTrue(){
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}


