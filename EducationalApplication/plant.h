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

public slots:
    void updateHeapGrowth();

private:
    void createCorn();
    void createFlower();
    void createTree();
    void createPotato();
    void createGrapes();
    std::string toString(Plants p);
    int heapGrowthTrack;
};

enum class Plants {
    Corn,
    Flower,
    Tree,
    Potato,
    Grapes
};

#endif
