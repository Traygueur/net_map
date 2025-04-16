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
#include <unordered_map>
#include <algorithm>
#include <limits>


#include "globals.h"


QString ipGateway, ip, mask;
QString ipGatewayLocal;
std::unordered_map<std::string, std::vector<std::string>> delay;
std::map<std::string, std::string> association;
std::vector<std::string> sortedSwitches;

int switchSorted() {
    sortedSwitches.clear();
    std::vector<std::pair<std::string, float>> sortedIPs;
    association.clear();
    for (std::unordered_map<std::string, std::vector<std::string>>::const_iterator it = delay.begin(); it != delay.end(); ++it) {
        if (!it->second.empty()) {
            // Convertir la réponse en float
            float time = std::stof(it->second[1]);
            sortedIPs.push_back(std::make_pair(it->first, time));
        }
    }

    // Trier selon le temps de réponse croissant
    std::sort(sortedIPs.begin(), sortedIPs.end(),
        [](const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
            return a.second < b.second;
        });

    // Déterminer l'IP du premier switch rencontré dans la liste triée
    std::string firstSwitch = "";
    for (std::vector<std::pair<std::string, float>>::const_iterator it = sortedIPs.begin();
        it != sortedIPs.end(); ++it) {
        // Vérifier si cette IP est un switch dans ipData
        if (!delay[it->first].empty() && delay[it->first][0] == "switch") {
            firstSwitch = it->first;
            break;
        }
    }
    if (firstSwitch == "") {
        std::cout << "Aucun switch trouvé dans la liste triée." << std::endl;
        return 1;
    }
    // Variable pour garder le switch courant (celui le plus proche juste avant dans la liste)
    std::string currentSwitch = "";
    // Parcourir la liste et associer chaque IP non-switch avec le switch le plus proche
    for (std::vector<std::pair<std::string, float>>::const_iterator it = sortedIPs.begin();
        it != sortedIPs.end(); ++it) {
        const std::string& ip = it->first;
        // Si c'est un switch, on ne fait pas d'association et on met à jour currentSwitch
        if (!delay[ip].empty() && delay[ip][0] == "switch") {
            currentSwitch = ip;
            sortedSwitches.push_back(ip);
        }
        else {  // Pour les autres types
            if (currentSwitch == "") {
                // Aucun switch précédent, associer à firstSwitch
                if (delay[ip][4] == "2") {
                    association[ip] = firstSwitch;
                }
            }
            else {
                if (delay[ip][4] == "2") {
                    association[ip] = currentSwitch;
                }
            }
        }
    }

    return 0;
}


int createMap(std::string path) {
    detectGateway();
    getLocalSubnet();
    localInfoInXML();
    QString xmlPath;
    std::unordered_map<std::string, Device> network_map;
    if (path == "Null") {
        xmlPath = exePath + "/scan_network.xml";
    }
    else {
        xmlPath = QString::fromStdString(path);
    }

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
    QDomNodeList localNodes = doc.documentElement().elementsByTagName("local");
    QDomElement local = localNodes.at(0).toElement();
    QString mask = local.attribute("subnetMask");
    QString gateway = local.attribute("gateway");
    QString localIp = local.attribute("ip");

    auto ipToInt = [](const QString& ipStr) -> uint32_t {
        QStringList parts = ipStr.split('.');
        if (parts.size() != 4) return 0;
        return (parts[0].toUInt() << 24) | (parts[1].toUInt() << 16) | (parts[2].toUInt() << 8) | parts[3].toUInt();
        };

    uint32_t localIPInt = ipToInt(localIp);
    uint32_t maskInt = ipToInt(mask);
    uint32_t localSubnet = localIPInt & maskInt;

    for (int i = 0; i < hosts.count(); ++i) {
        QDomElement host = hosts.at(i).toElement();

        QString ip, mac, osType, accuracy, vendor, type, time;

        QDomNodeList times = host.elementsByTagName("times");
        for (int j = 0; j < times.count(); ++j) {
            QDomElement timeElement = times.at(j).toElement();
            time = timeElement.attribute("srtt");
        }

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
                QDomElement osClass = osMatch.firstChildElement("osclass");
                type = osClass.attribute("type");
            }
        }

        ipGatewayLocal = gateway;

        uint32_t currentIPInt = ipToInt(ip);
        uint32_t currentSubnet = currentIPInt & maskInt;
        int id = (currentSubnet == localSubnet) ? 2 : 1;
        delay[ip.toStdString()] = { type.toStdString(), time.toStdString(), osType.toStdString(), mac.toStdString(), QString::number(id).toStdString() };


    }


    switchSorted();

    for (const auto& entry : delay) {
        const std::string& ip = entry.first;
        const std::string& type = entry.second[0];
        const std::string& ostype = entry.second[2];
        const std::string& mac = entry.second[3];
        const std::string& id = entry.second[4];

        if (ip == gateway) {
            network_map[ip] = { ostype, mac, {}, id };
        }
        else if (association[ip].empty()) {
            network_map[ip] = { ostype, mac, {}, id };
        }
        else if (id == "2") {
            network_map[ip] = { ostype, mac, {association[ip]}, id };
        }
        else {
            network_map[ip] = { ostype, mac, { }, id };
        }
    }

    // Génération du graphe
    generateGraphe(network_map);

    return 0;
};

