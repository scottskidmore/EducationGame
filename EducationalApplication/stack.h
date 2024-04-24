#ifndef STACK_H
#define STACK_H

#include <vector>
#include "plant.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the Stack class. The Stack stores plants.

Citations:
*/
class Stack
{
public:
    /// \brief Constructor for Stack
    Stack();

    /// \brief Vector storing Plant pointers
    std::vector<Plant*> plants;

    /// \brief Map storing Plant pointers indexed by QString
    std::map<QString, Plant*> plantMap; // this should be the one we use
};

#endif // STACK_H
