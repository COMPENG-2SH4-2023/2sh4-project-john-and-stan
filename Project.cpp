#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

Player* playerPtr = nullptr;
GameMechs* mechs = nullptr; 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();
    
    while(mechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    mechs = new GameMechs(30,15);
    playerPtr = new Player(mechs);
    
    //Generate first food
    objPos playerPosition;
    playerPtr->getPlayerPos(playerPosition);
    mechs->generateFood(playerPosition);

    
    
    
    
}

void GetInput(void)
{
   if(MacUILib_hasChar()){
            mechs->setInput(MacUILib_getChar());
            
    }else{
            mechs->setInput(0);
    }
}

void RunLogic(void)
{
    //get player position
    objPos playerPosition;
    playerPtr->getPlayerPos(playerPosition);
    //get Food Position
    objPos foodPosition;
    mechs->getFoodInfo(foodPosition);

    switch(mechs->getInput()){
        case ' ':
            
            break;            
    }

    if(playerPosition.isPosEqual(foodPosition.x,foodPosition.y)){
        mechs->incrementScore();
        mechs->generateFood(playerPosition);
    }

    playerPtr->updatePlayerDir();
    playerPtr->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos head;
    objPos foodPosition;
    
    playerPtr->getPlayerPos(head);
    
    mechs->getFoodInfo(foodPosition);


    // Draw the player at its position on the board
    for (int y = 0; y < mechs->getBoardSizeY(); y++) {
        for (int x = 0; x < mechs->getBoardSizeX(); x++) {
            
            if (x == head.x && y == head.y) {
                // Draw the player symbol
                cout << head.getSymbol();
            } else if(x == foodPosition.x && y == foodPosition.y){
                cout<< foodPosition.getSymbol();

            }else if (x == 0 || x == mechs->getBoardSizeX() - 1 || y == 0 || y == mechs->getBoardSizeY() - 1) {
                // Draw border
                cout << "#";
            } else {
                // Empty space
                cout << " ";
            }
        }
        // Move to the next line after each row
        cout << endl;
    }
    //score
    cout << "Your Score is: " << mechs->getScore() << endl;
    
    //debug messages
    cout <<"The Head X,Y is: " << head.x << ", "<< head.y <<endl;
} 



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    
    delete mechs;
    delete playerPtr;
    MacUILib_uninit();
}
