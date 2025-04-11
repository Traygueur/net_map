#include "mainwindow.h"
#include "map.h"
#include <QApplication>
#include "portsinfo.h"

int main(int argc, char *argv[])
{
    loadPortsInfo("json/ports_info.json");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
