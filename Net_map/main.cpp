#include "mainwindow.h"
#include "map.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    createMap();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