void generateGraphe(const std::unordered_map<std::string, Device>& network_map) {
    QString dotPath = exePath + "/network.dot";
    std::ofstream file(dotPath.toStdString());
    file << "graph Network {\n";
    file << R"( layout=twopi;
                bgcolor="#2E2E2E";
                overlap=scale;
                splines=true;
                sep="+0.5";
                nodesep=0.3;
                ranksep=0.4;

                node [style=filled, shape=ellipse, fillcolor="white", fontcolor="black", color="black", fontsize=14];
                edge [color="white", penwidth=1.2, len=0.4];

                "SWITCH_LOCAL" [label="Switch Virtuel Local"]
                "Passerelle" [label=Passerelle])";

    file << "  \"Passerelle\" -- \"" << ipGatewayLocal.toStdString() << "\";\n";
    file << "  \"SWITCH_LOCAL\" -- \"" << ipGatewayLocal.toStdString() << "\";\n";
    for (const auto& entry : network_map) {
        std::string ip = entry.first;
        Device device = entry.second;
        bool isSwitch = std::find(sortedSwitches.begin(), sortedSwitches.end(), ip) != sortedSwitches.end();
        if (ip == ipGatewayLocal)
        {
            file << "  \"" << ip << "\" [label=\"" << ip << "\\n" << device.type << "\", root=true];\n";
        }
        else
        {
            file << "  \"" << ip << "\" [label=\"" << ip << "\\n" << device.type << "\"];\n";
        }
        if (device.id == "2" && isSwitch) {
            file << "  \"SWITCH_LOCAL\" -- \"" << ip << "\";\n";
        }
        else if (device.id == "1") {
            file << "  \"Passerelle\" -- \"" << ip << "\";\n";
        }
        for (const auto& link : device.links) {
            file << "  \"" << ip << "\" -- \"" << link << "\";\n";
        }
    }
    file << "}\n"; // Fin du graphe
    file.close();  // Ferme le fichier

    QProcess process;
    QString program = exePath + "/Graphviz/bin/dot.exe";  // Chemin absolu
    QStringList arguments = { "-Ktwopi", "-Tsvg", "-Gdpi=72", "network.dot", "-o", "network.svg" };


    /*process.setWorkingDirectory(exePath);
    process.start(program, arguments);
    process.waitForFinished();*/

    process.setWorkingDirectory(exePath);

    // Log du programme et des arguments
    qDebug() << "Programme lancé :" << program;
    qDebug() << "Arguments :" << arguments;
    qDebug() << "Répertoire de travail :" << exePath;

    process.start(program, arguments);

    if (!process.waitForStarted()) {
        qDebug() << "Erreur : le processus n'a pas démarré.";
        qDebug() << "Erreur détaillée :" << process.errorString();
        return;
    }

    if (!process.waitForFinished()) {
        qDebug() << "Erreur : le processus ne s'est pas terminé correctement.";
        qDebug() << "Erreur détaillée :" << process.errorString();
    }
    else {
        qDebug() << "Processus terminé avec le code :" << process.exitCode();
        qDebug() << "Sortie standard :" << process.readAllStandardOutput();
        qDebug() << "Erreur standard :" << process.readAllStandardError();
    }
};

