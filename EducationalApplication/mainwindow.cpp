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

    //add the slides
    slideShow.push_back(":/Slideshow/Images/slide1.png");
    slideShow.push_back(":/Slideshow/Images/slide2.png");
    slideShow.push_back(":/Slideshow/Images/slide3.png");
    slideShow.push_back(":/Slideshow/Images/slide4.png");
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
    connect(m, &Model::timeUpdated, this, &MainWindow::onUpdatedTimer);
    connect(m, &Model::enableNewRound, this, &MainWindow::onNewRound);
    connect(m, &Model::gameOver, this, &MainWindow::onGameOver);
    QObject::connect(ui->pauseButton, &QPushButton::clicked, m, &Model::pauseGame);
    QObject::connect(ui->startRound, &QPushButton::clicked, m, &Model::nextRound);



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
    ui->toolBar->show();
    ui->lineEdit->setEnabled(true);
    ui->timerLabel->setText("Time: --");
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
    ui->stackLayout->addWidget(button);
}

void MainWindow::setHeapPlant(Plant* p)
{
    // clear command text since it was correct
    ui->lineEdit->setText(QString());

    QPushButton* button = new QPushButton(this);
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
    ui->currentRamLabel->setText(QString("Avalible Ram: " + QString::number(ram)));
}

void MainWindow::updateTargetScore(int score) {
    ui->targetScoreLabel->setText(QString("Target Score: " + QString::number(score)));
}

void MainWindow::updateCurrentScore(int score) {
    ui->CurrentScoreLabel->setText(QString("Current Score: " + QString::number(score)));
}

void MainWindow::onUpdatedTimer(int time)
{
    ui->timerLabel->setText(QString("Time: " + QString::number(time)));
}

void MainWindow::onNewRound(bool)
{
    ui->startRound->setEnabled(true);
}

void MainWindow::onGameOver()
{
    ui->startRound->setDisabled(true);
    ui->startButton->show();
    QMessageBox::information(this, "Game Over!", "You didn't reach the target score.");
}


void MainWindow::on_pauseButton_clicked()
{
    if (ui->pauseButton->text() == "Pause")
    {
        ui->pauseButton->setText("Resume");
        ui->lineEdit->setEnabled(false);
    }
    else
    {
        ui->pauseButton->setText("Pause");
        ui->lineEdit->setEnabled(true);
    }
}

