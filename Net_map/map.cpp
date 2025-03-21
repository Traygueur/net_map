#include "map.h"
#include <fstream>
#include <QProcess>


int createMap() {
    std::unordered_map<std::string, Device> network_map;

    network_map["192.168.1.1"] = { "Router", "AA:BB:CC:DD:EE:FF", {"192.168.1.2", "192.168.1.3"} };
    network_map["192.168.1.2"] = { "Switch", "11:22:33:44:55:66", {"192.168.1.1", "192.168.1.4", "192.168.1.5", "192.168.1.6", "192.168.1.7"} };
    network_map["192.168.1.3"] = { "PC", "77:88:99:AA:BB:CC", {"192.168.1.1"} };
    network_map["192.168.1.4"] = { "PC", "77:88:99:AA:BB:CC", {"192.168.1.2"} };
    network_map["192.168.1.5"] = { "PC", "77:88:99:AA:BB:CC", {"192.168.1.2"} };
    network_map["192.168.1.6"] = { "PC", "77:88:99:AA:BB:CC", {"192.168.1.2"} };
    network_map["192.168.1.7"] = { "PC", "77:88:99:AA:BB:CC", {"192.168.1.2"} };


    for (const std::pair<const std::string, Device>& entry : network_map) {

        std::string ip = entry.first;
        Device device = entry.second;
        std::vector<std::string> links = device.links;
    };
    generateGraphe(network_map);
    return 0;
};

void generateGraphe(const std::unordered_map<std::string, Device>& network_map) {
    std::ofstream file("network.dot");
    file << "graph Network {\n";
    file << R"(bgcolor="#2E2E2E"; node [style=filled, fillcolor="white", fontcolor="black", color="black"]; edge [color="white"]; dpi=72; atio=expand; )";
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

    process.setWorkingDirectory("C:\\Users\\coulo\\Documents\\netmap_qt\\build\\Desktop_Qt_6_8_2_MinGW_64_bit-Release");
    process.start(program, arguments);
    process.waitForFinished();

};
