#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    presetPlants.push_back(new Plant(Plants::Flower));
}

void Model::getPlantText()
{
    Plant* p = presetPlants.front();
    emit sendPlantText(QString::fromStdString(p->hintCode()));
}

void Model::checkUserCommand(QString text)
{

}
