#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    presetPlants[QString("actionCorn")] = new Plant(Plants::Corn);
    presetPlants[QString("actionFlower")] = new Plant(Plants::Flower);
    presetPlants[QString("actionPotato")] = new Plant(Plants::Potato);
    presetPlants[QString("actionTree")] = new Plant(Plants::Tree);
    presetPlants[QString("actionGrapes")] = new Plant(Plants::Grapes);

    rounds.push_back(Round(100,100, 200));
    targetScore = 100;
    totalRam = 200;
    currentRam = totalRam;
    roundTime = 20;
    currentScore = 0;
    stackCleared = false;
    QObject::connect(&timer, &QTimer::timeout, this, &Model::decreasingTime);
}

void Model::getPlantText()
{
    QObject *senderObject = QObject::sender();
    //int size = 10;
    //Plant* p = presetPlants.front();
    emit sendPlantText(QString::fromStdString(presetPlants[senderObject->objectName()]->basicInfo()));
    emit enableHint();
}

void Model::getPlantTextForDelete(Plant* p)
{
    currentPlant = p;
    emit sendPlantText("To Delete this plant type:\n" + p->deleteCode);
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
        QObject::connect(p, &Plant::updateTextForDelete, this, &Model::getPlantTextForDelete);
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
    else if (text == currentPlant->deleteCode) {
        currentPlant->deleteMyButton();
        // delete plant from heap or stack!
    }
    else {
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYour code did not match this plants heap\nor stack code. Try again.\nGet a hint if you're stuck!");
    }
}

void Model::clearStack()
{
    for (auto plant : stackObj.plants){
        currentScore += plant->reward;
        plant->deleteMyButton();
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
    rounds.push_back(Round(100,100, 200));
    targetScore = 100;
    totalRam = 200;
    currentRam = totalRam;
    roundTime = 20;
    stackCleared = false;
    qDebug() << "game started";
    emit targetScoreUpdated(rounds.at(0).targetScore);
    emit currentScoreUpdated(0);
    emit currentRamUpdated(currentRam);

    timer.start(1000);
}

void Model::decreasingTime()
{
    if (roundTime == 0){
        if (stackCleared == false)   {
            clearStack();
            stackCleared = true;
            emit enableNewRound(true);

        }
        if(currentScore < targetScore) {
            emit gameOver();
            roundTime = -1;
            timer.stop();
        }
    }
    else if (stackCleared == false){
        roundTime--;
        emit timeUpdated((roundTime));
    }


}

void Model::endRound()
{
    heapObj.updateHeapPlants();
    for (auto plant : stackObj.plants){
        plant->roundsOnHeap += 1;
    }
}


