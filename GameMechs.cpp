#include "GameMechs.h"

//Default Values
GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    
    exitFlag = false;
    loseFlag = false;
    score = 0;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    food.symbol = '!';


}

// do you need a destructor?

GameMechs::~GameMechs()
{

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

int GameMechs::getScore(){
    return score;
}

void GameMechs::incrementScore(){
    score++;
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


void GameMechs::generateFood(objPosArrayList snakeBody){
    int randX, randY;
    //Use current time as seed for randomness
    srand(time(NULL));

    //creates bitvectors to choose nonused x,y coordinates
    int* xBitV = (int*)calloc(boardSizeX-1, sizeof(int));
    int* yBitV = (int*)calloc(boardSizeY-1, sizeof(int));
    
    //block off snake body coordinates

    

    //block off walls
    xBitV[0] = 1;
    xBitV[boardSizeX-2] = 1;

    yBitV[0] = 1;
    yBitV[boardSizeY-2] = 1;

    
    //loops till it chooses non used x
    while(1){
        
        randX = rand() % (boardSizeX-2);
        if(xBitV[randX] == 0){
            xBitV[randX] = 1;
            break;
        }
    }
    //loops till it chooses non used y
    while(1){
        randY = rand() % (boardSizeY-2);
        if(yBitV[randY] == 0){
            yBitV[randY] = 1;
            break;
        }
    }

    food.x = randX;
    food.y = randY;

    free(xBitV);
    free(yBitV);
    
}

void GameMechs::getFoodInfo(objPos &returnPos){
    returnPos.setObjPos(food);
    
}