void detectGateway() {
    QProcess process;
    process.start("ipconfig");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    QRegularExpression ipv4Regex(R"(\b\d{1,3}(?:\.\d{1,3}){3}\b)");

    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines[i].trimmed().toLower();

        // Accepte toute ligne contenant 'passerelle'
        if (line.contains("passerelle")) {
            // Check IP dans cette ligne
            QRegularExpressionMatch match = ipv4Regex.match(line);
            if (match.hasMatch()) {
                ipGateway = match.captured(0);
                break;
            }

            // Sinon regarde jusqu’à 3 lignes suivantes
            for (int j = i + 1; j <= i + 3 && j < lines.size(); ++j) {
                QString nextLine = lines[j].trimmed();

                QRegularExpressionMatch matchNext = ipv4Regex.match(nextLine);
                if (matchNext.hasMatch()) {
                    ipGateway = matchNext.captured(0);
                    break;
                }
            }
        }

        if (!ipGateway.isEmpty()) break;
    }
}

QString getLocalSubnet() {
    QProcess process;
    process.start("ipconfig");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    QRegularExpression ipv4Regex(R"(\b\d{1,3}(?:\.\d{1,3}){3}\b)");

    QString currentIp, currentMask;
    bool isWiFiBlock = false;

    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines[i].simplified();

        // Détecte un nouveau bloc d'interface
        if (line.startsWith("Carte") || line.contains("adapter", Qt::CaseInsensitive)) {
            isWiFiBlock = line.contains("wi-fi", Qt::CaseInsensitive);  // Active uniquement si c'est Wi-Fi
        }

        if (isWiFiBlock) {
            // Récupère l'IP
            if (line.contains("ipv4", Qt::CaseInsensitive)) {
                QRegularExpressionMatch match = ipv4Regex.match(line);
                if (match.hasMatch()) {
                    currentIp = match.captured(0);
                }
            }

            // Récupère le masque
            if (!currentIp.isEmpty() && (line.contains("masque", Qt::CaseInsensitive) || line.contains("subnet", Qt::CaseInsensitive))) {
                QRegularExpressionMatch maskMatch = ipv4Regex.match(line);
                if (maskMatch.hasMatch()) {
                    currentMask = maskMatch.captured(0);
                    break;  // On a trouvé les deux dans le bon bloc
                }
            }
        }
    }

    if (!currentIp.isEmpty() && !currentMask.isEmpty()) {
        ip = currentIp;
        mask = currentMask;

        // Calcul du sous-réseau
        QStringList ipParts = ip.split('.');
        QStringList maskParts = mask.split('.');
        QStringList subnetParts;

        for (int i = 0; i < 4; ++i) {
            subnetParts << QString::number(ipParts[i].toInt() & maskParts[i].toInt());
        }

        return subnetParts.join('.');
    }

    return "";
}


void localInfoInXML() {
    QString exePath = QCoreApplication::applicationDirPath();
    QString xmlPath = exePath + "/scan_network.xml";

    // 1. Lire le fichier
    QFile readFile(xmlPath);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QString xmlContent = readFile.readAll();
    readFile.close();

    QDomDocument doc;
    if (!doc.setContent(xmlContent)) {
        return;
    }

    // 2. Vérifier si <local> existe déjà
    QDomNodeList existingLocals = doc.documentElement().elementsByTagName("local");
    if (!existingLocals.isEmpty()) {
        return;
    }

    // 3. Ajouter la balise <local>
    QDomElement local = doc.createElement("local");
    local.setAttribute("ip", ip);
    local.setAttribute("subnetMask", mask);
    local.setAttribute("gateway", ipGateway);
    doc.documentElement().appendChild(local);

    // 4. Réécriture dans le fichier
    QFile writeFile(xmlPath);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        return;
    }

    QTextStream out(&writeFile);
    out << doc.toString(4);
    writeFile.close();
}