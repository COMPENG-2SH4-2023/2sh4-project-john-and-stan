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
    score = 1;
    speed = 1;
    foodList = new objPosArrayList();

}

// do you need a destructor?

GameMechs::~GameMechs()
{
    delete foodList;
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


void GameMechs::generateFood(objPosArrayList *snakeBody){
    int randX, randY, randPower, randNum;
    //Use current time as seed for randomness
    srand(time(NULL));

    for(int i = 0; i < foodList->getSize(); i++){
        foodList->removeTail();
    }

    //creates bitvectors to choose nonused x,y coordinates
    int* xBitV = (int*)calloc(boardSizeX-1, sizeof(int));
    int* yBitV = (int*)calloc(boardSizeY-1, sizeof(int));
    
    //block off snake body coordinates
    objPos bodyPart;
    for(int i = 0; i < snakeBody->getSize(); i++){
        snakeBody->getElement(bodyPart,i);
        xBitV[bodyPart.x] = 1;
        yBitV[bodyPart.y] = 1;
    }

    //block off walls
    xBitV[0] = 1;
    xBitV[boardSizeX-2] = 1;

    yBitV[0] = 1;
    yBitV[boardSizeY-2] = 1;
    
    objPos food;
    //generates 5 pieces of Food
    
    //chooses to add 1 or 2 powerups
    randNum = rand()%2;

    for(int i = 0; i < 5 - randNum; i++){

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
        //adds it to food list
        food.setObjPos(randX,randY,'!');
        foodList->insertHead(food);
        xBitV[randX] = 1;
        yBitV[randY] = 1;
        //only runs powerup generation in last loop

    }    

    for(int j = 0; j < randNum; j++){
        //chooses which powerup to add
        randPower = rand() % 3;
        if(randPower == 1){
            //cuts the snake body in half
            food.setObjPos(randX,randY, '%');

        }else if(randPower== 2){
            //Power gives snake 10 more points and length
            food.setObjPos(randX,randY, '$');

        }else{
            //power increases snake speed
            food.setObjPos(randX,randY, '>');
        }

        //blocks off coordinates of food so new food is not generated in the same spot
        xBitV[randX] = 1;
        yBitV[randY] = 1; 

        //adds it to food list
        foodList->insertTail(food);
    }

        

    free(xBitV);
    free(yBitV);
    
}

void GameMechs::getFoodInfo(objPosArrayList &returnList){
    objPos food;
    for(int i = 0; i < foodList->getSize();i++){
        foodList->getElement(food,i);
        returnList.insertTail(food);
    }
    
}


bool GameMechs::isFoodPos(int x, int y){
    
    objPos food;
    for(int i =0; i < foodList->getSize(); i++){
        foodList->getElement(food,i);

        if(food.x == x && food.y == y){
            return true;
        }
    }

    return false;
}

float GameMechs::getSpeed(){
    return speed;
}
void GameMechs::setSpeed(float newSpeed){
    speed = newSpeed;
}