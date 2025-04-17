#include "device_detection.h"
#include <QVector>
#include <QPair>
#include <QRegularExpression>
#include <QMap>

static const QVector<QPair<QRegularExpression, QPair<QString, QString>>> regexTypeMap = {
    // Hostname patterns
    {QRegularExpression("(?i)desktop"), {"Ordinateur", "#0275D8"}},
    {QRegularExpression("(?i)laptop|notebook|macbook"), {"Ordinateur portable", "#5BC0DE"}},

    // OS patterns
    {QRegularExpression("(?i)windows server"), {"Serveur", "#D9534F"}},
    {QRegularExpression("(?i)ubuntu server"), {"Serveur", "#D9534F"}},
    {QRegularExpression("(?i)centos|red hat|rhel"), {"Serveur", "#D9534F"}},
    {QRegularExpression("(?i)linux kernel.*server"), {"Serveur", "#D9534F"}},
    {QRegularExpression("(?i)debian.*server"), {"Serveur", "#D9534F"}},
    {QRegularExpression("(?i)freebsd"), {"Serveur", "#D9534F"}},

    {QRegularExpression("(?i)windows (7|8|10|11)"), {"Ordinateur", "#0275D8"}},
    {QRegularExpression("(?i)macos|apple mac"), {"Ordinateur", "#0275D8"}},
    {QRegularExpression("(?i)ubuntu desktop|fedora"), {"Ordinateur", "#0275D8"}},

    {QRegularExpression("(?i)android"), {"Smartphone/Tablette", "#5CB85C"}},
    {QRegularExpression("(?i)iphone|ipad|ios"), {"Smartphone/Tablette", "#5CB85C"}},

    {QRegularExpression("(?i)vmware|virtualbox|qemu|kvm|hyper-v"), {"Machine virtuelle", "#F0AD4E"}},

    {QRegularExpression("(?i)fortinet|router|switch|firewall|cisco|ubiquiti"), {"Équipement réseau", "#9B59B6"}},

    {QRegularExpression("(?i)printer|hp jetdirect|canon|epson|brother"), {"Imprimante", "#F7DC6F"}},

    {QRegularExpression("(?i)smarttv|chromecast|google nest|xiaomi|sonos|iot"), {"Périphérique IoT", "#A3E4D7"}}
};

QString detectType(const QString& hostname, const QString& osName) {
    // Test sur hostname
    for (const auto& pair : regexTypeMap) {
        if (pair.first.match(hostname).hasMatch()) {
            return pair.second.first;
        }
    }
    // Puis test sur OS
    for (const auto& pair : regexTypeMap) {
        if (pair.first.match(osName).hasMatch()) {
            return pair.second.first;
        }
    }
    return "Inconnu";
}

QString getColorForType(const QString& type) {
    for (const auto& pair : regexTypeMap) {
        if (pair.second.first.compare(type, Qt::CaseInsensitive) == 0) {
            return pair.second.second;
        }
    }
    return "#FFFFFF"; // blanc par défaut
}
