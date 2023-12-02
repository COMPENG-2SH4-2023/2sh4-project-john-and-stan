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
    if(mechs->getInput() == ' '){
        mechs->setExitTrue();
    }
    playerPtr->updatePlayerDir();
    playerPtr->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos playerPosition;
    playerPtr->getPlayerPos(playerPosition);

    // Draw the player at its position on the board
    for (int y = 0; y < mechs->getBoardSizeY(); y++) {
        for (int x = 0; x < mechs->getBoardSizeX(); x++) {
            if (x == playerPosition.x && y == playerPosition.y) {
                // Draw the player symbol
                cout << playerPosition.getSymbol();
            } else if (x == 0 || x == mechs->getBoardSizeX() - 1 || y == 0 || y == mechs->getBoardSizeY() - 1) {
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
    printf("\n");
    cout << "The xSize is "<< mechs->getBoardSizeX();
    printf("\n");
    cout << "The ySize is "<< mechs->getBoardSizeY() << endl; 
    // Debugging: Print input to confirm it is being received
    cout << "Input received: " << mechs->getInput() << endl;

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
