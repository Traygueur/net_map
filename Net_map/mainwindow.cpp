#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setStyleSheet("background-color: #2E2E2E;");
    setFixedSize(1007, 511);
    connect(ui->pushButtonImage, &QPushButton::clicked, this, &MainWindow::loadImage);
    QAction *actionSaveCarto = new QAction("Enregistrer la cartographie", this);
    QAction *actionNouvellePage = new QAction("Changer de page", this);
    ui->menuEquipement->addAction(actionNouvellePage);
    ui->menuNetMap->addAction(actionNouvellePage);
    ui->menuNetMap->addAction(actionSaveCarto);
    connect(actionNouvellePage, &QAction::triggered, this, &MainWindow::ouvrirPage);
    connect(actionSaveCarto, &QAction::triggered, this, &MainWindow::saveCarto);


    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->widgetContainer->layout());
    if (layout) {
        layout->setAlignment(ui->imageLabel, Qt::AlignHCenter);        // Centre horizontalement
        layout->setAlignment(ui->pushButtonImage, Qt::AlignHCenter);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    qDebug() << "loadImage() est appelé !";  // Vérification

    QPixmap pixmap("C:/Users/coulo/Documents/netmap_qt/build/Desktop_Qt_6_8_2_MinGW_64_bit-Release/network.bmp");

    if (pixmap.isNull()) {
        ui->imageLabel->setText("Erreur : Impossible de charger l'image !");
    } else {
        ui->imageLabel->setPixmap(pixmap);
        ui->imageLabel->setFixedSize(pixmap.size());        // Fixe QLabel à la taille de l’image

    }
}


void MainWindow::ouvrirPage()
{
    if (ui->stackedWidget->currentWidget() == ui->page1) {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (ui->stackedWidget->currentWidget() == ui->page2) {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::saveCarto()
{
    qDebug() << "Enregistrement de la cartographie...";
}
