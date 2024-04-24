#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHBoxLayout"
#include "QMessageBox"

MainWindow::MainWindow(Model *m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->hide();
    ui->lineEdit->setDisabled(true);
    tutorialBoxes.push_back(ui->tutorialLabel1);
    tutorialBoxes.push_back(ui->tutorialLabel2);
    tutorialBoxes.push_back(ui->tutorialLabel3);
    tutorialBoxes.push_back(ui->tutorialLabel4);
    tutorialBoxes.push_back(ui->tutorialLabel5);
    tutorialBoxes.push_back(ui->tutorialLabel6);
    tutorialBoxes.push_back(ui->tutorialLabel7);
    tutorialBoxes.push_back(ui->tutorialLabel8);

    for (int i = 0; i < (int)tutorialBoxes.size(); i++)
    {
        tutorialBoxes[i]->hide();
    }
    tutorialComplete = false;
    tutorialCounter = 0;


    //add the slides
    slideShow.push_back(":/Slideshow/Images/titleSlide.png");
    slideShow.push_back(":/Slideshow/Images/stackSlide.png");
    slideShow.push_back(":/Slideshow/Images/heapSlide.png");
    slideShow.push_back(":/Slideshow/Images/inputSlide.png");
    slideShow.push_back(":/Slideshow/Images/infoSlide.png");
    slideShow.push_back(":/Slideshow/Images/flowerSlide.png");
    slideShow.push_back(":/Slideshow/Images/potatoSlide.png");
    slideShow.push_back(":/Slideshow/Images/cornSlide.png");
    slideShow.push_back(":/Slideshow/Images/treeSlide.png");
    slideShow.push_back(":/Slideshow/Images/grapesSlide.png");
    currentSlide = 0;

    QPixmap pixmap(slideShow[currentSlide]);
    ui->startLabel->setPixmap(pixmap);
    ui->startLabel->setScaledContents(true);

    QPalette pal;

    QObject::connect(ui->actionPotato, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionFlower, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionCorn, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionPotato, &QAction::triggered, m, &Model::setCurrentPlant);
    QObject::connect(ui->actionFlower, &QAction::triggered, m, &Model::setCurrentPlant);
    QObject::connect(ui->actionCorn, &QAction::triggered, m, &Model::setCurrentPlant);
    QObject::connect(ui->actionTree, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionTree, &QAction::triggered, m, &Model::setCurrentPlant);
    QObject::connect(ui->actionGrapes, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionGrapes, &QAction::triggered, m, &Model::setCurrentPlant);

    QObject::connect(m, &Model::enableHint, this, &MainWindow::enableHintButton);
    QObject::connect(m, &Model::sendPlantText, ui->centerTextDisplayBox, &QLabel::setText);
    QObject::connect(this, &MainWindow::gameStart, m, &Model::startGame);
    //QObject::connect(ui->scrollArea, &ScrollArea::clicked, m, &Model::sendCurrentPlantToStack);
    QObject::connect(m, &Model::sendPlantToStack, this, &MainWindow::setStackPlant);
    QObject::connect(m, &Model::sendPlantToHeap, this, &MainWindow::setHeapPlant);
    QObject::connect(this, &MainWindow::sendCommandText, m, &Model::checkUserCommand);
    QObject::connect(ui->hintButton, &QPushButton::clicked, m, &Model::sendHint);
    connect(m, &Model::currentRamUpdated, this, &MainWindow::updateCurrentRam);
    connect(m, &Model::targetScoreUpdated, this, &MainWindow::updateTargetScore);
    connect(m, &Model::currentScoreUpdated, this, &MainWindow::updateCurrentScore);
    connect(m, &Model::roundUpdate, this, &MainWindow::updateRound);
    connect(m, &Model::timeUpdated, this, &MainWindow::onUpdatedTimer);
    connect(m, &Model::enableNewRound, this, &MainWindow::onNewRound);
    connect(m, &Model::gameOver, this, &MainWindow::onGameOver);
    connect(m, &Model::roundOver, this, &MainWindow::onRoundOver);
    connect(m, &Model::levelCompleted, this, &MainWindow::onLevelCompleted);
    connect(m, &Model::gameCompleted, this, &MainWindow::onGameCompleted);
    QObject::connect(ui->pauseButton, &QPushButton::clicked, m, &Model::pauseGame);
    QObject::connect(ui->startRound, &QPushButton::clicked, m, &Model::nextRound);
    connect(m, &Model::addPhysicsPlant, this, &MainWindow::receivePhysicsPlant);
    QObject::connect(this, &MainWindow::messageBoxClosed, m, &Model::updateWorld);
    QObject::connect(m, &Model::modelPause, this, &MainWindow::on_pauseButton_clicked);
    QObject::connect(m, &Model::displayTutorial, this, &MainWindow::displayTutorialBox);
    QObject::connect(m, &Model::disablePlantButton, this, &MainWindow::disablePlantButton);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    ui->startLabel->hide();
    ui->nextSlide->hide();
    ui->previousSlide->hide();
    ui->startButton->hide();
    ui->startRound->hide();
    ui->toolBar->show();
    ui->lineEdit->setEnabled(true);
    ui->timerLabel->setText("Time: --");
    ui->actionCorn->setDisabled(true);
    ui->actionGrapes->setDisabled(true);
    ui->actionPotato->setDisabled(true);
    ui->actionCorn->setVisible(false);
    ui->actionGrapes->setVisible(false);
    ui->actionPotato->setVisible(false);
    emit gameStart();
}


