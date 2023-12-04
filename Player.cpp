#include "Player.h"
#include <iostream>
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // Initialize player position to middle of the board
    int initialX = thisGMRef->getBoardSizeX() / 2;
    int initialY = thisGMRef->getBoardSizeY() / 2;
    playerPosList = new objPosArrayList();
    objPos startingState;
    
    startingState.setObjPos(initialX,initialY,'*');
    playerPosList->insertHead(startingState);

    mainGameMechsRef->generateFood(playerPosList);


}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

void Player::getPlayerPosHead(objPos &returnPos)
{
    //changes passed objPos to head element
    playerPosList->getHeadElement(returnPos);
}

objPosArrayList Player::getPlayerPosList(){
    return *playerPosList;
}

bool Player::isPlayerPos(int x, int y){
    
    objPos bodyPart;
    for(int i =0; i < playerPosList->getSize(); i++){
        playerPosList->getElement(bodyPart,i);

        if(bodyPart.x == x && bodyPart.y == y){
            return true;
        }
    }

    return false;
}
void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    // This method should contain the player FSM
    // Obtain the most current input from the gameMechanics reference
    char input = mainGameMechsRef->getInput();

    if (input != 0) {  // If not a null character
        switch (input) {
            case ' ':  // Exit
                mainGameMechsRef->setExitTrue();
                break;

            // If w is pressed and player isn't moving down, move up
            case 'w':
                if (myDir != DOWN) {
                    myDir = UP;
                }
                break;

            // If s is pressed and player isn't moving up, move down
            case 's':
                if (myDir != UP) {
                    myDir = DOWN;
                }
                break;

            // If a is pressed and player isn't moving right, move left
            case 'a':
                if (myDir != RIGHT) {
                    myDir = LEFT;
                }
                break;

            // If d is pressed and player isn't moving left, move right
            case 'd':
                if (myDir != LEFT) {
                    myDir = RIGHT;
                }
                break;

            default:
                break;
        }

        // Clear the input buffer via gameMechanics reference
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    //gets head position
    objPos head;
    playerPosList->getHeadElement(head);
    
    //Moves player based on myDir
    switch (myDir) {
        //y-value is decremented and x stays the same when moving up
        case UP:
            head.setObjPos(head.x,head.y - 1, '*');
            break;

        //y-value is incremented and x stays the same when moving down
        case DOWN:
            head.setObjPos(head.x,head.y + 1, '*');
            break;

        //x-value is decremented and y stays the same when moving left
        case LEFT:
            head.setObjPos(head.x - 1, head.y, '*');
            break;

        //x-value is incremented and y stays the same when moving right
        case RIGHT:
            head.setObjPos(head.x + 1, head.y, '*');
            break;

        default:
            // If the state is STOP, do nothing
            break;
    }




    // PPA3 Boarder wraparound logic
    // Getting size of the board
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    // X-Direction Wraparound
    // If the player reaches the left boarder, position gets set to the right side of the board without going into the boarder
    if (head.x <= 0) {
        head.setObjPos(boardSizeX - 2, head.y, '*');
    } 
    // If the player reaches the right boarder, position gets set to the left side of the board without going into the boarder
    else if (head.x >= boardSizeX - 1) {
        head.setObjPos(1, head.y, '*');
    }

    // Y-Direction Wraparound
    // If the player reaches the top boarder, position gets set to the bottom of the board without going into the boarder
    if (head.y <= 0) {
        head.setObjPos(head.x, boardSizeY - 2, '*');
    } 
    // If the player reaches the bottom boarder, position gets set to the top of the board without going into the boarder
    else if (head.y >= boardSizeY - 1) {
        head.setObjPos(head.x, 1, '*');
    }
    
    if(checkSelfCollision()){
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseTrue();
    }

    int foodType = checkFoodConsumption();
    if(foodType > -1){
        if(foodType == 0){
            mainGameMechsRef->incrementScore();
            increasePlayerLength();
            mainGameMechsRef->generateFood(playerPosList);
        }else if(foodType == 1){
            //removes half the snake's body
            for(int i = 0; i < (playerPosList->getSize() / 2); i++){
                playerPosList->removeTail();
            }
        }else if(foodType == 2){
            
        }else{

        }
    }
    playerPosList->insertHead(head);
    playerPosList->removeTail();
    

    

}

void Player::increasePlayerLength(){
    objPos newTail;
    playerPosList->getTailElement(newTail);

    switch (myDir) {
        case DOWN:
            newTail.setObjPos(newTail.x,newTail.y - 1, '*');
            break;

        case UP:
            newTail.setObjPos(newTail.x,newTail.y + 1, '*');
            break;

        case RIGHT:
            newTail.setObjPos(newTail.x - 1, newTail.y, '*');
            break;

        case LEFT:
            newTail.setObjPos(newTail.x + 1, newTail.y, '*');
            break;

        default:
            // If the state is STOP, do nothing
            break;
    }
    playerPosList->insertTail(newTail);
    
}

int Player::checkFoodConsumption(){
    objPos head;
    objPosArrayList foodList;
    objPos food;
    
    playerPosList->getHeadElement(head);
    mainGameMechsRef->getFoodInfo(foodList);

    for(int i = 0; i < foodList.getSize(); i++){
        foodList.getElement(food,i);
        if(head.x == food.x && head.y == food.y){
            //returns between 0-3 depending on food type
            switch (food.symbol)
            {
            case '*':
                return 0;
                break;
            case '%':
                return 1;
                break;
            case '$':
                return 2;
                break;
            case '>':
                return 3;
                break;
            
            default:
                break;
            }
            
        }
    }

    //returns -1 if there is no collision
    return -1;
}

bool Player::checkSelfCollision(){
    objPos head;
    objPos bodyPart;
    if(playerPosList->getSize() < 4){
        //snake head cannot collide with itself with only 3 parts
        //because it can not reverse in the same direction
        return false;
    }

    playerPosList->getHeadElement(head);


    for(int i = 4; i < playerPosList->getSize(); i++){
        playerPosList->getElement(bodyPart,i);
        
        if(head.x == bodyPart.x && head.y == bodyPart.y){
            return true;
        }
    }
    return false;
}