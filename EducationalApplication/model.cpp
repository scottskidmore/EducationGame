#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    presetPlants[QString("actionCorn")] = new Plant(Plants::Corn);
    presetPlants[QString("actionFlower")] = new Plant(Plants::Flower);
    presetPlants[QString("actionPotato")] = new Plant(Plants::Potato);
    presetPlants[QString("actionTree")] = new Plant(Plants::Tree);
    presetPlants[QString("actionGrapes")] = new Plant(Plants::Grapes);
    totalRam = 200;
    currentRam = totalRam;
    roundTime = 20;
    stackCleared = false;
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
    //totalRam = totalRam - currentPlant->cost;
    //emit currentRamUpdated(totalRam);
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
        currentRam = currentRam - p->cost;
        emit currentRamUpdated(currentRam);

    }
    else if (text == currentPlant->stackCode) {
        Plant* p = new Plant(currentPlant->thisPlant);
        stackObj.plants.push_back(p);
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYou planted on the stack!");
        emit sendPlantToStack(p);
        currentRam = currentRam - p->cost;
        emit currentRamUpdated(currentRam);

    }
    else {
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYour code did not match this plants heap\nor stack code. Try again.\nGet a hint if you're stuck!");
    }
}

void Model::clearStack()
{
    for (auto plant : stackObj.plants){
        currentScore += plant->reward;
    }
    emit currentScoreUpdated(currentScore);
    stackObj.plants.clear();
}

void Model::clearHeap()
{
    heapObj.plants.clear();
}

void Model::startGame()
{
    qDebug() << "game started";
    emit currentRamUpdated(totalRam);
    emit targetScoreUpdated(100);
    emit currentScoreUpdated(0);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, decreasingTime);
    timer->start(1000);
}

void Model::decreasingTime()
{
    if (roundTime == 0 && stackCleared == false){
        clearStack();
        stackCleared = true;
        emit enableNewRound(true);
    }
    else if (stackCleared == false){
        roundTime--;
        emit timeUpdated((roundTime));
    }

}
