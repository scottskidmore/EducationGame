#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHBoxLayout"

MainWindow::MainWindow(Model *m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->hide();

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
    ui->timerLabel->setText("Time: --");
    emit gameStart();
}


void MainWindow::on_previousSlide_clicked()
{
    qDebug() << "prev slide";
}


void MainWindow::on_nextSlide_clicked()
{
    qDebug() << "next slide";
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

    QPushButton *button = new QPushButton(this);
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

    QPushButton *button = new QPushButton(this);
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
    ui->CurrentScoreLabel->setText(QString("Target Score: " + QString::number(score)));
}

void MainWindow::onUpdatedTimer(int time)
{
    ui->timerLabel->setText(QString("Time: " + QString::number(time)));
}

void MainWindow::onNewRound(bool)
{
    ui->startRound->setEnabled(true);
}

