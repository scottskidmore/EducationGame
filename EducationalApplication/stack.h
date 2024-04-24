#ifndef STACK_H
#define STACK_H

#include <vector>
#include "plant.h"

/// \brief Stack - manages collections of Plant pointers
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
