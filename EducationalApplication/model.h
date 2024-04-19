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
#include "round.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    //std::vector<Plant*> stackPlants;
    //std::vector<Plant*> heapPlants;
    Heap heapObj;
    Stack stackObj;
    std::vector<QString> levelInfo;
    QTimer timer;
    int roundTime;
    Plant* currentPlant=NULL;
    int currentScore;
    int targetScore;
    int currentRam;
    int totalRam;
    bool stackCleared;
    bool gamePaused;
    int round;

    // public methods
    ///
    /// \brief clearStack Initializes game parameters: targetScore, totalRam, currentRam, and roundTime. Then starts the game.
    ///
    void clearStack();
    void clearHeap();
    void startGame();
    void deletePlantFromHeap(Plant);

private:
    //std::vector<Plant*> presetPlants;
    std::map<QString, Plant*> presetPlants;
    std::vector<Round> rounds;
    QString checkCommandName(QString);

public slots:
    void getPlantText();
    void getPlantTextForDelete(Plant* p);
    void setCurrentPlant();

    /// \brief checkUserCommand - checks if the command entered is valid based on the current plant
    /// this will emit send plant text if the command is wrong, with slightly modified text.
    /// \param text - the command it is checking
    void checkUserCommand(QString text);

    void sendCurrentPlantToStack();

    /// \brief sendHint - sends a hint to the mainwindow based on the currentPlant
    void sendHint();

    void decreasingTime();

    void endRound();

    void nextRound();

    void pauseGame();

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
    void enableNewRound(bool);
    void gameOver();
};

#endif // MODEL_H
