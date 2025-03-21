#include "gui.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include "map.h"
#include <fstream> 
#include <direct.h>
#include <thread>
#include <chrono>



int createMap() {
	std::unordered_map<std::string, Device> network_map;

	network_map["192.168.1.1"] = { "Router", "AA:BB:CC:DD:EE:FF", {"192.168.1.2", "192.168.1.3"} };
	network_map["192.168.1.2"] = { "Switch", "11:22:33:44:55:66", {"192.168.1.1", "192.168.1.4"} };
	network_map["192.168.1.3"] = { "PC", "77:88:99:AA:BB:CC", {"192.168.1.1"} };

	for (const std::pair<const std::string, Device>& entry : network_map) {

		std::string ip = entry.first;
		Device device = entry.second;
		std::vector<std::string> links = device.links;

		GUI::AppendTextToConsole("IP: " + ip + " (" + device.type + ") - MAC: " + device.mac_address + "\n");
		GUI::AppendTextToConsole("Connecte a: ");
		for (const auto& link : links) {
			GUI::AppendTextToConsole(link + " ");
		};
		GUI::AppendTextToConsole("\n");
	};

	generateGraphe(network_map);
};



void generateGraphe(const std::unordered_map<std::string, Device>& network_map) {
	std::ofstream file("network.dot");
	file << "graph Network {\n";
	for (const auto& entry : network_map) {
		std::string ip = entry.first;
		Device device = entry.second;

		for (const auto& link : device.links) {
			file << "  \"" << ip << "\" -- \"" << link << "\";\n";
		}
	}
	file << "}\n"; // Fin du graphe
	file.close();  // Ferme le fichier

	GUI::AppendTextToConsole("Fichier DOT généré: network.dot\n");

	int result = system("dot -Tpng network.dot -o network.bmp > dot_log.txt 2>&1");

	if (result != 0) {
		GUI::AppendTextToConsole("❌ Erreur : dot a échoué ! Consulte dot_log.txt\n");
	}
	GUI::AppendTextToConsole("Image affiché\n");
};