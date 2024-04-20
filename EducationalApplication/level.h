#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:
    Level(int round,int target, int ram);
    int roundNumber;
    int targetScore;
    int ramAmount;
};

#endif // LEVEL_H
