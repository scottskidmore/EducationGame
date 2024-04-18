#ifndef PLANT_H
#define PLANT_H
#include <iostream>
#include <string>
#include <QString>
#include <QPushButton>
#include "qobject.h"

enum class Plants;

class Plant : public QObject
{
    Q_OBJECT
public:
    explicit Plant(Plants plantType, QObject *parent = nullptr);
    Plants thisPlant;
    std::string hintCode();
    std::string basicInfo();
    std::string displayName();
    bool onHeap;
    int cost;
    int reward;
    int roundsOnHeap;
    QString heapCode;
    QString stackCode;
    QString imagePath;
    QString deleteCode;
    void deleteMyButton();

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
    int heapGrowthTrack;
    QPushButton* myButton;
};

enum class Plants {
    Corn,
    Flower,
    Tree,
    Potato,
    Grapes
};

#endif
