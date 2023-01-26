#pragma once

#include <vector>
#include <map>
#include <unordered_map>

#include "BusStop.h"
#include "BusLine.h"
#include "Printer.h"
#include "Path.h"


class Graph {
public:
    Graph() { path_strategy = path_strategies.front(); }
    ~Graph();

    void loadStops(const std::string& file_path);
    void loadLines(const std::string& file_path);
    void clearLines();
    void clearStops();

    void printStop(int id);
    void printLine(const std::string& name);
    
    void findPath(int start, int end);
    void printPath();

    void changePathStrategy();

    std::list<BusStop*>& getImportantStops() { return important_stops; }

private:
    std::unordered_map<int, BusStop*> stops; //where key is station id
    std::list<BusStop*> important_stops;

    std::unordered_map<std::string, BusLine*> lines; //where key is line_name

    class PathStrategy;
    PathStrategy* path_strategy;
    Path path;

    Printer printer;

    void insertBusLine(const std::string& string);
    void insertBusStop(const std::string& string);

    Path findLeastTransfersPath(BusStop* start, BusStop* end);
    void unvisit();


    class PathStrategy {
    public:
        PathStrategy(const std::string& description, Graph* graph) 
        : description(description), graph(graph) {}

        virtual Path findPath(BusStop* start, BusStop* end) = 0;

        virtual ~PathStrategy() = default;
        static const std::string default_file_path;

        friend std::ostream& operator<<(std::ostream& os, const Graph::PathStrategy& path_strategy);
    
    protected:
        Graph* graph;
    
    private:
        std::string description;
    };
    friend std::ostream& operator<<(std::ostream& os, const Graph::PathStrategy& path_strategy);

    class LeastTransfersPathStrategy : public PathStrategy {
    public:
        LeastTransfersPathStrategy(Graph* graph) 
        : PathStrategy("Putanja sa najmanje presedanja", graph) {}

        Path findPath(BusStop* start, BusStop* end) override;
    };

    class DefaultPathStrategy : public PathStrategy {
    public:
        DefaultPathStrategy(Graph* graph) 
        : PathStrategy("Bilo koja putanja", graph) {}

        Path findPath(BusStop* start, BusStop* end) override;
    };

    class ImportantStopsStrategy : public PathStrategy {
    public:
        ImportantStopsStrategy(Graph* graph) 
        : PathStrategy("Putanja koja obilazi sva vazna stajalista u mrezi gradskog prevoza", graph) {}

        Path findPath(BusStop* start, BusStop* end) override;
    };


    std::vector<PathStrategy*> path_strategies = { new DefaultPathStrategy(this), 
    new LeastTransfersPathStrategy(this), new ImportantStopsStrategy(this) };
    
};