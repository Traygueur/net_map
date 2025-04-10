#include "map.h"
#include <fstream>
#include <QProcess>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdio>
#include <regex>
#include <sstream>
#include <QFile> // Ajout de l'inclusion nécessaire
#include <QRegularExpression> // Ajout de l'inclusion nécessaire
#include <QDomDocument> // Ajout de l'inclusion nécessaire
#include <QMessageBox> // Ajout de l'inclusion nécessaire
#include <QRegularExpressionMatch> // Ajout de l'inclusion nécessaire
#include <QRegularExpressionMatchIterator> // Ajout de l'inclusion nécessaire
#include <QDebug> // Ajout de l'inclusion nécessaire


QString ipGateway;


void parseArpTableQt(std::unordered_map<std::string, Device>& network_map) {
    QProcess process;
    process.start("arp", { "-a" });
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n');

    QRegularExpression regex(R"((\d+\.\d+\.\d+\.\d+)\s+([\da-fA-F:-]{17}))");

    for (const QString& line : lines) {
        QRegularExpressionMatch match = regex.match(line);
        if (match.hasMatch()) {
            QString ip = match.captured(1);
            QString mac = match.captured(2);

            network_map[ip.toStdString()] = Device{ "Unknown", mac.toStdString(), {} };
        }
    }
};


int createMap() {
	detectGateway();
    QString exePath = QCoreApplication::applicationDirPath();
    std::unordered_map<std::string, Device> network_map;

    QString xmlPath = exePath + "/scan_network.xml";
    QFile file(xmlPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return 0;
    }
    file.close();

    QDomElement root = doc.documentElement(); // <nmaprun>
    QDomNodeList hosts = root.elementsByTagName("host");

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
        }

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

        qDebug() << ipGateway;
        if (ip == ipGateway) {
            network_map[ip.toStdString()] = { osType.toStdString(), mac.toStdString(), {} };
        }
        else
        {
            network_map[ip.toStdString()] = { osType.toStdString(), mac.toStdString(), {ipGateway.toStdString()} };
        }
    }
	
    // Génération du graphe
    generateGraphe(network_map);

    return 0;
};

void generateGraphe(const std::unordered_map<std::string, Device>& network_map) {
    QString exePath = QCoreApplication::applicationDirPath();
    QString dotPath = exePath + "/network.dot";
    std::ofstream file(dotPath.toStdString());
    file << "graph Network {\n";
    file << R"( layout=neato;
                bgcolor="#2E2E2E";
                overlap=scale;
                splines=true;
                sep="+1";
                nodesep=0.3;
                ranksep=0.4;

                node [style=filled, shape=ellipse, fillcolor="white", fontcolor="black", color="black", fontsize=14];
                edge [color="white", penwidth=1.2, len=0.1];)";
    for (const auto& entry : network_map) {
        std::string ip = entry.first;
        Device device = entry.second;
        file << "  \"" << ip << "\" [label=\"" << ip << "\\n" << device.type << "\"];\n";

        for (const auto& link : device.links) {
            file << "  \"" << ip << "\" -- \"" << link << "\";\n";
        }
    }
    file << "}\n"; // Fin du graphe
    file.close();  // Ferme le fichier

    QProcess process;
    QString program = exePath + "/graphviz/dot.exe";  // Chemin absolu
    QStringList arguments = {"-Kneato", "-Tpng", "-Gdpi=100", "network.dot", "-o", "network.png"};


    process.setWorkingDirectory(exePath);
    process.start(program, arguments);
    process.waitForFinished();

    qDebug() << "✅ Graphviz terminé, on charge l’image.";

};

void detectGateway() {
    QProcess process;
    process.start("ipconfig");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    qDebug() << "ipconfig Output brut >>" << output;

    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    QRegularExpression ipv4Regex(R"(\b\d{1,3}(?:\.\d{1,3}){3}\b)");

    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines[i].trimmed().toLower();

        // Accepte toute ligne contenant 'passerelle'
        if (line.contains("passerelle")) {
            qDebug() << "🔍 Ligne avec 'passerelle' détectée :" << line;

            // Check IP dans cette ligne
            QRegularExpressionMatch match = ipv4Regex.match(line);
            if (match.hasMatch()) {
                ipGateway = match.captured(0);
                break;
            }

            // Sinon regarde jusqu’à 3 lignes suivantes
            for (int j = i + 1; j <= i + 3 && j < lines.size(); ++j) {
                QString nextLine = lines[j].trimmed();
                qDebug() << "👉 Ligne suivante : " << nextLine;

                QRegularExpressionMatch matchNext = ipv4Regex.match(nextLine);
                if (matchNext.hasMatch()) {
                    ipGateway = matchNext.captured(0);
                    break;
                }
            }
        }

        if (!ipGateway.isEmpty()) break;
    }

    if (ipGateway.isEmpty())
        qDebug() << "❌ Gateway non trouvée.";
    else
        qDebug() << "✅ Gateway détectée :" << ipGateway;
}

