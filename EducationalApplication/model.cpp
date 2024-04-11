#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    plants.push_back(new Plant(Plants::Flower));
}

void Model::getPlantText()
{
    Plant* p = plants.front();
    emit sendPlantText(QString::fromStdString(p->hintCode()));
}
