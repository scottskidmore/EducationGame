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
#include "level.h"
#include "physicsplant.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the Model class. The Model is the Model in the MV structure.
            It handles the underlying logic of the game. It interacts with other classes
            to initiate gamplay, plant plants, and progression.
Citations:
*/
class Model : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief Model - constructor
    /// \param parent
    ///
    explicit Model(QObject *parent = nullptr);
    ///
    /// \brief heapObj
    ///
    Heap heapObj;
    ///
    /// \brief stackObj
    ///
    Stack stackObj;
    ///
    /// \brief timer - timer for the rounds
    ///
    QTimer timer;
    ///
    /// \brief worldSimTimer - timer for the world simulation, used to update world at 60 fps
    ///
    QTimer worldSimTimer;
    ///
    /// \brief currentTime - current time of the round, in seconds
    ///
    int currentTime;
    ///
    /// \brief currentPlant - pointer to a plant object, this will point to a plant in the presentPlanta map
    ///
    Plant* currentPlant = NULL;
    ///
    /// \brief currentScore
    ///
    int currentScore;
    ///
    /// \brief targetScore
    ///
    int targetScore;
    ///
    /// \brief currentRam
    ///
    int currentRam;
    ///
    /// \brief roundTime - how many seconds the current round should be
    ///
    int roundTime;
    ///
    /// \brief totalRam
    ///
    int totalRam;
    ///
    /// \brief stackCleared - bool if the stack has been cleared yet
    ///
    bool stackCleared;
    ///
    /// \brief gamePaused - bool to track if game is paused
    ///
    bool gamePaused;
    ///
    /// \brief round - current round
    ///
    int round;
    ///
    /// \brief level - current level
    ///
    int level;
    ///
    /// \brief tutorialComplete - bool to track if the tutorial has been completed
    ///
    bool tutorialComplete;
    ///
    /// \brief tutorialCounter - tracks which part of the tutorial the user is on
    ///
    int tutorialCounter;
    ///
    /// \brief clearStack - Initializes game parameters: targetScore, totalRam, currentRam, and currentTime. Then starts the game
    ///
    void clearStack();
    ///
    /// \brief clearHeap - Clears all plants in the heap, and deletes their buttons. Does not add any score
    ///
    void clearHeap();
    ///
    /// \brief startGame Initializes game parameters: targetScore, totalRam, currentRam, and currentTime. Then starts the game
    ///
    void startGame();
    ///
    /// \brief startTutorial - Starts the tutorial
    ///
    void startTutorial();

private:
    ///
    /// \brief presetPlants - holds the preset plants that represent the buttons in the toolbar, their key is the toolbar action name
    ///
    std::map<QString, Plant*> presetPlants;
    ///
    /// \brief rounds - holds the rounds/levels for this game
    ///
    std::vector<Level> rounds;
    ///
    /// \brief world - pointer to the current world that represents the physics plants
    ///
    b2World* world;
    ///
    /// \brief physicsPlants - holds all the physics plants so they can be deleted
    ///
    std::vector<PhysicsPlant*> physicsPlants;
    ///
    /// \brief currentPlantToolbarName - holds the name of the action in the toolbar for the currentPlant, used to disable the currentPlants button
    ///
    QString currentPlantToolbarName;
    // All these counts represent how many of that plant the user has planted this level.
    int flowerCount;
    int cornCount;
    int potatoCount;
    int treeCount;
    int grapesCount;
    ///
    /// \brief checkCommandName - Checks if a command is valid, and returns the name that the user used in the command if so.
    /// \return Returns a string starting with S or H for stack or heap. D for delete, or I for invalid. The name is one space after the initial character.
    ///
    QString checkCommandName(QString);
    ///
    /// \brief nextLevel - Starts the next Level.
    ///
    void nextLevel();
    ///
    /// \brief checkPlantInventory - Checks if the plant type passed in will reach its limit for the current level, handles incrementing the plant count.
    /// This will also emit disablePlantButton, when the plant limit has been reached for that type of plant.
    /// \return True if the plant limit has been reached.
    ///
    bool checkPlantInventory(Plants);

