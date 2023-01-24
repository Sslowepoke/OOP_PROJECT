#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <queue>
#include <utility>

Graph::~Graph() {
    clearStops();
    clearLines();
    for(auto* path_strategy : path_strategies) {
        delete path_strategy;
    }
    if(path) delete path;
    delete printer;
}

void Graph::clearLines() {
    for(auto& [key, value] : lines) {
        delete value;
    }
    lines.clear();
}

void Graph::clearStops() {
    for(auto [key, value] : stops) {
        delete value;
    }
    stops.clear();
}


void Graph::loadStops(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    try{
        if(file.is_open()) {
            while(getline(file, line)) {
                int index = line.find_first_of("\n\r");
                line = line.substr(0, index);
                insertBusStop(line);
            }
        }
        else
            throw std::runtime_error("Neuspesno otvaranje fajla, molimo pokusajte ponovo.");
    }
    catch(std::exception& e) {
        clearLines();
        clearStops();
        throw;
    }
}

void Graph::loadLines(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    try{
        if(file.is_open()) {
            std::string name;
            while(getline(file, line, '\n')) {
                insertBusLine(line);
            }
        }
        else
            throw std::runtime_error("Neuspesno otvaranje fajla, molimo pokusajte ponovo.");
    }
    catch(std::exception& e) {
        clearLines();
        clearStops();
        throw;
    }
}

void Graph::insertBusLine(const std::string& string) {
    size_t index1 = string.find_first_of(' ');
    std::string name = string.substr(0, index1);
    // std::string new_string = string.substr(index1 + 1);
    std::stringstream ss(string.substr(index1 + 1));
    int temp_id;
    std::list<BusStop*> line_stops;
    while(ss >> temp_id) {
        line_stops.push_back(stops[temp_id]);
    }
    BusLine* new_line = new BusLine(name, line_stops);
    lines.insert({name, new_line});
}
 
void Graph::insertBusStop(const std::string& string) {
    bool important;
    std::string name;
    int id;

    size_t index1 = string.find_first_of(' ');
    size_t index2 = string.find("[!]");
    if(index2 == std::string::npos){
        // index2 = string.find_first_of("\n\r");
        index2 = string.length();
        important = false;
    }
    else{
        important = true;
        index2--;
    }

    id = stoi(string);
    name = string.substr(index1+1, index2 - index1 - 1);

    BusStop* new_stop = new BusStop(id, name, important);

    stops.insert({id, new_stop});

    if(important) 
        important_stops.push_front(new_stop);
}

void Graph::printStop(int id) {
    if(!stops.contains(id)) throw std::out_of_range("Stajaliste sa tom sifrom ne postoji.");
    printer->printStop(stops[id]);
}

void Graph::printLine(const std::string& name) {
    if(!lines.contains(name)) throw std::out_of_range("Linija sa tom sifrom ne postoji.");
    printer->printLine(lines[name]);
}

void Graph::findPath(int start, int end) {
    if(!stops.contains(start) || !stops.contains(end)) throw std::out_of_range("Stajaliste sa tom sifrom ne postoji.");
    path = path_strategy->findPath(stops[start], stops[end]);
}

void Graph::unvisit() {
    for (auto& pair : stops) {
        pair.second->unvisit();
    }
}

void Graph::printPath() {
    std::string file_path = "output/putanja_" + std::to_string(path->getStartId())
        + "_" + std::to_string(path->getEndId()) + ".txt";
    std::ofstream file(file_path);
    if(file.is_open()) {
        file << *path;
    }
    else
        throw std::runtime_error("Neuspesno otvaranje fajla.");
}

int Graph::Path::getStartId() const{
    return stop_ids.front().front();
}

int Graph::Path::getEndId() const {
    return stop_ids.back().back();
}

Graph::Path* Graph::LeastTransfersPathStrategy::findPath(BusStop* start, BusStop* end) {
    std::queue<std::pair<BusStop*, std::vector<Edge*>>> queue;
    std::unordered_map<int, bool> visited;
    queue.push({start, std::vector<Edge*>()});

    while(queue.size() > 0) {
        auto current = queue.front();
        auto* current_stop = current.first;
        auto current_path = current.second;
        queue.pop();
        if(current_stop == end) {
            Path* path = new Path(start, current_path);
            // graph->unvisit();
            return path;
        }
        for(auto edge : current_stop->getEdges()) {
            auto neighbour = edge->other(current_stop);
            if(!visited.contains(neighbour->getId())) {
                visited[neighbour->getId()] = true;
                std::vector<Edge*> new_path(current_path);
                new_path.push_back(edge);
                queue.push({neighbour, new_path});
            }
        }
    }
    throw std::out_of_range("Nije moguce doci sa zadatog pocetnog stajalista do krajnjeg.");
}


