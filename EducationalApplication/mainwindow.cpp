#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Model *m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionCorn, &QAction::triggered, m, &Model::getPlantText);
    QObject::connect(m, &Model::sendPlantText, ui->centerTextDisplayBox, &QLabel::setText);
}

MainWindow::~MainWindow()
{
    delete ui;
}
