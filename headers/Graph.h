#pragma once

#include <vector>
#include <map>
#include <unordered_map>

#include "BusStation.h"
#include "BusLine.h"


class Graph {
public:
    
    // loads bus stations
    void loadStations(const std::string& file_path);
    void loadLines(const std::string& file_path);



private:
    std::unordered_map<int, BusStation*> stations; //where key is station id
    std::list<BusStation*> important_stations;
    std::unordered_map<std::string, BusLine*> lines; //where key is line_name
};