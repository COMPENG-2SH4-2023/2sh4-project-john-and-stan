#include "Player.h"
#include <iostream>
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // Initialize player position 
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
    // return the reference to the playerPos arrray list
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

            // Add more key processing here
            case 'w':
                if (myDir != DOWN) {
                    myDir = UP;
                }
                break;

            case 's':
                if (myDir != UP) {
                    myDir = DOWN;
                }
                break;

            case 'a':
                if (myDir != RIGHT) {
                    myDir = LEFT;
                }
                break;

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
    
    
    switch (myDir) {
        case UP:
            head.setObjPos(head.x,head.y - 1, '*');
            break;

        case DOWN:
            
            head.setObjPos(head.x,head.y + 1, '*');
            break;

        case LEFT:
            head.setObjPos(head.x - 1, head.y, '*');
            break;

        case RIGHT:
            head.setObjPos(head.x + 1, head.y, '*');
            break;

        default:
            // If the state is STOP, do nothing
            break;
    }




    // PPA3 Boarder wraparound logic
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    if (head.x <= 0) {
        head.setObjPos(boardSizeX - 2, head.y, '*');
    } else if (head.x >= boardSizeX - 1) {
        head.setObjPos(1, head.y, '*');
    }

    if (head.y <= 0) {
        head.setObjPos(head.x, boardSizeY - 2, '*');
    } else if (head.y >= boardSizeY - 1) {
        head.setObjPos(head.x, 1, '*');
    }
    
    if(checkSelfCollision()){
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseTrue();
    }
    
    if(checkFoodConsumption()){
        mainGameMechsRef->incrementScore();
        increasePlayerLength();
        mainGameMechsRef->generateFood(playerPosList);
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

bool Player::checkFoodConsumption(){
    objPos head;
    objPos food;
    
    playerPosList->getHeadElement(head);
    mainGameMechsRef->getFoodInfo(food);

    if(head.x == food.x && head.y == food.y){
        return 1;
    }


    return 0;
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
            cout <<"Collision Detected!"<<"\n";
            cout <<"The head coordinates are: " <<head.x << ", " << head.y <<"\n";
            cout <<"It collided with bodyPart " << i<< " and its coordinates are: " <<bodyPart.x << ", " <<bodyPart.y<<"\n";
            return true;
        }
    }
    return false;
}