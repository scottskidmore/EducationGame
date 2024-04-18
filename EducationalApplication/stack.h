#ifndef STACK_H
#define STACK_H

#include <vector>
#include "plant.h"

class Stack
{
public:
    Stack();
    std::vector<Plant*> plants;
    std::map<QString, Plant*> plantMap;
};

#endif // STACK_H
