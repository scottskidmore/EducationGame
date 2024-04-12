#ifndef MODEL_H
#define MODEL_H

#include "plant.h"
#include "qobject.h"
#include <vector>
#include <QString>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    std::vector<Plant*> stackPlants;
    std::vector<Plant*> heapPlants;

private:
    std::vector<Plant*> presetPlants;


public slots:
    void getPlantText();
    void checkUserCommand(QString text);

signals:
    void sendPlantText(QString text);
    void sendPlantLocation(bool onHeap, QString plant);
};

#endif // MODEL_H
