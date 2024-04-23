#include "model.h"
#include <regex>

Model::Model(QObject *parent)
    : QObject{parent}
{
    presetPlants[QString("actionCorn")] = new Plant(Plants::Corn, "cornDefault");
    presetPlants[QString("actionFlower")] = new Plant(Plants::Flower, "flowerDefault");
    presetPlants[QString("actionPotato")] = new Plant(Plants::Potato, "potatoDefault");
    presetPlants[QString("actionTree")] = new Plant(Plants::Tree, "treeDefault");
    presetPlants[QString("actionGrapes")] = new Plant(Plants::Grapes, "grapesDefault");

    rounds.push_back(Level(100, 100, 200));

    currentScore = 0;
    stackCleared = false;
    gamePaused = false;
    tutorialComplete = false;
    tutorialCounter = 0;

    // Connect model's game timer to the decreasingTime slot;
    QObject::connect(&timer, &QTimer::timeout, this, &Model::decreasingTime);
    connect(&worldSimTimer, &QTimer::timeout, this, &Model::updateWorld);
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
            plant->second->deleteMyButton();
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
            emit sendPlantText(QString("The plant with name: " + name + "\nWas deleted"));

            emit currentScoreUpdated(currentScore);
            emit currentRamUpdated(currentRam);
            return;
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
    b2Vec2 gravity(0.0f, 25.0f);
    this->world = new b2World(gravity);
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // adding the physics plants and getting scores.
    for(auto plant : stackObj.plants){
        currentScore += plant->reward;
        //get plant position, create a Box2D plant object and connect it to dropPlants
        QPoint plantPos = plant->myButton->pos();

        PhysicsPlant* p = new PhysicsPlant(world, plant->imagePath, plantPos);
        QObject::connect(this, &Model::dropPlants, p, &PhysicsPlant::updateSimulation);
        physicsPlants.push_back(p);
        emit addPhysicsPlant(p);
        plant->deleteMyButton();

    }

    emit currentScoreUpdated(currentScore);
    stackObj.plants.clear();
    stackObj.plantMap.clear();
}

void Model::clearHeap()
{
    for (auto plant : heapObj.plants){ //added to make sure the bottons/icons are
        plant->deleteMyButton();      // deleted along with the map
    }
    heapObj.plants.clear();
    heapObj.plantMap.clear();
}

void Model::startGame()
{
    clearHeap(); // make sure heap is cleared on game restart
    targetScore = 5;
    totalRam = 150;
    currentRam = totalRam;
    round = 1;
    level = 1;
    rounds.push_back(Level(round, targetScore, totalRam));
    roundTime = 10;
    currentTime = roundTime;
    stackCleared = false;
    qDebug() << "game started";
    emit targetScoreUpdated(targetScore);
    emit currentScoreUpdated(0);
    emit currentRamUpdated(currentRam);
    emit roundUpdate(0);
    timer.start(1000);
    startTutorial();
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
    if (currentTime == 0){
        if (stackCleared == false)   {      // Clear stack and update heap plants when timer raeches 0
            for (auto plant : stackObj.plants){
                currentRam += plant->cost;
            }
            clearStack();
            stackCleared = true;
            heapObj.updateHeapPlants();
            if ((round > 0) && (round % 5 == 0) && currentScore >= targetScore){
                if((((round - (round % 5)) / 5)) == 4){
                    emit gameCompleted();
                }
                else {
                    emit levelCompleted(level, currentScore);
                    level++;
                }
            }
            else{
                 emit roundOver(round - 1, currentScore, targetScore);
            }
        }
        if((round > 0 ) && (round % 5 == 0) && currentScore < targetScore) {    // End the game becuase the player didn't reach the target score
            emit gameOver();
            currentTime = -1;
            timer.stop();
        }
    }
    else if (stackCleared == false){        // Decrement timer countdown
        currentTime--;
        emit timeUpdated((currentTime));
    }
}

void Model::endRound()
{
    heapObj.updateHeapPlants();
}

void Model::nextRound()
{
    for (auto physPlant : physicsPlants) {
        physPlant->deleteLater();
    }
    physicsPlants.clear();
    worldSimTimer.stop();

    if((round > 0) && (round % 5 == 0)){
        nextLevel();
    }
    round += 1;
    currentTime = roundTime;
    stackCleared = false;
    emit enableNewRound(false);
    emit roundUpdate(round);
    qDebug() << "round started";
}

void Model::nextLevel(){
    for (auto physPlant : physicsPlants) {
        physPlant->deleteLater();
    }
    physicsPlants.clear();
    worldSimTimer.stop();

    for (auto plant : heapObj.plants){
        plant->heapGrowthTrack = 4;
    }

    level++;
    targetScore += 5;
    currentRam += 50;
    roundTime += 10;
    currentScore = 0;
    round=0;
    rounds.push_back(Level(round, targetScore, totalRam));
    emit targetScoreUpdated(targetScore);
    emit currentScoreUpdated(0);
    emit roundUpdate(0);
    emit currentRamUpdated(currentRam);
}

void Model::pauseGame()
{
    if (!gamePaused)
    {
        gamePaused = true;
        qDebug() << "game paused";
        timer.stop();
    }
    else
    {
        gamePaused = false;
        qDebug() << "game resumed";
        timer.start();
        if (!tutorialComplete)
        {
            startTutorial();
        }
        if (tutorialCounter == 2)
        {
            tutorialComplete = true;
        }
    }
}

void Model::updateWorld()
{
    world->Step(1.0f / 60.0f, 6, 2);
    emit dropPlants();

    if (!worldSimTimer.isActive()) {
        worldSimTimer.start(16);
    }
}

void Model::startTutorial()
{
    if (!tutorialComplete && round == 1 && tutorialCounter == 0)
    {
        emit modelPause();
        pauseGame();
        emit displayTutorial(tutorialCounter);
        tutorialCounter++;
    }
    else if (!tutorialComplete && round == 1 && tutorialCounter == 1)
    {
        emit modelPause();
        pauseGame();
        emit displayTutorial(tutorialCounter);
        tutorialCounter++;
    }
}



