#pragma once

#include <string>
#include <list>

#include "BusStop.h"

class BusLine{
public:
    BusLine(const std::string& name, BusStop* first_stop)
        : name(name), first_stop(first_stop) {}

    const std::string& getName() const { return name; }

private:
    std::string name;
    BusStop *first_stop;
};