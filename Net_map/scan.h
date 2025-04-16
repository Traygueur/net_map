// scan.h
#ifndef SCAN_H
#define SCAN_H

#include <string>
#include "libs/nlohmann/json.hpp"

void startScan(QProcess * process, QString ipRange);

#endif // SCAN_H
