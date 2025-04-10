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



    ui->progressBar->setValue(0);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QVBoxLayout* scrollLayout = new QVBoxLayout(ui->scrollAreaWidgetContents_3); 
    scrollLayout->setSpacing(10);

    ui->progressBar->setStyleSheet("QProgressBar { min-height: 30px; max-height: 30px; }");


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{

    QString ipRange = ui->lineEdit->text().trimmed();
	if (ipRange.isEmpty()) {
		QMessageBox::warning(this, "Erreur", "Veuillez entrer une plage d'adresses IP.");
		return;
	}

    QString exePath = QCoreApplication::applicationDirPath();
    qDebug() << "loadImage() est appelé !";  // Vérification
	qDebug() << "exePath : " << exePath;  // Vérification

    ui->progressBar->setValue(0);

    scanBuffer.clear();
    process = new QProcess(this);
    QString program = exePath + "/nmap/nmap.exe";
    QStringList arguments = {
         "-sS", "-O", "-F",
        "--script=broadcast-dhcp-discover,broadcast-ping,broadcast-netbios-master-browser,broadcast-igmp-discovery",
         "--stats-every", "2s",
         "-oX", "scan_network.xml",
         ipRange
    };
    connect(process, &QProcess::readyReadStandardOutput,
        this, &MainWindow::updateScanOutput);
    connect(process, &QProcess::readyReadStandardError,
        this, &MainWindow::updateScanOutput);

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, &MainWindow::onScanFinished);



    startTime = QTime::currentTime();
    process->setWorkingDirectory(exePath);
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
    QString exePath = QCoreApplication::applicationDirPath();
    QString sourcePath = exePath + "/network.png";  // Chemin actuel de l'image
    QString destinationPath = QFileDialog::getSaveFileName(this,
        "Enregistrer la cartographie",
        "network.png",  // Nom suggéré par défaut
        "Images PNG (*.png)");

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
        if (lastProgressPercent > percent) {
            currentScanPhase++;
            if (currentScanPhase > 6) currentScanPhase = 6; // pas au-delà
        }

        lastProgressPercent = percent;

        ui->progressBar->setValue(static_cast<int>(percent));
        ui->labelStep->setText(QString("Étape %1/6").arg(currentScanPhase));
    }
}



void MainWindow::onScanFinished(int exitCode, QProcess::ExitStatus status) {
    if (exitCode == 0) {
        QString exePath = QCoreApplication::applicationDirPath();
        currentScanPhase = 1;
        ui->labelStep->setText("Étape 1/6");
        ui->progressBar->setValue(0);
        createMap();

        QString bmpPath = exePath + "/network.png";
        qDebug() << "🧩 Chemin absolu image : " << bmpPath;
        qDebug() << "🧩 Existe ? " << QFile::exists(bmpPath);

        QPixmap pixmap(bmpPath);
        qDebug() << "🧩 Taille du pixmap : " << pixmap.size();

        // Affiche l'image dans le QLabel
        pixmapItem = scene->addPixmap(pixmap);
        scene->setSceneRect(pixmap.rect());

        // (facultatif, pour test visuel)
       

        // Charge les données XML dans le tableau
        QString xmlPath = exePath +"/scan_network.xml";
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

void MainWindow::wheelEvent(QWheelEvent* event) {
    if (ui->graphicsView->underMouse() && (event->modifiers() & Qt::ControlModifier)) {
        const double zoomFactor = 1.15;
        if (event->angleDelta().y() > 0)
            ui->graphicsView->scale(zoomFactor, zoomFactor);
        else
            ui->graphicsView->scale(1.0 / zoomFactor, 1.0 / zoomFactor);
        event->accept();
    }
    else {
        QMainWindow::wheelEvent(event);
    }
}


