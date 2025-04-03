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
    ui->progressBar->setValue(0);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QVBoxLayout* scrollLayout = new QVBoxLayout(ui->scrollAreaWidgetContents_3); 
    scrollLayout->setSpacing(10);

    scrollLayout->addWidget(ui->imageLabel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    qDebug() << "loadImage() est appelé !";  // Vérification

    ui->progressBar->setValue(0);

    scanBuffer.clear();
    process = new QProcess(this);
    QString program = "C:/Program Files (x86)/Nmap/nmap.exe";
    QStringList arguments = {
         "-sS", "-O", "-F",
         "--script=broadcast-dhcp-discover,broadcast-ping,broadcast-netbios-master-browser,broadcast-igmp-discovery",
         "--stats-every", "2s",
         "-oX", "scan_network.xml",
         "192.168.1.0/24"
    };
    process->setWorkingDirectory("C:\\Users\\coulo\\Documents\\ESAIP\\PROJECT_APPLICATIF_C++\\net_map\\Net_map\\");
    connect(process, &QProcess::readyReadStandardOutput,
        this, &MainWindow::updateScanOutput);
    connect(process, &QProcess::readyReadStandardError,
        this, &MainWindow::updateScanOutput);

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, &MainWindow::onScanFinished);

    startTime = QTime::currentTime();
    process->start(program, arguments);

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
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({ "IP", "Type (OS)", "Accuracy", "MAC Address", "Vendor"});

    for (int i = 0; i < hosts.count(); ++i) {
        QDomElement host = hosts.at(i).toElement();

        QString ip, mac, osType, accuracy, vendor;

        // Adresse IP + MAC
        QDomNodeList addresses = host.elementsByTagName("address");
        for (int j = 0; j < addresses.count(); ++j) {
            QDomElement address = addresses.at(j).toElement();
            QString addr = address.attribute("addr");
            QString type = address.attribute("addrtype");
			QString vendoradd = address.attribute("vendor");

            if (type == "ipv4") ip = addr;
            if (type == "mac") mac = addr;
            vendor = vendoradd;
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
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(vendor));
		
    }
}


void MainWindow::updateScanOutput() {
    QString output = process->readAllStandardOutput();
    output += process->readAllStandardError();

    qDebug() << "📥 Nmap Output brut >>" << output;

    scanBuffer += output;

    QRegularExpression regex(
        "About (\\d+(?:\\.\\d+)?)% done(?:;.*?\\((\\d+:\\d+) remaining\\))?",
        QRegularExpression::DotMatchesEverythingOption
    );

    QRegularExpressionMatchIterator it = regex.globalMatch(scanBuffer);

    QRegularExpressionMatch lastMatch;
    while (it.hasNext()) {
        lastMatch = it.next();  // 🔁 on garde le dernier match
    }

    if (lastMatch.hasMatch()) {
        double percent = lastMatch.captured(1).toDouble();
        QString remaining = lastMatch.captured(2);

        ui->progressBar->setValue(static_cast<int>(percent));

        qDebug() << "✅ Progress match trouvé :" << percent << "%, reste : " << remaining;
    }
    else {
        qDebug() << "❌ Aucun match dans scanBuffer (longueur : " << scanBuffer.length() << ")";
    }
}



void MainWindow::onScanFinished(int exitCode, QProcess::ExitStatus status) {
    if (exitCode == 0) {
        ui->progressBar->setValue(0);
        createMap();

        QString bmpPath = "C:/Users/coulo/Documents/ESAIP/PROJECT_APPLICATIF_C++/net_map/Net_map/network.bmp";
        qDebug() << "🧩 Chemin absolu image : " << bmpPath;
        qDebug() << "🧩 Existe ? " << QFile::exists(bmpPath);

        QPixmap pixmap(bmpPath);
        qDebug() << "🧩 Taille du pixmap : " << pixmap.size();

        if (pixmap.isNull()) {
            qDebug() << "❌ L'image BMP n'a pas été trouvée ou est vide !";
            ui->imageLabel->setText("Erreur : Impossible de charger l'image !");
            return;
        }

        // Affiche l'image dans le QLabel
        ui->imageLabel->setPixmap(pixmap);
        ui->imageLabel->adjustSize();  // ajuste la taille du QLabel à celle de l’image
        ui->imageLabel->setFixedSize(pixmap.size());

        // (facultatif, pour test visuel)
       

        // Charge les données XML dans le tableau
        QString xmlPath = "C:/Users/coulo/Documents/ESAIP/PROJECT_APPLICATIF_C++/net_map/Net_map/scan_network.xml";
        if (QFile::exists(xmlPath)) {
            loadXmlToTable(xmlPath);
        }
        else {
            qDebug() << "❌ Fichier XML introuvable : " << xmlPath;
        }
    }
    else {
        qDebug() << "❌ Scan Nmap échoué avec exitCode =" << exitCode;
    }
}


