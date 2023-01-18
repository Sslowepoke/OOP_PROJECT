#pragma once

#include "BusLine.h"
#include "BusStop.h"

class BusStop;
class BusLine;
class Edge {
public:
    Edge(BusStop* first_stop, BusStop* second_stop, BusLine* line);

    
    const BusLine* getLine() const { return line; }
    BusStop* other(const BusStop* first) const {  return first == first_stop? second_stop : first_stop; }

private:
    BusStop *first_stop, *second_stop;
    bool travelled = false;
    BusLine* line;
};