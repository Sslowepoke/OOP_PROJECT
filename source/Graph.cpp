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
            bool important;
            std::string name;
            int id;
            while(getline(file, line, '\n')) {
                size_t index1 = line.find_first_of(' ');
                size_t index2 = line.find("[!]");
                if(index2 == std::string::npos){
                    index2 = line.find_last_of("\n\r");
                    important = false;
                }
                else
                    important = true;

                id = stoi(line);
                name = line.substr(index1+1, index2);

                BusStop* new_stop = new BusStop(id, name, important);

                stops.insert({id, new_stop});
                if(important) 
                    important_stops.push_front(new_stop);
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
                size_t index1 = line.find_first_of(' ');
                name = line.substr(0, index1);
                line = line.substr(index1 + 1);
                std::stringstream ss(line);

                int prev, next;

                ss >> prev;
                BusLine* new_line = new BusLine(name, stops[prev]);

                while(ss >> next) {
                    Edge* new_edge = new Edge(stops[prev], stops[next], new_line);
                    
                    stops[prev]->addEdge(new_edge);
                    stops[next]->addEdge(new_edge);
                    
                    prev = next;
                }
            }
        }
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

