#ifndef PLANT_H
#define PLANT_H
#include <iostream>
#include <string>
#include <QString>
#include <QPushButton>
#include "qobject.h"
#include <regex>

enum class Plants;

class Plant : public QObject
{
    Q_OBJECT
public:
    explicit Plant(Plants plantType, QString name, QObject *parent = nullptr);
    Plants thisPlant;
    std::string hintCode();
    std::string basicInfo();
    std::string displayName();
    bool onHeap;
    int cost;
    int reward;
    int heapGrowthTrack; // this tracks the heap growth, to change image and points
    QString heapCode;
    std::regex heapPattern;
    std::regex stackPattern;
    QString stackCode;
    QString imagePath;
    QString deleteCode;
    std::regex deletePattern;
    void deleteMyButton();
    QString myName; // this is its name, its used as the key for the heap or stack
    QPushButton* myButton;

public slots:
    void updateHeapGrowth();
    void myPlantClicked();
    void myPlantHarvested();
    void setMyButton(QPushButton*);

signals:
    void updateButtonImage(QIcon);
    void removeThisPlantsButton();
    void updateTextForDelete(Plant* p);

private:
    void createCorn();
    void createFlower();
    void createTree();
    void createPotato();
    void createGrapes();
    std::string toString(Plants p);

};

enum class Plants {
    Corn,
    Flower,
    Tree,
    Potato,
    Grapes
};

#endif
