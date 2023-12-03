#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.



objPosArrayList::objPosArrayList()
{
    sizeArray = ARRAY_MAX_CAP;  // Default capacity
    aList = new objPos[sizeArray];
    sizeList = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // Deallocate the heap array
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Shift existing elements to make room for the new element
    for (int i = sizeList - 1; i >= 0; i--) {
        aList[i + 1] = aList[i];
    }

    // Insert the new element at the head
    aList[0] = thisPos;
    //Increment the size of the list
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Insert the new element at the tail
    aList[sizeList] = thisPos;
    sizeList++;
}

void objPosArrayList::removeHead()
{
    if (sizeList > 0) {
        // Shift remaining elements to fill the gap left by the removed head
        for (int i = 0; i < sizeList - 1; i++) {
            aList[i] = aList[i + 1];
        }

        sizeList--;
    }
}

void objPosArrayList::removeTail()
{
    if (sizeList > 0) {
        //Reduce the size to remove the tail element
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (sizeList > 0) {
        returnPos = aList[0]; //Gets the position of the head element
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1]; //Gets the position of the tail element
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < sizeList) {
        returnPos = aList[index]; //Gets the position of the element specified by index
    }
}