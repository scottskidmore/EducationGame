#include "heap.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Implementation file for heap class. The heap handles all the plants that are planted on the heap.
Citations:
*/
Heap::Heap() {}
void Heap::updateHeapPlants()
{
    for (auto pair : plantMap) {
        pair.second->updateHeapGrowth();
    }
}
