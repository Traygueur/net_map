#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    QTime startTime;
    int currentScanPhase = 1;
    int lastProgressPercent = -1;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmapItem;
    double scaleFactor = 1.0;


private slots:
    void loadImage();
    void ouvrirPage();
    void saveCarto();
    void loadXmlToTable(const QString& filePath);
    void updateScanOutput();
    void onScanFinished(int exitCode, QProcess::ExitStatus status);
    void wheelEvent(QWheelEvent* event);
};

#endif // MAINWINDOW_H
