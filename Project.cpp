#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

#define DELAY_CONST 100000
#define xSize 30
#define ySize 15
bool exitFlag;

const objPos at;
const objPos star;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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
    //boarder testing elements
    objPos at = objPos(14,6,'@');
    objPos star = objPos(8,9,'*');
    
    
    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    objPos test = objPos(at);

    for(int y = 0; y <= ySize; y++ ){
        for(int x = 0; x <= xSize; x++){
            
            if (x == 0 || x == xSize || y ==0 || y == ySize)
            {
                cout << "#";
            }
            else if (x > 2 && y == 2 )
            {
                cout << test.getSymbol();
            }
            
            else{
                cout << " ";
            }
        }
        printf("\n");
    }

    

    } 



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
