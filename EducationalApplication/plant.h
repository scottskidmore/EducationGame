#ifndef PLANT_H
#define PLANT_H
#include <iostream>
#include <string>
#include <QString>

enum class Plants;

class Plant {
public:
    Plant(Plants plantType);
    Plants thisPlant;
    std::string hintCode();
    std::string basicInfo();
    std::string displayName();
    bool onHeap;
    int cost;
    int reward;
    QString heapCode;
    QString stackCode;
    QString imagePath;

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
