#include "Edge.h"


Edge::Edge(BusStop* first_stop, BusStop* second_stop, BusLine* line):
first_stop(first_stop), second_stop(second_stop), line(line) {
    first_stop->addEdge(this);
    second_stop->addEdge(this);
}