Graph::Path* Graph::DefaultPathStrategy::findPath(BusStop* start, BusStop* end) {
    std::queue<std::pair<BusStop*, std::vector<Edge*>>> queue;
    std::unordered_map<int, bool> visited;
    queue.push({start, std::vector<Edge*>()});

    while(queue.size() > 0) {
        auto current = queue.front();
        auto* current_stop = current.first;
        auto current_path = current.second;
        queue.pop();
        if(current_stop == end) {
            Path* path = new Path(start, current_path);
            // graph->unvisit();
            return path;
        }
        for(auto edge : current_stop->getEdges()) {
            auto neighbour = edge->other(current_stop);
            if(!visited.contains(neighbour->getId())) {
                visited[neighbour->getId()] = true;
                std::vector<Edge*> new_path(current_path);
                new_path.push_back(edge);
                queue.push({neighbour, new_path});
            }
        }
    }
    throw std::out_of_range("Nije moguce doci sa zadatog pocetnog stajalista do krajnjeg.");
}

Graph::Path* Graph::findLeastTransfersPath(BusStop* start, BusStop* end) {
    return path_strategies[1]->findPath(start, end);
}

Graph::Path* Graph::ImportantStopsStrategy::findPath(BusStop* start, BusStop* end) {
    Graph::Path *path = new Graph::Path();
    BusStop* previous = start;
    for(auto current : graph->getImportantStops()) {
        if(path->goesThrough(current)) continue;
        (*path) += *graph->findLeastTransfersPath(previous, current);
        previous = current;
    }
    *path += *graph->findLeastTransfersPath(previous, end);
    return path;
}

bool Graph::Path::goesThrough(BusStop* stop) {
    int stop_id = stop->getId();
    for(auto& list : stop_ids) {
        for(auto id : list) {
            if(id == stop_id) return true;
        }
    }
    return false;
}

Graph::Path& Graph::Path::operator+=(const Graph::Path& rhs) {
    if(this->lines.size() > 0 && this->lines.back() == rhs.lines.front()) {
        this->stop_ids.back().insert(this->stop_ids.back().end(), rhs.stop_ids.front().begin(), rhs.stop_ids.front().end());
        this->lines.insert(this->lines.end(), rhs.lines.begin()+1, rhs.lines.end());
        this->stop_ids.insert(this->stop_ids.end(), rhs.stop_ids.begin()+1, rhs.stop_ids.end());
    }
    else {
        this->lines.insert(this->lines.end(), rhs.lines.begin(), rhs.lines.end());
        this->stop_ids.insert(this->stop_ids.end(), rhs.stop_ids.begin(), rhs.stop_ids.end());
    }
    return *this;
}

Graph::Path::Path(BusStop* start, std::vector<Edge*> edges){
    BusStop* prev = start;
    for(auto edge : edges) {
        lines.push_back(edge->getLine()->getName());
        stop_ids.push_back(edge->getLine()->travel(prev, edge->other(prev)));
        prev = edge->other(prev);
    }
}

std::ostream& operator<<(std::ostream& os, const Graph::Path& path) {
    std::string* previous = nullptr;
    for(int i = 0; i < path.lines.size(); i++) {
        if(i > 0) os << path.lines[i-1];
        os << "->" << path.lines[i] << std::endl;
        for(auto id : path.stop_ids[i]) {
            os << id << " ";
        }
        os << std::endl;
    }
    return os;
}

void Graph::changePathStrategy() {
    std::cout << "Molimo vas izaberite jednu od strategija za pronalazenje puta." << std::endl;
    int count = 0;
    for(auto path_strategy : path_strategies) {
        std::cout << count++ << ". " << *path_strategy << std::endl;
    }
    int position = 0;
    if(std::cin >> position){
        std::cin.ignore();
        if(position > number_of_strategies -1 || position < 0)
            throw std::invalid_argument("Opcija koju ste izabrali nije validna, molimo pokusajte ponovo.");
        path_strategy = path_strategies[position];
        return;
    }
    else
        throw std::invalid_argument("Opcija koju ste izabrali nije validna, molimo pokusajte ponovo.");
}

std::ostream& operator<<(std::ostream& os, const Graph::PathStrategy& path_strategy) {
    return os << path_strategy.description;
}
