#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtWidgets/qlabel.h"
#include "model.h"
#include <QDebug>
#include "physicsplant.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Poalo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the MainWindow class. The MainWindow is the view in the MV structure.
            It handles the displaying and controlling of all UI elements. It has slots and signals
            to handle user inputs, and connections with the model class.
Citations:
*/
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief MainWindow - constructor
    /// \param parent - QWidget, defaulted to nullptr
    ///
    MainWindow(Model*, QWidget *parent = nullptr);
    ///
    /// \brief destructor
    ///
    ~MainWindow();
    ///
    /// \brief slideShow - stores the string path to the slides
    ///
    std::vector<QString> slideShow;
    ///
    /// \brief tutorialBoxes - stores pointers to all the tutorial labels
    ///
    std::vector<QLabel*> tutorialBoxes;
    ///
    /// \brief currentSlide - current slide counter
    ///
    int currentSlide;
    ///
    /// \brief tutorialComplete - bool to track if the tutorial is completed
    ///
    bool tutorialComplete;
    ///
    /// \brief tutorialCounter - counter to track which tutorial label to show
    ///
    int tutorialCounter;

private slots:
    ///
    /// \brief on_startButton_clicked - hides the slideshow and starts the game
    ///
    void on_startButton_clicked();
    ///
    /// \brief on_previousSlide_clicked - goes to the previous slide
    ///
    void on_previousSlide_clicked();
    ///
    /// \brief on_nextSlide_clicked - goes to the next slide
    ///
    void on_nextSlide_clicked();
    ///
    /// \brief on_hintButton_clicked - shows the hint for the selected plant
    ///
    void on_hintButton_clicked();
    ///
    /// \brief enableHintButton - enables the hint button
    ///
    void enableHintButton();
    ///
    /// \brief setStackPlant - sets a plant on the stack
    ///
    void setStackPlant(Plant*);
    ///
    /// \brief setHeapPlant - sets a plant on the heap
    ///
    void setHeapPlant(Plant*);
    ///
    /// \brief on_lineEdit_returnPressed - when the user clicks enter on the text box
    ///
    void on_lineEdit_returnPressed();
    ///
    /// \brief updateCurrentRam - updates the current ram
    ///
    void updateCurrentRam(int);
    ///
    /// \brief updateTargetScore - updates the target score
    ///
    void updateTargetScore(int);
    ///
    /// \brief updateCurrentScore - updates the current score
    ///
    void updateCurrentScore(int);
    ///
    /// \brief updateRound - updates the round
    ///
    void updateRound(int);
    ///
    /// \brief onUpdatedTimer - updates the timer label
    ///
    void onUpdatedTimer(int);
    ///
    /// \brief onNewRound - sets up the next round
    ///
    void onNewRound(bool);
    ///
    /// \brief onGameOver - displays the game over message
    ///
    void onGameOver();
    ///
    /// \brief onRoundOver - displays the round over message
    ///
    void onRoundOver(int, int, int);
    ///
    /// \brief onLevelCompleted - displays the level completed message
    ///
    void onLevelCompleted(int, int);
    ///
    /// \brief onGameCompleted - displays the game completed message
    ///
    void onGameCompleted();
    ///
    /// \brief on_pauseButton_clicked - pauses the game
    ///
    void on_pauseButton_clicked();
    ///
    /// \brief receivePhysicsPlant - takes in a physics plant and sets it visible
    ///
    void receivePhysicsPlant(PhysicsPlant*);
    ///
    /// \brief displayTutorialBox - displays the respective tutorial box
    ///
    void displayTutorialBox(int);

    void disablePlantButton(QString);

private:
    ///
    /// \brief ui - ui object
    ///
    Ui::MainWindow *ui;

signals:
    ///
    /// \brief gameStart - emitted when the game is started
    ///
    void gameStart();
    ///
    /// \brief sendCommandText - sends the text to the model that the user entered
    ///
    void sendCommandText(QString);
    ///
    /// \brief messageBoxClosed - emitted when the close the end round box
    ///
    void messageBoxClosed();
};
#endif // MAINWINDOW_H
