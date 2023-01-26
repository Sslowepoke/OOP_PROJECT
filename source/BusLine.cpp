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

BusLine::~BusLine() {
    for(auto edge : edges) {
        delete edge;
    }
}

std::list<int> BusLine::travel(BusStop* start, BusStop* end) const{
    std::list<int> path;
    bool on_the_bus = false;
    for(auto stop : stops) {
        if(stop == start || stop == end) on_the_bus = !on_the_bus;
        if(on_the_bus) {
            path.push_back(stop->getId());
        }
    }
    if(path.front() != start->getId()) {
        path.push_back(start->getId());
        path.reverse();
    }
    else if(path.front() == start->getId()) {
        path.push_back(end->getId());
    }
    return path;
}
