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
#include <QRegularExpression> // Ajout de l'inclusion nécessaire



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
    std::unordered_map<std::string, Device> network_map;

    network_map["192.168.1.1"] = { "Router", "AA:BB:CC:DD:EE:FF", {"192.168.1.2", "192.168.1.3"} };
    network_map["192.168.1.2"] = { "Switch", "11:22:33:44:55:66", {"192.168.1.1", "192.168.1.4"} };
    network_map["192.168.1.3"] = { "PC", "77:88:99:AA:BB:CC", {"192.168.1.1"} };
    // Génération du graphe
    generateGraphe(network_map);

    return 0;
};

void generateGraphe(const std::unordered_map<std::string, Device>& network_map) {
    std::ofstream file("network.dot");
    file << "graph Network {\n";
    file << R"(bgcolor="#2E2E2E"; node [style=filled, fillcolor="white", fontcolor="black", color="black"]; edge [color="white"]; dpi=72; ratio=expand; )";
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
    QString program = "C:\\Program Files (x86)\\Graphviz\\bin\\dot.exe";  // Chemin absolu
    QStringList arguments = { "-Tpng", "network.dot", "-o", "network.bmp" };

    process.setWorkingDirectory("C:\\Users\\coulo\\Documents\\ESAIP\\PROJECT_APPLICATIF_C++\\net_map\\Net_map");
    process.start(program, arguments);
    process.waitForFinished();

};


