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

    loadXmlToTable("C:/Users/coulo/Downloads/scan_network.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    qDebug() << "loadImage() est appelé !";  // Vérification

    QPixmap pixmap("C:\\Users\\coulo\\Documents\\ESAIP\\PROJECT_APPLICATIF_C++\\net_map\\Net_map\\network.bmp");

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
    QString sourcePath = "C:\\Users\\coulo\\Documents\\ESAIP\\PROJECT_APPLICATIF_C++\\net_map\\Net_map\\network.bmp";  // Chemin actuel de l'image
    QString destinationPath = QFileDialog::getSaveFileName(this,
        "Enregistrer la cartographie",
        "network.bmp",  // Nom suggéré par défaut
        "Images BMP (*.bmp)");

    if (destinationPath.isEmpty())
        return;

    if (!QFile::copy(sourcePath, destinationPath)) {
        QMessageBox::warning(this, "Erreur", "Impossible de copier l'image à l'emplacement choisi.");
    }

    
}

void MainWindow::loadXmlToTable(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier XML");
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        QMessageBox::critical(this, "Erreur", "Le fichier XML est invalide");
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement(); // <nmaprun>
    QDomNodeList hosts = root.elementsByTagName("host");

    ui->tableWidget->setRowCount(hosts.count());
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({ "IP", "Type (OS)", "Accuracy", "MAC Address" });

    for (int i = 0; i < hosts.count(); ++i) {
        QDomElement host = hosts.at(i).toElement();

        QString ip, mac, osType, accuracy;

        // Adresse IP + MAC
        QDomNodeList addresses = host.elementsByTagName("address");
        for (int j = 0; j < addresses.count(); ++j) {
            QDomElement address = addresses.at(j).toElement();
            QString addr = address.attribute("addr");
            QString type = address.attribute("addrtype");

            if (type == "ipv4") ip = addr;
            if (type == "mac") mac = addr;
        }

        // OS name à partir de <osmatch>
        QDomNodeList osNodes = host.elementsByTagName("os");
        if (!osNodes.isEmpty()) {
            QDomElement osElement = osNodes.at(0).toElement();
            QDomNodeList osMatches = osElement.elementsByTagName("osmatch");
            if (!osMatches.isEmpty()) {
                QDomElement osMatch = osMatches.at(0).toElement();
                osType = osMatch.attribute("name");
				accuracy = osMatch.attribute("accuracy");
            }
        }


        // Ajout dans le tableau
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(ip));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(osType.isEmpty() ? "Inconnu" : osType));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(accuracy));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(mac));
		
    }
}