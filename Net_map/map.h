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



int createMap();
void generateGraphe(const std::unordered_map<std::string, Device>& network_map);
void parseArpTableQt(std::unordered_map<std::string, Device>& network_map);

#endif // MAP_H
