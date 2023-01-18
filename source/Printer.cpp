#include "Printer.h"

// #include <fstream>



void StopPrintBehaviour::print(BusStop* stop, std::ostream& output) {
    output << stop->getId() << stop->getName();
    std::list<const std::string&> line_names = stop->getLineNames();
    output << " [";
    for(auto line_name : line_names) {
        output << line_name << " " ;
    }
    output << "] {! ";
    std::list<int> important_stops = stop->getImportantStops();

}
// sifra naziv [oznake_svih_linija] {! oznake_vaznih_stajalista !}
