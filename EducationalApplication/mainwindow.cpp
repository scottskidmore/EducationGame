#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHBoxLayout"

MainWindow::MainWindow(Model *m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->hide();

    QObject::connect(ui->actionRose_Flower, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionOrange_Flower, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionCorn, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(ui->actionRose_Flower, &QAction::triggered, m, &Model::setCurrentPlant);
    QObject::connect(ui->actionOrange_Flower, &QAction::triggered, m, &Model::setCurrentPlant);
    QObject::connect(ui->actionCorn, &QAction::triggered, m, &Model::setCurrentPlant);
    QObject::connect(m, &Model::enableHint, this, &MainWindow::enableHintButton);
    QObject::connect(m, &Model::sendPlantText, ui->centerTextDisplayBox, &QLabel::setText);
    QObject::connect(this, &MainWindow::gameStart, m, &Model::startGame);
    QObject::connect(ui->scrollArea, &ScrollArea::clicked, m, &Model::sendCurrentPlantToStack);
    QObject::connect(m, &Model::sendPlantToStack, this, &MainWindow::setStackPlant);
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
    QPushButton *button = new QPushButton(this);
    button->setMaximumSize(64, 64);
    button->setMinimumSize(64, 64);
    button->setGeometry(75, 10, 64, 64);
    QPixmap pixmap(":/Flowers/Images/flower_complete.png");
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
    button->setIconSize( QSize( button->size().width(),button->size().height()));
    ui->verticalLayout_2->addWidget(button);
}
