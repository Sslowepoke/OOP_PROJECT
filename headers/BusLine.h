#pragma once

#include <string>
#include <list>
#include <vector>

#include "BusStop.h"
#include "Edge.h"
class BusStop;
class Edge;

class BusLine{
public:
    BusLine(const std::string& name, const std::list<BusStop*> stops);

    const std::string& getName() const { return name; }
    std::list<int> travel(BusStop* start, BusStop* end) const;

private:
    std::string name;
    std::list<BusStop*> stops;
    std::list<Edge*> edges;

    friend class LinePrintBehaviour;
};