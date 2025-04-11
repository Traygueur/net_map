#ifndef MAP_H
#define MAP_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include "QString"
#include <QVector>
#include <QMainWindow>
#include <QScrollArea>
#include <QProcess>
#include <QTime>          
#include <QString>
#include <QStringList>
#include <QCoreApplication>


struct Device {
    std::string type;
    std::string mac_address;
    std::vector<std::string> links;
};

extern std::unordered_map<std::string, std::vector<std::string>> delay;
extern std::vector<std::pair<std::string, float>> sortedIPs;
extern std::map<std::string, std::string> association;


int createMap();
void generateGraphe(const std::unordered_map<std::string, Device>& network_map);
void parseArpTableQt(std::unordered_map<std::string, Device>& network_map);
void detectGateway();

#endif // MAP_H
