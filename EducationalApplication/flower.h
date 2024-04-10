#ifndef FLOWER_H
#define FLOWER_H

#include "Plant.h" // Include the header file of the base class

class Flower : public Plant
{
public:
    Flower();
    std::string displayCode() override;
};

#endif // FLOWER_H
