#include "level.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Implementation file for the level class. A level stores information for each level.
Citations:
*/
Level::Level(int number, int target, int ram, int stackLimit, int heapLimit) {
    roundNumber=number;
    targetScore=target;
    ramAmount = ram;
    individualHeapPlantLimit = heapLimit;
    individualStackPlantLimit = stackLimit;
}
