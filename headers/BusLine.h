#pragma once

#include <string>
#include <list>

#include "BusStation.h"

class BusLine{
public:
    BusLine(const std::string& name, const std::string& stations);

private:
    std::string name;
    BusStation* first_station, last_station;
};