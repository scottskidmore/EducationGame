#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:
    Level(int round,int target, int ram, int stackLimit, int heapLimit);
    int roundNumber;
    int targetScore;
    int ramAmount;

    int individualStackPlantLimit;
    int individualHeapPlantLimit;
};

#endif // LEVEL_H
