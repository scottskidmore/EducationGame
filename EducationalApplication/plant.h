#ifndef PLANT_H
#define PLANT_H
#include <iostream>
#include <string>

enum class Plants;

class Plant {
public:
    Plant(Plants plantType);
    Plants thisPlant;
    std::string hintCode();
    std::string displayName();
    bool onHeap;
    int cost;
    int reward;
    std::string heapCode;
    std::string stackCode;

private:
    void createCorn();
    void createFlower();
    void createTree();
    std::string toString(Plants p);
};

enum class Plants {
    Corn,
    Flower,
    Tree
};

#endif
