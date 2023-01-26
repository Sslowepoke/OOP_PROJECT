#pragma once

#include <string>
#include <list>
#include <unordered_map>

#include "Edge.h"

class Edge;
class BusStop {
public:
    BusStop(int id, const std::string& name, bool important) 
    : id(id), name(name), important(important), visited(false) {}
    
    void addEdge(Edge* new_edge);

    int getId() const { return id; }
    const std::string& getName() const { return name; } 
    bool is_important() const { return important; }
    const std::list<Edge*>& getEdges() const { return edges; }
    bool was_visited() const { return visited; }
    void visit() { visited = true; }
    void unvisit() { visited = false; }

private:
    int id;
    std::string name;
    bool important;
    std::list<Edge*> edges;
    bool visited;
    friend class StopPrintBehaviour;
};
