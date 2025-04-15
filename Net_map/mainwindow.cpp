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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setStyleSheet("background-color: #2E2E2E;");
    connect(ui->pushButtonImage, &QPushButton::clicked, this, &MainWindow::nmapScan);
    //QAction *actionNouvellePage = new QAction("Changer de page", this);
    //ui->menuNetMap->addAction(actionNouvellePage);

    // Nav Function
    manageActionMenu(ui->menuNetMap, "Changer de page", 0);
    manageActionMenu(ui->menuDevices, "Changer de page", 1);
    manageActionMenu(ui->menuSecurity, "Changer de page", 2);

    // Save carto
    QAction *actionSaveCarto = new QAction("Enregistrer la cartographie", this);
    ui->menuNetMap->addAction(actionSaveCarto);
    connect(actionSaveCarto, &QAction::triggered, this, &MainWindow::saveCarto);
    // Load carto
    QAction* actionLoadCarto = new QAction("Charger la cartographie (Xml File)", this);
    ui->menuNetMap->addAction(actionLoadCarto);
    connect(actionLoadCarto, &QAction::triggered, this, 
        [=]() {
            loadCarto(0, QProcess::NormalExit, false);
        }
    );


    ui->progressBar->setValue(0);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QVBoxLayout* scrollLayout = new QVBoxLayout(ui->scrollAreaWidgetContents_3); 
    scrollLayout->setSpacing(10);

    ui->progressBar->setStyleSheet("QProgressBar { min-height: 30px; max-height: 30px; }");

    connect(ui->checkBoxOpen, &QCheckBox::checkStateChanged, this, &MainWindow::updateSecurityTable);
    connect(ui->checkBoxFiltered, &QCheckBox::checkStateChanged, this, &MainWindow::updateSecurityTable);
    connect(ui->checkBoxClosed, &QCheckBox::checkStateChanged, this, &MainWindow::updateSecurityTable);



    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
   
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::manageActionMenu(QMenu* menu, QString texte, int index) {
    QAction* action = new QAction(texte, this);
    action->setData(index);
    connect(action, &QAction::triggered, this, [this, action]() {
        ouvrirPage(action->data().toInt());
        });
    menu->addAction(action);
}

void MainWindow::nmapScan()
{

    QString ipRange = ui->lineEdit->text().trimmed();
	if (ipRange.isEmpty()) {
		QMessageBox::warning(this, "Erreur", "Veuillez entrer une plage d'adresses IP.");
		return;
	}

    QString exePath = QCoreApplication::applicationDirPath();

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
        this, [=](int exitCode, QProcess::ExitStatus status) {
            loadCarto(exitCode, status, true);
        });



    startTime = QTime::currentTime();
    process->setWorkingDirectory(exePath);
    process->start(program, arguments);

}

void MainWindow::ouvrirPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
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

