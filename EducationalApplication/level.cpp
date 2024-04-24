#include "level.h"

Level::Level(int number, int target, int ram, int stackLimit, int heapLimit) {
    roundNumber=number;
    targetScore=target;
    ramAmount = ram;
    individualHeapPlantLimit = heapLimit;
    individualStackPlantLimit = stackLimit;
}