void MainWindow::on_previousSlide_clicked()
{
    qDebug() << "prev slide";
    if (currentSlide > 0)
    {
        currentSlide--;
        QPixmap pixmap(slideShow[currentSlide]);
        ui->startLabel->setPixmap(pixmap);
        ui->startLabel->setScaledContents(true);
    }
}


void MainWindow::on_nextSlide_clicked()
{
    qDebug() << "next slide";
    if (currentSlide < (int)slideShow.size() - 1)
    {
        currentSlide++;
        QPixmap pixmap(slideShow[currentSlide]);
        ui->startLabel->setPixmap(pixmap);
        ui->startLabel->setScaledContents(true);
    }
}


void MainWindow::on_hintButton_clicked()
{

}

void MainWindow::enableHintButton()
{
    ui->hintButton->setEnabled(true);
}

void MainWindow::setStackPlant(Plant* p)
{
    // clear command text since it was correct
    ui->lineEdit->setText(QString());

    QPushButton* button = new QPushButton(this);
    button->setObjectName(p->myName);
    button->setStyleSheet("#" + p->myName + " {background-color: white; }");
    button->setAutoFillBackground(true);
    p->setMyButton(button);
    QObject::connect(p, &Plant::removeThisPlantsButton, button, &QPushButton::deleteLater);
    QObject::connect(p, &Plant::updateButtonImage, button, &QPushButton::setIcon);
    QObject::connect(button, &QPushButton::clicked, p, &Plant::myPlantClicked);

    button->setMaximumSize(64, 64);
    button->setMinimumSize(64, 64);
    button->setGeometry(75, 10, 64, 64);
    button->setIcon(QIcon(p->imagePath));
    button->setIconSize(QSize(64, 64));
    ui->stackLayout->addWidget(button);
}

void MainWindow::setHeapPlant(Plant* p)
{
    // clear command text since it was correct
    ui->lineEdit->setText(QString());
    QPushButton* button = new QPushButton(this);
    button->setStyleSheet("background-color: white;");
    button->setAutoFillBackground(true);
    p->setMyButton(button);
    QObject::connect(p, &Plant::removeThisPlantsButton, button, &QPushButton::deleteLater);
    QObject::connect(p, &Plant::updateButtonImage, button, &QPushButton::setIcon);
    QObject::connect(button, &QPushButton::clicked, p, &Plant::myPlantClicked);

    button->setMaximumSize(64, 64);
    button->setMinimumSize(64, 64);
    button->setGeometry(75, 10, 64, 64);
    QPixmap pixmap(p->imagePath);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
    button->setIconSize( QSize( button->size().width(),button->size().height()));
    ui->heapLayout->addWidget(button);
}

void MainWindow::on_lineEdit_returnPressed()
{
    emit sendCommandText(ui->lineEdit->text());
}

void MainWindow::updateCurrentRam(int ram) {
    ui->currentRamLabel->setText(QString("Available RAM: " + QString::number(ram)));
}

void MainWindow::updateTargetScore(int score) {
    ui->targetScoreLabel->setText(QString("Target Score: " + QString::number(score)));
}

void MainWindow::updateCurrentScore(int score) {
    ui->CurrentScoreLabel->setText(QString("Current Score: " + QString::number(score)));
}

void MainWindow::updateRound(int round) {
    ui->RoundLabel->setText(QString("Round: " + QString::number(round))+"/5");
}

void MainWindow::onUpdatedTimer(int time)
{
    ui->timerLabel->setText(QString("Time: " + QString::number(time)));
}

void MainWindow::onNewRound(bool FT)
{

    ui->lineEdit->setEnabled(true);
    ui->startRound->setEnabled(FT);
    ui->startRound->hide();
    ui->pauseButton->setEnabled(true);
}

