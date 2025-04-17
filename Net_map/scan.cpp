#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "map.h"
#include <QFile>
#include <QDomDocument>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QProcess>
#include <QProgressBar>
#include <QLineEdit>
#include <QWheelEvent>
#include <QGraphicsPixmapItem>
#include <QImageReader>
#include "portsinfo.h"

void startScan(QProcess * process, QString ipRange) {
    QString program = exePath + "/nmap/nmap.exe";
    QStringList arguments = {
         "-sS", "-O", "-F",
        "--script=broadcast-dhcp-discover,broadcast-ping,broadcast-netbios-master-browser,broadcast-igmp-discovery",
         "--stats-every", "2s",
         "-oX", "scan_network.xml",
         ipRange
    };
    process->setWorkingDirectory(exePath);
    process->start(program, arguments);
}