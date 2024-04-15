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

void Model::setCurrentPlant()
{
    QObject *senderObject = QObject::sender();
    currentPlant=presetPlants[senderObject->objectName()];
}

void Model::sendCurrentPlantToStack()
{
    emit sendPlantToStack(currentPlant);
}

void Model::sendHint()
{
    emit sendPlantText(QString::fromStdString(currentPlant->hintCode()));
}

void Model::checkUserCommand(QString text)
{
    if (text == currentPlant->heapCode) {
        Plant* p = new Plant(currentPlant->thisPlant);
        heapObj.plants.push_back(p);
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYou planted on the heap!");
        emit sendPlantToHeap(p);
    }
    else if (text == currentPlant->stackCode) {
        Plant* p = new Plant(currentPlant->thisPlant);
        stackObj.plants.push_back(p);
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYou planted on the stack!");
        emit sendPlantToStack(p);
    }
    else {
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYour code did not match this plants heap\nor stack code. Try again.\nGet a hint if you're stuck!");
    }
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
