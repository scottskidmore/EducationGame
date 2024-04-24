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
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Poalo Diotaiuti, Drew Humphrey, Adam Bentley.
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
    explicit Model(QObject *parent = nullptr);
    Heap heapObj;
    Stack stackObj;
    QTimer timer; // Timer for the rounds.
    QTimer worldSimTimer; // Timer for the world simulation, used to update the world at 60fps.
    int currentTime; // The current time of the round, in seconds.
    Plant* currentPlant=NULL; // A pointer to a plant object, this will point to a plant in the presetPlants map.
    int currentScore;
    int targetScore;
    int currentRam;
    int roundTime; // How many seconds the current round should be.
    int totalRam;
    bool stackCleared;
    bool gamePaused;
    int round;
    int level;
    bool tutorialComplete;
    int tutorialCounter; // Tracks which part of the tutorial the user is on.

    // public methods

    /// \brief clearStack - Initializes game parameters: targetScore, totalRam, currentRam, and currentTime. Then starts the me.ga
    void clearStack();

    /// \brief clearHeap - Clears all plants in the heap, and deletes their buttons. Does not add any score.
    void clearHeap();

    /// \brief startGame Initializes game parameters: targetScore, totalRam, currentRam, and currentTime. Then starts the game.
    void startGame();

    /// \brief startTutorial - Starts the tutorial.
    void startTutorial();

private:
    std::map<QString, Plant*> presetPlants; // Holds the preset plants that represent the buttons in the toolbar, their key is the toolbar action name.
    std::vector<Level> rounds; // Holds the rounds/levels for this game.
    b2World* world; // Pointer to the current world that represents the physics plants.
    std::vector<PhysicsPlant*> physicsPlants; // Holds all the physics plants so they can be deleted.
    QString currentPlantToolbarName; // Holds the name of the action in the toolbar for the currentPlant, used to disable the currentPlants button

    // All these counts represent how many of that plant the user has planted this level.
    int flowerCount;
    int cornCount;
    int potatoCount;
    int treeCount;
    int grapesCount;

    // private methods

    /// \brief checkCommandName - Checks if a command is valid, and returns the name that the user used in the command if so.
    /// \return Returns a string starting with S or H for stack or heap. D for delete, or I for invalid. The name is one space after the initial character.
    QString checkCommandName(QString);

    /// \brief nextLevel - Starts the next Level.
    void nextLevel();

    /// \brief checkPlantInventory - Checks if the plant type passed in will reach its limit for the current level, handles incrementing the plant count.
    /// This will also emit disablePlantButton, when the plant limit has been reached for that type of plant.
    /// \return True if the plant limit has been reached.
    bool checkPlantInventory(Plants);



public slots:

    /// \brief getPlantText - called from MainWindow when a toolbar plant is clicked. Emits sendPlantText with that plants appropriate text.
    void getPlantText();

    /// \brief getPlantTextForDelete - This is called from a plant object, when that plant object is clicked on in the Heap.
    /// It will emit text to be displayed to guide the user through deleting that specific plant.
    /// \param p - Pointer to the plant, currentPlant will be set to this pointer.
    void getPlantTextForDelete(Plant* p);

    /// \brief setCurrentPlant - sets the currentPlant to the appropriate plant.
    void setCurrentPlant();

    /// \brief checkUserCommand - Checks if the command entered is valid based on the current plant.
    /// This will emit send plant text if the command is wrong, with slightly modified text.
    /// \param text - the command it is checking
    void checkUserCommand(QString text);

    /// \brief sendHint - Sends a hint to the mainwindow based on the currentPlant.
    void sendHint();

    /// \brief decreasingTime - Decreases time in the round, and checks if the round is over and if levels are over.
    void decreasingTime();

    /// \brief nextRound - Starts the next round with more time, more ram, and a higher target score.
    void nextRound();

    /// \brief pauseGame - Pauses the game so the timer does not count down.
    void pauseGame();

    /// \brief updateWorld - Updates the physics world so the plants fall out of the stack.
    void updateWorld();

signals:
    void sendPlantToStack(Plant*); // Sends a pointer to a new Plant object to the MainWindow
    void sendPlantToHeap(Plant*); // Sends a pointer to a new Plant object to the MainWindow, this will be connected to its button so it can be clicked on and deleted.
    void sendPlantText(QString text); // Sends the text that will be displayed in the center box of the MainWindow.
    void enableHint(); // Turns on the hint button.

    // These updated will change the text displayed on the MainWindow for each field
    void currentRamUpdated(int);
    void targetScoreUpdated(int);
    void currentScoreUpdated(int);
    void timeUpdated(int);

    void enableNewRound(bool);
    void gameOver();
    void roundOver(int, int, int);// round, current score, target score
    void levelCompleted(int, int); // level, current score
    void gameCompleted();
    void dropPlants(); // This will update the physics plants when they are falling out of the stack.
    void addPhysicsPlant(PhysicsPlant*); // Adds a PhysicsPlant to the MainWindow.
    void roundUpdate(int);
    void modelPause();
    void displayTutorial(int);
    void disablePlantButton(QString); // The QString is the toolbar action name
};

#endif // MODEL_H
