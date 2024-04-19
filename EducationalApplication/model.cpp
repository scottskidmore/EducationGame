#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    presetPlants[QString("actionCorn")] = new Plant(Plants::Corn, "cornDefault");
    presetPlants[QString("actionFlower")] = new Plant(Plants::Flower, "flowerDefault");
    presetPlants[QString("actionPotato")] = new Plant(Plants::Potato, "potatoDefault");
    presetPlants[QString("actionTree")] = new Plant(Plants::Tree, "treeDefault");
    presetPlants[QString("actionGrapes")] = new Plant(Plants::Grapes, "grapesDefault");

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
    if (currentPlant == nullptr)
        return;
    QString result = checkCommandName(text);
    QStringList substrings = result.split(" ");
    QString name = "";
    if (substrings.count() == 2) {
        name = substrings[1];
    }
    if(substrings.count() == 2 && substrings[0] != "D"){
        // if the name does exist on either let them know they can't use it.
        if (heapObj.plantMap.find(name) != heapObj.plantMap.end() || stackObj.plantMap.find(name) != stackObj.plantMap.end()) {
            emit sendPlantText(QString("You already have a plant named " + name));
            return;
        }
    }
    else
        emit sendPlantText("\nYour code did not match this plants heap\nor stack code. Try again.\nGet a hint if you're stuck!");
    if (substrings[0] == "H") {
        Plant* p = new Plant(currentPlant->thisPlant, name);
        p->onHeap=true;
        QObject::connect(p, &Plant::updateTextForDelete, this, &Model::getPlantTextForDelete);
        heapObj.plants.push_back(p);
        heapObj.plantMap[name] = p; // add to map, we will need to get rid of list
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYou planted on the heap!");
        emit sendPlantToHeap(p);
        currentRam = currentRam - p->cost;
        emit currentRamUpdated(currentRam);
    }
    else if (substrings[0] == "S") {
        Plant* p = new Plant(currentPlant->thisPlant, name);
        stackObj.plants.push_back(p);
        stackObj.plantMap[name] = p; // add to map, we will need to get rid of list
        emit sendPlantText(QString::fromStdString(currentPlant->basicInfo()) + "\nYou planted on the stack!");
        emit sendPlantToStack(p);
        currentRam = currentRam - p->cost;
        emit currentRamUpdated(currentRam);
    }
    else if (substrings[0] == "D") {
        // delete plant from heap!
        auto plant = heapObj.plantMap.find(name);
        if (plant != heapObj.plantMap.end()) { // if the plant is found on the heap delete it
             currentPlant->deleteMyButton();
            if (heapObj.plantMap[name]->heapGrowthTrack == 1){ // handles calculating score bassed on
                currentScore += heapObj.plantMap[name]->reward; // number of rounds the plant was on the heap
            }
            else if (heapObj.plantMap[name]->heapGrowthTrack == 2){
                currentScore += heapObj.plantMap[name]->reward * 2;
            }
            else if (heapObj.plantMap[name]->heapGrowthTrack == 3){
                currentScore += heapObj.plantMap[name]->reward * 3;
            }

            currentRam += heapObj.plantMap[name]->cost;
            heapObj.plantMap.erase(name);

            emit currentScoreUpdated(currentScore);
            emit currentRamUpdated(currentRam);
        }
        else
            emit sendPlantText(QString("The plant with name: " + name + "\nDoes not exist on the heap."));
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
    stackObj.plantMap.clear();
}

void Model::clearHeap()
{
    heapObj.plants.clear();
    heapObj.plantMap.clear();
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

QString Model::checkCommandName(QString command)
{
    std::smatch match;
    std::string commandStr = command.toStdString();
    std::regex validChars(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");
    std::regex deletePattern(R"(^delete\s([a-zA-Z_][a-zA-Z0-9_]*);$)");

    if (std::regex_match(commandStr, match, currentPlant->heapPattern)) {
        // If the match is successful, extract the name (group 1)
        std::string name = match[1].str();
        qDebug() << "name Heap: '" << name << "'";
        if (std::regex_match(name, validChars)) { // if the name is valid chars
            return QString("H " + QString::fromStdString(name));
        }
    }
    else if (std::regex_match(commandStr, match, currentPlant->stackPattern)) {
        // If the match is successful, extract the name (group 1)
        std::string name = match[1].str();
        qDebug() << "name Stack: '" << name << "'";
        if (std::regex_match(name, validChars)) { // if the name is valid chars
            return QString("S " + QString::fromStdString(name));
        }
    }
    else if (std::regex_match(commandStr, match, deletePattern)) {
        // If the match is successful, extract the name, this name is already valid checked.
        std::string name = match[1].str();
        return QString("D " + QString::fromStdString(name));
    }
    else {
        qDebug() << "invalid name";
        return QString("I");
    }
    qDebug() << "invalid name";
    return QString("I");
}

void Model::decreasingTime()
{
    if (roundTime == 0){
        if (stackCleared == false)   {
            clearStack();
            stackCleared = true;
            heapObj.updateHeapPlants();
            emit enableNewRound(true);
        }
        // if(currentScore < targetScore) {
        //     emit gameOver();
        //     roundTime = -1;
        //     timer.stop();
        // }
    }
    else if (stackCleared == false){
        roundTime--;
        emit timeUpdated((roundTime));
    }


}

void Model::endRound()
{
    heapObj.updateHeapPlants();
}


