#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        void getPlayerPosHead(objPos &returnPos); // Upgrade this in iteration 3.
        objPosArrayList getPlayerPosList(); // Upgrade this in iteration 3.
        bool isPlayerPos(int x, int y);
        


        void updatePlayerDir();
        void movePlayer();

        
        void increasePlayerLength();
        int checkFoodConsumption();

        bool checkSelfCollision();


    private:
       
        
        objPosArrayList* playerPosList;
        enum Dir myDir;
        

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif