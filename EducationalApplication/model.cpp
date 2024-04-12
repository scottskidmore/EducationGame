#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    presetPlants[QString("actionCorn")] = new Plant(Plants::Corn);
    presetPlants[QString("actionRose_Flower")] = new Plant(Plants::Flower);
    presetPlants[QString("actionOrange_Flower")] = new Plant(Plants::Flower);
}

void Model::getPlantText()
{
    QObject *senderObject = QObject::sender();
    //int size = 10;
    //Plant* p = presetPlants.front();
    emit sendPlantText(QString::fromStdString(presetPlants[senderObject->objectName()]->basicInfo()));
    emit enableHint();
}

void Model::checkUserCommand(QString text)
{

}

void Model::clearStack()
{
    stackObj.plants.clear();
}

void Model::clearHeap()
{
    heapObj.plants.clear();
}

void Model::startGame()
{
    qDebug() << "game started";
}
