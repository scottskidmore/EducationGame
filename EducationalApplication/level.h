#ifndef LEVEL_H
#define LEVEL_H

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the level class. A level stores information for each level.
Citations:
*/
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
    ///
    /// \brief roundNumber
    ///
    int roundNumber;
    ///
    /// \brief targetScore
    ///
    int targetScore;
    ///
    /// \brief ramAmount
    ///
    int ramAmount;
    ///
    /// \brief individualStackPlantLimit - limit amount of stack plants
    ///
    int individualStackPlantLimit;
    ///
    /// \brief individualHeapPlantLimit - limit amoiunt of heap plants
    ///
    int individualHeapPlantLimit;
};

#endif // LEVEL_H
