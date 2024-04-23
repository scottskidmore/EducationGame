#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtWidgets/qlabel.h"
#include "model.h"
#include <QDebug>
#include "physicsplant.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model*, QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<QString> slideShow;
    std::vector<QLabel*> tutorialBoxes;
    int currentSlide;
    bool tutorialComplete;
    int tutorialCounter;

private slots:
    void on_startButton_clicked();

    void on_previousSlide_clicked();

    void on_nextSlide_clicked();

    void on_hintButton_clicked();

    void enableHintButton();

    void setStackPlant(Plant*);

    void setHeapPlant(Plant*);

    void on_lineEdit_returnPressed();

    void updateCurrentRam(int);

    void updateTargetScore(int);

    void updateCurrentScore(int);

    void updateRound(int);

    void onUpdatedTimer(int);

    void onNewRound(bool);

    void onGameOver();

    void onRoundOver(int, int, int);

    void onLevelCompleted(int, int);

    void onGameCompleted();

    void on_pauseButton_clicked();

    void receivePhysicsPlant(PhysicsPlant*);

    void displayTutorialBox(int);

private:
    Ui::MainWindow *ui;

signals:
    void gameStart();

    /// \brief sendCommandText - sends the text to the model that the user entered.
    void sendCommandText(QString);
    void messageBoxClosed();
};
#endif // MAINWINDOW_H
