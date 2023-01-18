#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>

void Graph::loadStations(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    try{
        if(file.is_open()) {
            bool important;
            std::string name;
            int code;
            while(getline(file, line, '\n')) {
                size_t index1 = line.find_first_of(' ');
                size_t index2 = line.find("[!]");
                if(index2 == std::string::npos){
                    index2 = line.find_last_of("\n\r");
                    important = false;
                }
                else
                    important = true;

                code = stoi(line);
                name = line.substr(index1+1, index2);
                stations.insert({code, new BusStation(code, name, important)});
            }
        }
    }
    catch(std::exception& e) {

    }
}

void Graph::loadLines(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    try{
        if(file.is_open()) {
            bool important;
            std::string name;
            int code;
            while(getline(file, line, '\n')) {
                size_t index1 = line.find_first_of(' ');
                size_t index2 = line.find("[!]");
                if(index2 == std::string::npos){
                    index2 = line.find_last_of("\n\r");
                    important = false;
                }
                else
                    important = true;

                code = stoi(line);
                name = line.substr(index1+1, index2);
                // stations.push_back(new BusStation(code, name, important));
            }
        }
    }
    catch(std::exception& e) {

    }
}