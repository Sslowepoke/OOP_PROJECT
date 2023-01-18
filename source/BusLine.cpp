#include "BusLine.h"
#include "Edge.h"
#include <sstream>

BusLine::BusLine(const std::string& name, const std::list<BusStop*> stops) : name(name), stops(stops) {
    for(auto i = this->stops.begin(); i != this->stops.end(); ++i) {
        auto j = i;
        ++j;
        for(; j != this->stops.end(); ++j) {
            edges.push_back(new Edge(*i, *j, this));
        }
    }

}