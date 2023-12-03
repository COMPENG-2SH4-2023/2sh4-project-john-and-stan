#include "Player.h"

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
    
    

    if(checkFoodConsumption()){
        mainGameMechsRef->incrementScore();
        increasePlayerLength();
        mainGameMechsRef->generateFood(playerPosList);
    }
    playerPosList->insertHead(head);
    playerPosList->removeTail();

    

}

void Player::increasePlayerLength(){
    objPos newHead;
    playerPosList->getHeadElement(newHead);

    switch (myDir) {
        case UP:
            newHead.setObjPos(newHead.x,newHead.y - 1, '*');
            break;

        case DOWN:
            newHead.setObjPos(newHead.x,newHead.y + 1, '*');
            break;

        case LEFT:
            newHead.setObjPos(newHead.x - 1, newHead.y, '*');
            break;

        case RIGHT:
            newHead.setObjPos(newHead.x + 1, newHead.y, '*');
            break;

        default:
            // If the state is STOP, do nothing
            break;
    }
    playerPosList->insertHead(newHead);
    
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