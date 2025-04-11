// portsinfo.h
#ifndef PORTSINFO_H
#define PORTSINFO_H

#include <string>
#include "libs/nlohmann/json.hpp"

using json = nlohmann::json;

// Fonction pour charger le fichier JSON une fois
void loadPortsInfo(const std::string& filename);

// Fonction pour récupérer les infos sur un port spécifique
std::string getProtocolForPort(int port);
int getDangerLevelForPort(int port);

// Variable globale pour stocker les données du fichier JSON
extern json portsData;

#endif // PORTSINFO_H
