/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the Level class. This class store information about specific levels.
*/
#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:
    ///
    /// \brief Level Constructor.
    /// \param round Current round in this level.
    /// \param target The target score for the level.
    /// \param ram How much RAM is given to the player.
    /// \param stackLimit Specifies the plant limit in the stack.
    /// \param heapLimit Specifies the plant limit in the heap.
    ///
    Level(int round,int target, int ram, int stackLimit, int heapLimit);
    int roundNumber;
    int targetScore;
    int ramAmount;

    int individualStackPlantLimit;
    int individualHeapPlantLimit;
};

#endif // LEVEL_H
