#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // Initialize player position 
    int initialX = thisGMRef->getBoardSizeX() / 2;
    int initialY = thisGMRef->getBoardSizeY() / 2;
    playerPos.setObjPos(initialX, initialY, '*');

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos);
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
    // PPA3 Finite State Machine logic
    switch (myDir) {
        case UP:
            playerPos.setObjPos(playerPos.x, playerPos.y - 1, '*');
            break;

        case DOWN:
            playerPos.setObjPos(playerPos.x, playerPos.y + 1, '*');
            break;

        case LEFT:
            playerPos.setObjPos(playerPos.x - 1, playerPos.y, '*');
            break;

        case RIGHT:
            playerPos.setObjPos(playerPos.x + 1, playerPos.y, '*');
            break;

        default:
            // If the state is STOP, do nothing
            break;
    }

    // PPA3 Boarder wraparound logic
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    if (playerPos.x <= 0) {
        playerPos.setObjPos(boardSizeX - 2, playerPos.y, '*');
    } else if (playerPos.x >= boardSizeX - 1) {
        playerPos.setObjPos(1, playerPos.y, '*');
    }

    if (playerPos.y <= 0) {
        playerPos.setObjPos(playerPos.x, boardSizeY - 2, '*');
    } else if (playerPos.y >= boardSizeY - 1) {
        playerPos.setObjPos(playerPos.x, 1, '*');
    }
}

