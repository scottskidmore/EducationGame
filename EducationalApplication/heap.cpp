#include "heap.h"

Heap::Heap() {}

void Heap::updateHeapPlants()
{
    for (auto pair : plantMap) {
        pair.second->updateHeapGrowth();
    }
}
