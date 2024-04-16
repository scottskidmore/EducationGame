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
    int totalRam;
    int currentRam;

private:
    //std::vector<Plant*> presetPlants;
    std::map<QString, Plant*> presetPlants;


public slots:
    void getPlantText();
    void setCurrentPlant();

    /// \brief checkUserCommand - checks if the command entered is valid based on the current plant
    /// this will emit send plant text if the command is wrong, with slightly modified text.
    /// \param text - the command it is checking
    void checkUserCommand(QString text);

    void sendCurrentPlantToStack();

    /// \brief sendHint - sends a hint to the mainwindow based on the currentPlant
    void sendHint();

    void decreasingTime();

signals:
    void sendPlantToStack(Plant*);
    void sendPlantToHeap(Plant*);
    void sendPlantText(QString text);
    void sendPlantLocation(bool onHeap, QString plant);
    void enableHint();
    void sendHintText(QString text);
    void currentRamUpdated(int);
    void targetScoreUpdated(int);
    void currentScoreUpdated(int);
    void timeUpdated(int);
};

#endif // MODEL_H
