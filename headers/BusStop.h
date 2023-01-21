#pragma once

#include <string>
#include <list>
#include <unordered_map>

#include "Edge.h"

class Edge;
class BusStop {
public:
    BusStop(int id, const std::string& name, bool important) : id(id), name(name), important(important) {}
    void addEdge(Edge* new_edge);

    int getId() const { return id; }
    const std::string& getName() const { return name; } 
    // std::list<const std::string&> getLineNames() const;
    // std::list<int> getNeighbourIds() const;
    bool is_important() const { return important; }
    const std::list<Edge*>& getEdges() const { return edges; }

    


private:
    int id;
    std::string name;
    bool important;
    std::list<Edge*> edges;
    // std::unordered_map<BusLine*, BusStop*> neighbours;
    friend class StopPrintBehaviour;
    // friend class LeastTransfersPathStrategy;
};