void MainWindow::onGameOver()
{
    for (QAction* act : ui->toolBar->actions()) {
        act->setEnabled(true);
    }
    ui->startRound->setDisabled(true);
    ui->startRound->hide();
    ui->lineEdit->clear();
    ui->lineEdit->setDisabled(true);
    ui->startButton->show();
    QMessageBox::information(this, "Game Over!", "You didn't reach the target score.");
}

void MainWindow::onRoundOver(int round, int currentScore, int targetScore){
    update();
    ui->lineEdit->clear();
    ui->lineEdit->setDisabled(true);
    ui->startRound->setEnabled(true);
    ui->startRound->show();
    ui->pauseButton->setDisabled(true);
    if(((((round - (round % 5)) / 5) + 1) == 1) && ((round % 5) + 1 == 1)){
        ui->actionCorn->setVisible(true);
        ui->actionPotato->setVisible(true);
        ui->actionCorn->setEnabled(true);
        ui->actionPotato->setEnabled(true);
        }
    else if(((((round - (round % 5)) / 5) + 1) == 1) && ((round % 5) + 1 == 2)){
        ui->actionGrapes->setVisible(true);
        ui->actionGrapes->setEnabled(true);
    }
    QMessageBox::information(this, "Level: " + QString::number(((round - (round % 5)) / 5) + 1) +
                                   " Round: " + QString::number((round % 5) + 1),
                                   "Nice work! Keep going to ensure you reach the "
                                   "target score by the end of round 5."
                                   "\nCurrent Score: " + QString::number(currentScore) +
                                   "\nTarget Score: " + QString::number(targetScore));
    qDebug() << "message box ok";
    emit messageBoxClosed();
}

void MainWindow::onLevelCompleted(int level, int score){
    for (QAction* act : ui->toolBar->actions()) {
        act->setEnabled(true);
    }
    ui->lineEdit->clear();
    ui->lineEdit->setDisabled(true);
    ui->startRound->setEnabled(true);
    ui->startRound->show();
    ui->pauseButton->setDisabled(true);
    if(level == 1){
        QMessageBox::information(this, "Level: " + QString::number(2) +
                                   " Round: " + QString::number(0), "CONGRATULATIONS!!!"
                                   "\nYou have completed level " + QString::number(level) +
                                   "\nWith a score of " + QString::number(score) +
                                   "\nYou are now an FARMING INTERN");
    }
    else if(level == 2){
        QMessageBox::information(this, "Level: " + QString::number(3) +
                                   " Round: " + QString::number(0), "CONGRATULATIONS!!!"
                                   "\nYou have completed level " + QString::number(level) +
                                   "\nWith a score of " + QString::number(score) +
                                   "\nYou are now an JUNIOR FARMER");
    }
    else if (level == 3){
        QMessageBox::information(this,"Level: " + QString::number(4) +
                                  " Round: " + QString::number(0), "CONGRATULATIONS!!!"
                                  "\nYou have completed level " + QString::number(level) +
                                  "\nWith a score of " + QString::number(score) +
                                  "\nYou are now an SENIOR FARMER");
    }
    emit messageBoxClosed();
}

void MainWindow::onGameCompleted(){
    QMessageBox::information(this,"GAME COMPLETED", "CONGRATULATIONS!!!"
                                 "\nYou have completed all levels"
                                 "\nYou really know your memory allocation"
                                 "\nYou are now ready to startup your own farm");
}

void MainWindow::on_pauseButton_clicked()
{
    if (ui->pauseButton->text() == "Pause")
    {
        ui->pauseButton->setText("Resume");
        ui->lineEdit->setEnabled(false);
        ui->startRound->setDisabled(true);
    }
    else
    {
        ui->pauseButton->setText("Pause");
        ui->lineEdit->setEnabled(true);
        if (!tutorialComplete)
        {
            tutorialBoxes[tutorialCounter]->hide();
            tutorialCounter++;
        }
        if (tutorialCounter == 8)
        {
            tutorialComplete = true;
        }
    }
}

void MainWindow::receivePhysicsPlant(PhysicsPlant *p)
{
    p->setParent(ui->centralwidget);
    p->raise();
    p->setVisible(true);
    this->update();
    //qDebug() << ui->centralwidget->children().toList();
}

void MainWindow::displayTutorialBox(int tutorialNum)
{
    //ui->tutorialLabel1->show();
    tutorialBoxes[tutorialNum]->show();
}

void MainWindow::disablePlantButton(QString name)
{
    QList<QAction*> actions = ui->toolBar->actions();
    for (QAction* act : actions) {
        if (act->objectName() == name) {
            act->setEnabled(false);
        }
    }
}

