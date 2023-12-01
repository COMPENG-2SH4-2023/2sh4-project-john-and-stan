#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

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
    mechs = new GameMechs(15,30);
    
    
    
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
    if(mechs->getInput() == 'a'){
        mechs->setExitTrue();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    for(int y = 0; y <= 15; y++ ){
        for(int x = 0; x <= 30; x++){
            
            if (x == 0 || x == 30 || y ==0 || y == 15)
            {
                //Draw Boarder
                cout << "#";
            }else{
                cout << " ";
            }
        }
        printf("\n");
    }
    
    printf("\n");
    cout << "The xSize is "<< mechs->getBoardSizeX();

    

    } 



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete mechs;
    MacUILib_uninit();
}
