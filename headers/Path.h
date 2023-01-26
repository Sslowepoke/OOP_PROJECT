#pragma once

#include "BusStop.h"
#include <iostream>
#include <vector>

class Path {
public:
    Path(BusStop* start, std::vector<Edge*> edges);
    Path() : lines(), stop_ids() {}
    
    Path& operator+=(const Path& rhs);
    friend Path operator+(Path lhs, const Path& rhs) {
        lhs += rhs;
        return lhs;
    }

    bool goesThrough(BusStop* stop);
    friend std::ostream& operator<<(std::ostream& os, const Path& path);
    int getStartId() const;
    int getEndId() const;
private:
    std::vector<std::string> lines;
    std::vector<std::list<int>> stop_ids;
};
