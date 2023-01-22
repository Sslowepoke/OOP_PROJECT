#pragma once

#include <vector>
#include <map>
#include <unordered_map>

#include "BusStop.h"
#include "BusLine.h"
#include "Printer.h"


class Graph {
private:
    class PathStrategy;
public:
    Graph(PathStrategy* path_strategy = new DefaultPathStrategy(), Printer* printer = new Printer()) 
    : stops(), important_stops(), lines(), path_strategy(path_strategy), printer(printer) {}
    ~Graph();
    // loads bus stations
    void loadStops(const std::string& file_path);
    void loadLines(const std::string& file_path);

    void printStop(int id);
    void printLine(const std::string& name);
    void printPath();
    
    void findPath(int start, int end);

    
    

private:
    std::unordered_map<int, BusStop*> stops; //where key is station id
    std::list<BusStop*> important_stops;
    std::unordered_map<std::string, BusLine*> lines; //where key is line_name
    PathStrategy* path_strategy;
    Printer* printer;
    class Path;
    Path* path = nullptr;

    void insertBusLine(const std::string& string);
    void insertBusStop(const std::string& string);

    class Path {
    public:
        Path(BusStop* start, std::vector<Edge*> edges);
        friend std::ostream& operator<<(std::ostream& os, const Graph::Path& path);
        int getStartId() const;
        int getEndId() const;
    private:
        
        std::vector<std::string> lines;
        std::vector<std::list<int>> stop_ids;
    };

    class PathStrategy {
    public:
        virtual Path* findPath(BusStop* start, BusStop* end) = 0;
        virtual ~PathStrategy() = default;
        static const std::string default_file_path;
    };

    class LeastTransfersPathStrategy : public PathStrategy {
    public:
        Path* findPath(BusStop* start, BusStop* end) override;
    private:
        // std::vector<Edge*> path;
    };

    class DefaultPathStrategy : public PathStrategy {
    public:
        Path* findPath(BusStop* start, BusStop* end) override;
    };

    friend std::ostream& operator<<(std::ostream& os, const Graph::Path& path);


};