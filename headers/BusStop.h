#pragma once

#include <string>
#include <list>
#include <unordered_map>

#include "Edge.h"


class BusStop {
public:
    BusStop(int id, const std::string& name, bool is_important) : id(id), name(name), is_important(is_important) {}
    void addEdge(Edge* new_edge);

    int getId() const { return id; }
    const std::string& getName() const { return name; } 
    std::list<const std::string&> getLineNames() const;
    std::list<int> getImportantStops() const;
    


private:
    int id;
    std::string name;
    bool is_important;
    std::list<Edge*> edges;
    // std::unordered_map<BusLine*, BusStop*> neighbours;
};