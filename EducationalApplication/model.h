#ifndef MODEL_H
#define MODEL_H

#include "plant.h"
#include "qobject.h"
#include <vector>
#include <QString>
#include <QObject>
#include "heap.h"
#include "stack.h"
#include "qtimer.h"
#include <QDebug>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    //std::vector<Plant*> stackPlants;
    //std::vector<Plant*> heapPlants;
    Heap heapObj;
    Stack stackObj;
    void clearStack();
    void clearHeap();
    std::vector<QString> levelInfo;
    QTimer timer;
    void startGame();
    int round;
    int roundTime;
    Plant* currentPlant=NULL;

private:
    //std::vector<Plant*> presetPlants;
    std::map<QString, Plant*> presetPlants;


public slots:
    void getPlantText();
    void setCurrentPlant();
    void checkUserCommand(QString text);
    void sendCurrentPlantToStack();

signals:
    void sendPlantToStack(Plant*);
    void sendPlantText(QString text);
    void sendPlantLocation(bool onHeap, QString plant);
    void enableHint();
};

#endif // MODEL_H
