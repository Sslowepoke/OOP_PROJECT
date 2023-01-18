#pragma once

#include <vector>
#include <map>
#include <unordered_map>

#include "BusStop.h"
#include "BusLine.h"
#include "Printer.h"

class Graph {
public:
    Graph() : stops(), important_stops(), lines() {}
    
    // loads bus stations
    void loadStops(const std::string& file_path);
    void loadLines(const std::string& file_path);

    void printStop(int id, const std::string& file_name);
    void printLine(const std::string& name, const std::string& file_name);
    

    



private:
    std::unordered_map<int, BusStop*> stops; //where key is station id
    std::list<BusStop*> important_stops;
    std::unordered_map<std::string, BusLine*> lines; //where key is line_name
    

    void insertBusLine(const std::string& string);
    void insertBusStop(const std::string& string);

    // std::unordered_map<int
};