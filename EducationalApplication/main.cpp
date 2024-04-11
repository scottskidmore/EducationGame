#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model *m = new Model();
    MainWindow w(m);
    w.show();
    return a.exec();
}
