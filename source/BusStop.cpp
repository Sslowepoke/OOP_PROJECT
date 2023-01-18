#include "BusStop.h"

void BusStop::addEdge(Edge* new_edge) {
    edges.push_front(new_edge);
}

std::list<const std::string&> BusStop::getLineNames() const {
    std::list<const std::string&> line_names;
    for(Edge* edge : edges) {
        line_names.push_front(edge->getLine()->getName());
    }
    line_names.sort();
    return line_names;
}

std::list<int> BusStop::getImportantStops() const {
    
}