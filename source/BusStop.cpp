#include "BusStop.h"

void BusStop::addEdge(Edge* new_edge) {
    edges.push_front(new_edge);
}
