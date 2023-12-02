#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // Initialize player position 
    int initialX = thisGMRef->getBoardSizeX() / 2;
    int initialY = thisGMRef->getBoardSizeY() / 2;
    playerPos.setObjPos(initialX, initialY, '*');
    

    playerPosList = new objPosArrayList();
    objPos startingState;
    startingState.setObjPos(initialX,initialY,'*');
    playerPosList->insertHead(startingState);


}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    playerPosList->getHeadElement(returnPos);
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

    //update body list
    playerPosList->insertHead(head);
    playerPosList->removeTail();

}

