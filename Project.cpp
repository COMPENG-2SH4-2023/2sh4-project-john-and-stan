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
    
    
    
    
    MacUILib_Delay(DELAY_CONST*50); // 0.1s delay

    
    
    
    
}

void GetInput(void)
{
   // Checking to see if there has been an input, if there was an input, set it
   if(MacUILib_hasChar()){
            mechs->setInput(MacUILib_getChar());
            
    }else{
            mechs->setInput(0); // If no input detected set input to 0
    }
}

void RunLogic(void)
{
    
    playerPtr->updatePlayerDir();
    playerPtr->movePlayer();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();
    objPos head;
    objPos foodPosition;
    
    
    mechs->getFoodInfo(foodPosition);


    // Draw the player at its position on the board
    for (int y = 0; y < mechs->getBoardSizeY(); y++) {
        for (int x = 0; x < mechs->getBoardSizeX(); x++) {
            
            if (playerPtr->isPlayerPos(x,y)) {
                
                // Draw the player symbol
                cout << "*";
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
    
} 



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    if(mechs->getLoseFlagStatus()){
        cout << "You have lost! Better luck next time :)" << endl;
    }else{
        cout<< "You have quit!" <<endl;
    }

    delete mechs;
    delete playerPtr;
    MacUILib_uninit();
}
