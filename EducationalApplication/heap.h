#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "plant.h"

class Heap
{
public:
    Heap();
    std::vector<Plant*> plants;

public slots:
    void updateHeapPlants();
};

#endif // HEAP_H
