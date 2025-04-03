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

		network_map[ip.toStdString()] = {osType.toStdString(), mac.toStdString(), {}};
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
    file << R"(bgcolor="#2E2E2E"; node [style=filled, fillcolor="white", fontcolor="black", color="black"]; edge [color="white"] ;ratio=expand; )";
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
    QStringList arguments = { "-Tpng", "network.dot", "-o", "network.bmp" };


    process.setWorkingDirectory(exePath);
    process.start(program, arguments);
    process.waitForFinished();

};


