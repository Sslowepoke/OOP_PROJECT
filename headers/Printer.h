#pragma once

#include "BusStop.h"
#include "BusLine.h"
#include <fstream>


class StopPrintBehaviour {
public:
    virtual void print(BusStop* stop, std::ostream& output);

private:

};

class LinePrintBehaviour {
public:
    virtual void print(BusLine* line, std::ostream& output);

private:


};

class Printer {
public:
    Printer(const std::string& file_name, LinePrintBehaviour* line, StopPrintBehaviour* stop)
     : output(file_name), line_print_behaviour(line), stop_print_behaviour(stop) {}

    void printStop(BusStop* stop) {
        stop_print_behaviour->print(stop, output);
    }
    void printLine(BusLine* line) {
        line_print_behaviour->print(line, output);
    }

private:
    std::ofstream output;
    LinePrintBehaviour* line_print_behaviour;
    StopPrintBehaviour* stop_print_behaviour;

};
