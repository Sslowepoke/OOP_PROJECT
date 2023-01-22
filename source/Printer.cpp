#include "Printer.h"

#include <set>
#include <fstream>


void DefaultStopPrintBehaviour::print(BusStop* stop, std::ostream& output) {
    output << stop->id << " " << stop->name << " [";

    std::set<std::string> line_names;
    std::set<int> important_ids;
    for(Edge* edge : stop->edges) {
        line_names.insert(edge->getLine()->getName());
        BusStop* neighbour = edge->other(stop);
        if(neighbour->is_important()) important_ids.insert(neighbour->getId());
    }
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

void DefaultLinePrintBehaviour::print(BusLine* line, std::ostream& output) {
    output << line->name << " " << line->stops.front()->getName() <<
        "->" << line->stops.back()->getName() << std::endl;
    for(auto stop : line->stops) {
        output << stop->getId() << " " << stop->getName();
        if(stop->is_important()) output << " [!]";
        output << std::endl;
    }
}

Printer::~Printer() {
    delete line_print_behaviour;
    delete stop_print_behaviour;
}

void Printer::printStop(BusStop* stop) {
    std::string file_path = output_path + "stajaliste_" + std::to_string(stop->getId()) + file_extension;
    std::ofstream file(file_path);
    if(file.is_open()) {
        stop_print_behaviour->print(stop, file);
    }
    else
        throw std::runtime_error("Neuspesno otvaranje fajla.");
}

void Printer::printLine(BusLine* line) {
    std::string file_path = output_path + "linija_" + line->getName() + file_extension;
    std::ofstream file(file_path);
    if(file.is_open()) {
        line_print_behaviour->print(line, file);
    }
    else
        throw std::runtime_error("Neuspesno otvaranje fajla.");
}

// void DefaultPathPrintBehaviour::print(const Graph::Path& Path) {
//     int start_id;
//     int end_id;
//     std::string file_path = output_path + "putanja_" + std::to_string(start_id) + 
//         "_" + std::to_string(end_id) + file_extension;
// }