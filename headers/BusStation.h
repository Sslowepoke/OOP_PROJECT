#pragma once

#include <string>
#include <unordered_map>

#include "Edge.h"


class BusStation {
public:
    BusStation(int id, const std::string& name, bool is_important) : id(id), name(name), is_important(is_important) {}

private:
    int id;
    std::string name;
    bool is_important;
    // std::map<std::string, Edge*> edges; //where key is line_name
    std::unordered_map<std::string, BusStation*> neighbors; //where key is line_name\
    // ordered map ali tako da su leksikografski poredjane linje pa mogu samo da ih ispisem? veroatno ne.
};