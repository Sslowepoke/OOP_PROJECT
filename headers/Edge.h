#pragma once

#include "BusLine.h"
#include "BusStop.h"

class Edge {
public:
    Edge(BusStop* first_stop, BusStop* second_stop, BusLine* line):
        first_stop(first_stop), second_stop(second_stop), line(line) {}
    
    const BusLine* getLine() const { return line; }

private:
    BusStop *first_stop, *second_stop;
    bool travelled = false;
    BusLine* line;
};