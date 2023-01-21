#pragma once

#include <vector>
#include <map>
#include <unordered_map>

#include "BusStop.h"
#include "BusLine.h"
#include "Printer.h"

class Graph {
public:
    Graph() : stops(), important_stops(), lines() {}
    
    // loads bus stations
    void loadStops(const std::string& file_path);
    void loadLines(const std::string& file_path);

    void printStop(int id, const std::string& file_name);
    void printLine(const std::string& name, const std::string& file_name);
    
    void findPath(int start, int end);
    

private:
    std::unordered_map<int, BusStop*> stops; //where key is station id
    std::list<BusStop*> important_stops;
    std::unordered_map<std::string, BusLine*> lines; //where key is line_name
    

    void insertBusLine(const std::string& string);
    void insertBusStop(const std::string& string);

    class PathStrategy {
    public:
        virtual void findPath(BusStop* start, BusStop* end) = 0;
        virtual ~PathStrategy() = default;
    };

    class LeastTransfersPathStrategy : public PathStrategy {
    public:
        LeastTransfersPathStrategy() = default;
        void findPath(BusStop* start, BusStop* end) override;
    private:
        std::vector<Edge*> path;
    };
    class Path {
    public:
        Path(BusStop* start, std::vector<Edge*> edges);
        friend std::ostream& operator<<(std::ostream& os, const Graph::Path& path);
    private:

        std::vector<std::string> lines;
        std::vector<std::list<int>> stop_ids;

    };
    friend std::ostream& operator<<(std::ostream& os, const Graph::Path& path);


};