#include "Printer.h"

#include <set>
// #include <fstream>



void StopPrintBehaviour::print(BusStop* stop, std::ostream& output) {
    output << stop->id << " " << stop->name << " [";

    std::set<std::string> line_names;
    std::set<int> important_ids;
    for(Edge* edge : stop->edges) {
        line_names.insert(edge->getLine()->getName());
        // std::string line_name = edge->getLine()->getName();
        BusStop* neighbour = edge->other(stop);
        if(neighbour->is_important()) important_ids.insert(neighbour->getId());
    }
    // line_names.sort();
    // important_ids.sort();
    for(auto line_name : line_names) {
        output << line_name << " ";
    }
    output << "] {! ";
    for(auto id : important_ids) {
        output << id << " " ;
    }
    output << "!}" << std::endl;
}
// sifra naziv [oznake_svih_linija] {! oznake_vaznih_stajalista !}

void LinePrintBehaviour::print(BusLine* line, std::ostream& output) {
    output << line->name << " " << line->stops.front()->getName() <<
        "->" << line->stops.back()->getName() << std::endl;
    for(auto stop : line->stops) {
        output << stop->getId() << " " << stop->getName();
        if(stop->is_important()) output << " [!]";
        output << std::endl;
    }
}