public slots:
    ///
    /// \brief getPlantText - called from MainWindow when a toolbar plant is clicked. Emits sendPlantText with that plants appropriate text.
    ///
    void getPlantText();
    ///
    /// \brief getPlantTextForDelete - This is called from a plant object, when that plant object is clicked on in the Heap.
    /// It will emit text to be displayed to guide the user through deleting that specific plant.
    /// \param p - Pointer to the plant, currentPlant will be set to this pointer.
    ///
    void getPlantTextForDelete(Plant* p);
    ///
    /// \brief setCurrentPlant - sets the currentPlant to the appropriate plant.
    ///
    void setCurrentPlant();
    ///
    /// \brief checkUserCommand - Checks if the command entered is valid based on the current plant.
    /// This will emit send plant text if the command is wrong, with slightly modified text.
    /// \param text - the command it is checking
    ///
    void checkUserCommand(QString text);
    ///
    /// \brief sendHint - Sends a hint to the mainwindow based on the currentPlant.
    ///
    void sendHint();
    ///
    /// \brief decreasingTime - Decreases time in the round, and checks if the round is over and if levels are over.
    ///
    void decreasingTime();
    ///
    /// \brief nextRound - Starts the next round with more time, more ram, and a higher target score.
    ///
    void nextRound();
    ///
    /// \brief pauseGame - Pauses the game so the timer does not count down.
    ///
    void pauseGame();
    ///
    /// \brief updateWorld - Updates the physics world so the plants fall out of the stack.
    ///
    void updateWorld();

signals:
    ///
    /// \brief sendPlantToStack - sends a pointer to a new Plant object to the MainWindow
    ///
    void sendPlantToStack(Plant*);
    ///
    /// \brief sendPlantToHeap - sends a pointer to a new Plant object to the MainWindow, this will be connected to its button so it can be clicked on and deleted
    ///
    void sendPlantToHeap(Plant*);
    ///
    /// \brief sendPlantText - sends the text that will be displayed in the center box of the MainWindow
    /// \param text
    ///
    void sendPlantText(QString text);
    ///
    /// \brief enableHint - turns on the hint button
    ///
    void enableHint();
    // These updated will change the text displayed on the MainWindow for each field
    void currentRamUpdated(int);
    void targetScoreUpdated(int);
    void currentScoreUpdated(int);
    void timeUpdated(int);
    ///
    /// \brief enableNewRound - enables a new round
    ///
    void enableNewRound(bool);
    ///
    /// \brief gameOver - emitted to display game over
    ///
    void gameOver();
    ///
    /// \brief roundOver
    ///
    void roundOver(int, int, int);// round, current score, target score
    ///
    /// \brief levelCompleted
    ///
    void levelCompleted(int, int); // level, current score
    ///
    /// \brief gameCompleted
    ///
    void gameCompleted();
    ///
    /// \brief dropPlants - emitted to make the physics plants fall
    ///
    void dropPlants(); // This will update the physics plants when they are falling out of the stack.
    ///
    /// \brief addPhysicsPlant - emitted to add a physics plant to the UI
    ///
    void addPhysicsPlant(PhysicsPlant*); // Adds a PhysicsPlant to the MainWindow.
    ///
    /// \brief roundUpdate - emitted to update the round
    ///
    void roundUpdate(int);
    ///
    /// \brief modelPause - emitted when the model initiates a pause
    ///
    void modelPause();
    ///
    /// \brief displayTutorial - emitted to display desired tutorial box
    ///
    void displayTutorial(int);
    ///
    /// \brief disablePlantButton - emitted to disable a specific plant button
    ///
    void disablePlantButton(QString); // The QString is the toolbar action name
};

#endif // MODEL_H
