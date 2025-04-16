#include <string>
#include "mainwindow.h"
#include "map.h"
#include <QApplication>
#include "portsinfo.h"
#include "globals.h"

#include <QDebug>

QString exePath;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    exePath = QCoreApplication::applicationDirPath();
    std::string strExePath = exePath.toStdString();
    std::string jsonPath = strExePath + "/json_data/ports_info.json";
    loadPortsInfo(jsonPath);

    MainWindow w;
    w.show();
    return a.exec();
}