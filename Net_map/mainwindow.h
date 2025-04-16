#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include <QMainWindow>
#include <QScrollArea>
#include <QProcess>
#include <QTime>           // pour QTime startTime
#include <QString>
#include <QStringList>
#include <QCoreApplication>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QScrollArea *scrollArea;
    QProcess *process = nullptr;     // le processus Nmap
    QString scanBuffer;
    int currentScanPhase = 1;
    int lastProgressPercent = -1;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmapItem;
    double scaleFactor = 1.0;


private slots:
    void manageActionMenu(QMenu* menu, QString texte, int index);
    void nmapScan();
    void ouvrirPage(int index);
    void saveCarto();
    void loadCarto(int exitCode, QProcess::ExitStatus status, bool scanDone);
    void loadXmlToTable(const QString& filePath);
    void securityTable(const QString& filePath);
    void updateSecurityTable();
    void updateScanOutput();
};

#endif // MAINWINDOW_H
