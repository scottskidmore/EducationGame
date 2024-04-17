#include "heap.h"

Heap::Heap() {}

void Heap::updateHeapPlants()
{
    for (Plant* p : plants) {
        if (p->onHeap)
            p->updateHeapGrowth();
    }
}
