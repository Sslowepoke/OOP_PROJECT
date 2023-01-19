#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void Graph::loadStops(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    try{
        if(file.is_open()) {
            while(getline(file, line, '\n')) {
                insertBusStop(line);
            }
        }
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Graph::loadLines(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    try{
        if(file.is_open()) {
            std::string name;
            while(getline(file, line, '\n')) {
                insertBusLine(line);
            }
        }
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Graph::insertBusLine(const std::string& string) {
    size_t index1 = string.find_first_of(' ');
    std::string name = string.substr(0, index1);
    // std::string new_string = string.substr(index1 + 1);
    std::stringstream ss(string.substr(index1 + 1));
    int temp_id;
    std::list<BusStop*> line_stops;
    while(ss >> temp_id) {
        line_stops.push_back(stops[temp_id]);
    }
    BusLine* new_line = new BusLine(name, line_stops);
    lines.insert({name, new_line});
}
 
void Graph::insertBusStop(const std::string& string) {
    bool important;
    std::string name;
    int id;

    size_t index1 = string.find_first_of(' ');
    size_t index2 = string.find("[!]");
    if(index2 == std::string::npos){
        index2 = string.find_first_of("\n\r");
        important = false;
    }
    else
        important = true;
        index2--;

    id = stoi(string);
    name = string.substr(index1+1, index2 - index1 - 1);

    BusStop* new_stop = new BusStop(id, name, important);

    stops.insert({id, new_stop});

    if(important) 
        important_stops.push_front(new_stop);
}

void Graph::printStop(int id, const std::string& file_name) {
    Printer p(file_name, new LinePrintBehaviour(), new StopPrintBehaviour());
    p.printStop(stops[id]);
}

void Graph::printLine(const std::string& name, const std::string& file_name) {
    Printer p(file_name, new LinePrintBehaviour(), new StopPrintBehaviour());
    p.printLine(lines[name]);
}

void Graph::findPath(int start, int end) {
    LeastTransfersPathStrategy s = LeastTransfersPathStrategy();
    s.findPath(stops[start], stops[end]);

}