void MainWindow::loadCarto(int exitCode, QProcess::ExitStatus status, bool scanDone) {
    if (exitCode == 0) {
        ui->labelStep->setText("Étape 1/6");
        ui->progressBar->setValue(0);

        QString xmlPath, linkQString;
        if (!scanDone) {
            linkQString = QFileDialog::getOpenFileName(this, "Choisir un fichier", "", "Fichiers XML (*.xml);;Tous les fichiers (*)");

            if (linkQString.isEmpty()) {
                return;
            }

            std::string link = linkQString.toStdString();
            createMap(link);
        }
        else {
            createMap("Null");
        }

        QString exePath = QCoreApplication::applicationDirPath();
        QString pngPath = exePath + "/network.png";
        QImageReader::setAllocationLimit(2048);
        QPixmap pixmap(pngPath);

        if (!pixmap.isNull()) {
            // Affiche l'image dans le QLabel
            pixmapItem = scene->addPixmap(pixmap);
            scene->setSceneRect(pixmapItem->boundingRect().adjusted(-10, -10, 10, 10));
            ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
        }

        


        if (!scanDone) {
            xmlPath = linkQString;
        }
        else {
            xmlPath = exePath + "/scan_network.xml";
        }

        if (QFile::exists(xmlPath)) {
            loadXmlToTable(xmlPath);
            securityTable(xmlPath);
        }
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

void MainWindow::securityTable(const QString& filePath) {
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

    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
    ui->tableWidget_2->setColumnCount(5);
    ui->tableWidget_2->setHorizontalHeaderLabels({ "IP", "Ports", "Protocols", "State", "Danger" });

    int line = 0;
    int Danger;
    QString ip, Ports, Protocols, State;
    std::string Protocol;

    for (int i = 0; i < hosts.count(); ++i) {
        QDomElement host = hosts.at(i).toElement();

        // Adresse IP + MAC
        QDomNodeList addresses = host.elementsByTagName("address");
        for (int j = 0; j < addresses.count(); ++j) {
            QDomElement address = addresses.at(j).toElement();
            QString addr = address.attribute("addr");
            QString type = address.attribute("addrtype");

            if (type == "ipv4") ip = addr;
        }
        //ui->tableWidget_2->insertRow(line);
        //ui->tableWidget_2->setItem(line, 0, new QTableWidgetItem(ip));

        // Ports "spécials" à partir de <ports>...<port ...>
        QDomNodeList portsItems = host.elementsByTagName("ports");
        if (!portsItems.isEmpty()) {
            for (int j = 0; j < portsItems.count(); ++j) {
                QDomElement portsElement = portsItems.at(j).toElement();
                QDomNodeList portList = portsElement.elementsByTagName("port");

                for (int k = 0; k < portList.count(); ++k) {
                    QDomElement portElement = portList.at(k).toElement();
                    Ports = portElement.attribute("portid");

                    QDomElement serviceElement = portElement.firstChildElement("service");
                    if (!serviceElement.isNull()) {
                        Protocols = serviceElement.attribute("name");
                    }

                    QDomElement stateElement = portElement.firstChildElement("state");
                    if (!stateElement.isNull()) {
                        State = stateElement.attribute("state");
                    }

                    int numPort = Ports.toInt();
                    Danger = getDangerLevelForPort(numPort);

                    ui->tableWidget_2->insertRow(line);
                    ui->tableWidget_2->setItem(line, 0, new QTableWidgetItem(ip));
                    ui->tableWidget_2->setItem(line, 1, new QTableWidgetItem(Ports));
                    ui->tableWidget_2->setItem(line, 2, new QTableWidgetItem(Protocols));
                    ui->tableWidget_2->setItem(line, 3, new QTableWidgetItem(State));
                    ui->tableWidget_2->setItem(line, 4, new QTableWidgetItem(Danger));

                    line++;

                }
            }
        }
        // <extraports state="filtered" count="98"><extrareasons reason = "no-response" count = "98" proto = "tcp" ports = "7,9,...,49152-49157"/></extraports>
        QDomElement portsElement = host.firstChildElement("ports");
        if (!portsElement.isNull()) {
            QDomElement extraPorts = portsElement.firstChildElement("extraports");
            if (!extraPorts.isNull()) {
                QString extraPortsState;
                extraPortsState = extraPorts.attribute("state");

                QDomElement listExtraPorts = extraPorts.firstChildElement("extrareasons");
                if (!listExtraPorts.isNull()) {
                    Ports = listExtraPorts.attribute("ports");

                    QStringList listPorts = Ports.split(",", Qt::SkipEmptyParts);
                    for (int j = 0; j < listPorts.count(); ++j) {
                        QString port = listPorts.at(j);

                        if (port.contains("-")) {
                            QStringList range = port.split("-");
                            int start = range.at(0).toInt();
                            int end = range.at(1).toInt();

                            for (int k = start; k <= end; ++k) {
                                QString strPort = QString::number(k);
                                Protocol = getProtocolForPort(k);
                                Danger = getDangerLevelForPort(k);
                                QString dangerText = (Danger != -1) ? QString::number(Danger) : "Unknown";

                                // Ajout au tableau HERE
                                ui->tableWidget_2->insertRow(line);
                                ui->tableWidget_2->setItem(line, 0, new QTableWidgetItem(ip));
                                ui->tableWidget_2->setItem(line, 1, new QTableWidgetItem(strPort));
                                ui->tableWidget_2->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(Protocol)));
                                ui->tableWidget_2->setItem(line, 3, new QTableWidgetItem(extraPortsState));
                                ui->tableWidget_2->setItem(line, 4, new QTableWidgetItem(dangerText));

                                line++;
                            }
                        }
                        else {
                            int numPort = port.toInt();
                            Protocol = getProtocolForPort(numPort);
                            Danger = getDangerLevelForPort(numPort);
                            QString dangerText = (Danger != -1) ? QString::number(Danger) : "Unknown";

                            ui->tableWidget_2->insertRow(line);
                            ui->tableWidget_2->setItem(line, 0, new QTableWidgetItem(ip));
                            ui->tableWidget_2->setItem(line, 1, new QTableWidgetItem(port));
                            ui->tableWidget_2->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(Protocol)));
                            ui->tableWidget_2->setItem(line, 3, new QTableWidgetItem(extraPortsState));
                            ui->tableWidget_2->setItem(line, 4, new QTableWidgetItem(dangerText));

                            line++;
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::updateSecurityTable() {
    for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row) {
        QTableWidgetItem* item = ui->tableWidget_2->item(row, 3);
        if (!item) continue; // Skip des lignes sans état défini

        QString state = item->text();

        bool show = (state == "open" && ui->checkBoxOpen->isChecked()) ||
            (state == "filtered" && ui->checkBoxFiltered->isChecked()) ||
            (state == "closed" && ui->checkBoxClosed->isChecked());

        ui->tableWidget_2->setRowHidden(row, !show);
    }
}

void MainWindow::updateScanOutput() {

    QString output = process->readAllStandardOutput();
    output += process->readAllStandardError();

    scanBuffer += output;

    QRegularExpression regex(
        "About (\\d+(?:\\.\\d+)?)% done(?:;.*?\\((\\d+:\\d+) remaining\\))?",
        QRegularExpression::DotMatchesEverythingOption
    );

    QRegularExpressionMatchIterator it = regex.globalMatch(scanBuffer);

    QRegularExpressionMatch lastMatch;
    while (it.hasNext()) {
        lastMatch = it.next();  // on garde le dernier match
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
