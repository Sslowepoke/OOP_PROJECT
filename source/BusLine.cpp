#include "BusLine.h"

#include <sstream>

BusLine::BusLine(const std::string& name, const std::string& stations) : name(name) {
    std::stringstream s(stations);
    int code;
    while(s >> code) {
        this->stations.push_back(code);
    }
}