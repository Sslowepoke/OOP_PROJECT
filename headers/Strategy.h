#pragma once

#include "BusStop.h"
#include <map>
#include <vector>

class PathStrategy {
public:
    PathStrategy() = default;
    virtual void findPath(BusStop* start, BusStop* end) = 0;
private:

};

// class DefaultPathStrategy : public PathStrategy {
// public:
//     void findPath(BusStop* start, BusStop* end) override;

// private:

// };

class LeastTransfersPathStrategy : public PathStrategy {
public:
    LeastTransfersPathStrategy() = default;
    void findPath(BusStop* start, BusStop* end) override;
private:
    void constructPath(BusStop* start, BusStop* end);
    std::vector<Edge*> path;
};

class Path {
public:
    Path(BusStop* start, std::vector<Edge*> edges);
    friend std::ostream& operator<<(std::ostream& os, Path& path);
private:

    std::vector<std::string> lines;
    std::vector<std::list<int>> stop_ids;

};