#ifndef MAP_H 
#define MAP_H


#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>  



struct Device {
    std::string type;
    std::string mac_address;
    std::vector<std::string> links;
};

int createMap();
void generateGraphe(const std::unordered_map<std::string, Device>& network_map);

#endif

