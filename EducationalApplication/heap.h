#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "plant.h"

class Heap
{
public:
    Heap();
    std::vector<Plant*> plants;
    std::map<QString, Plant*> plantMap; // this should be the one we use

public slots:

    /// \brief updateHeapPlants - this will update the growth of all plants on the heap, and they will change their image if needed.
    void updateHeapPlants();
};

#endif // HEAP_H
