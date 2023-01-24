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
    Graph(Printer* printer = new Printer()) 
    : stops(), important_stops(), lines(), path_strategy(new DefaultPathStrategy(this)), printer(printer) {}
    ~Graph();
    // loads bus stations
    void loadStops(const std::string& file_path);
    void loadLines(const std::string& file_path);
    void clearLines();
    void clearStops();

    void printStop(int id);
    void printLine(const std::string& name);
    void printPath();
    
    void findPath(int start, int end);

    void changePathStrategy();
    std::list<BusStop*>& getImportantStops() { return important_stops; }

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
    Path* findLeastTransfersPath(BusStop* start, BusStop* end);

    void unvisit();

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
        friend std::ostream& operator<<(std::ostream& os, const Graph::Path& path);
        int getStartId() const;
        int getEndId() const;
    private:
        std::vector<std::string> lines;
        std::vector<std::list<int>> stop_ids;
    };

    class PathStrategy {
    public:
        PathStrategy(const std::string& description, Graph* graph) : description(description), graph(graph) {}
        virtual Path* findPath(BusStop* start, BusStop* end) = 0;
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
        LeastTransfersPathStrategy(Graph* graph) : PathStrategy("Putanja sa najmanje presedanja", graph) {}
        Path* findPath(BusStop* start, BusStop* end) override;
    };

    class DefaultPathStrategy : public PathStrategy {
    public:
        DefaultPathStrategy(Graph* graph) : PathStrategy("Bilo koja putanja", graph) {}
        Path* findPath(BusStop* start, BusStop* end) override;
    };

    class ImportantStopsStrategy : public PathStrategy {
    public:
        ImportantStopsStrategy(Graph* graph) 
        : PathStrategy("Putanja koja obilazi sva vazna stajalista u mrezi gradskog prevoza", graph) {}
        Path* findPath(BusStop* start, BusStop* end) override;
    };

    friend std::ostream& operator<<(std::ostream& os, const Graph::Path& path);

    static constexpr int number_of_strategies = 3;
    PathStrategy* path_strategies[number_of_strategies] = { new DefaultPathStrategy(this), new LeastTransfersPathStrategy(this), new ImportantStopsStrategy(this) };
};