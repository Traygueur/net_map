// portsinfo.cpp
#include "portsinfo.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

// Déclaration de la variable globale
json portsData;

void loadPortsInfo(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    file >> portsData;  // Charger le fichier JSON dans la variable globale
}

std::string getProtocolForPort(int port) {
    if (portsData.contains(std::to_string(port))) {
        return portsData[std::to_string(port)]["protocol"];
    }
    return "Unknown";
}

int getDangerLevelForPort(int port) {
    if (portsData.contains(std::to_string(port))) {
        return portsData[std::to_string(port)]["danger_level"];
    }
    return -1;  // Retourne -1 si le port n'est pas trouvé
}