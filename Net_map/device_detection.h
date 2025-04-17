#ifndef DEVICE_DETECTION_H
#define DEVICE_DETECTION_H

#include <QString>

QString detectType(const QString& hostname, const QString& osName);
QString getColorForType(const QString& type);

#endif // DEVICE_DETECTION_H
#pragma once
