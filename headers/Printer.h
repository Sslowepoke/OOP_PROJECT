#pragma once

#include "BusStop.h"
#include "BusLine.h"

class StopPrintBehaviour {
public:
    virtual void print(BusStop* stop, std::ostream& output) = 0;
    virtual ~StopPrintBehaviour() = default;
};

class DefaultStopPrintBehaviour : public StopPrintBehaviour {
public:
    void print(BusStop* stop, std::ostream& output) override;
};

class LinePrintBehaviour {
public:
    virtual void print(BusLine* line, std::ostream& output) = 0;
    virtual ~LinePrintBehaviour() = default;

private:
    
};

class DefaultLinePrintBehaviour : public LinePrintBehaviour {
public:
    void print(BusLine* line, std::ostream& output) override;
};



class Printer {
public:
    Printer(LinePrintBehaviour* line_print_behaviour = new DefaultLinePrintBehaviour(), 
            StopPrintBehaviour* stop_print_behaviour = new DefaultStopPrintBehaviour(), 
            const std::string output_path = "output/", const std::string& file_extension = ".txt")
        : line_print_behaviour(line_print_behaviour), stop_print_behaviour(stop_print_behaviour), 
        output_path(output_path), file_extension(file_extension) {}
    
    ~Printer();

    void printStop(BusStop* stop);
    void printLine(BusLine* line);

private:
    LinePrintBehaviour* line_print_behaviour;
    StopPrintBehaviour* stop_print_behaviour;

    std::string output_path;
    std::string file_extension;

};
