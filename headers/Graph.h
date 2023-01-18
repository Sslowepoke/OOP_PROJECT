#pragma once

#include <vector>
#include <map>
#include <unordered_map>

#include "BusStop.h"
#include "BusLine.h"


class Graph {
public:
    
    // loads bus stations
    void loadStops(const std::string& file_path);
    void loadLines(const std::string& file_path);

    



private:
    std::unordered_map<int, BusStop*> stops; //where key is station id
    std::list<BusStop*> important_stops;
    std::unordered_map<std::string, BusLine*> lines; //where key is line_name

    // std::unordered_map<int
};