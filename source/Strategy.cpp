#include "Strategy.h"
#include <set>
#include <queue>
#include <utility>
#include <iostream>

void LeastTransfersPathStrategy::findPath(BusStop* start, BusStop* end) {
    std::set<BusStop*> visited;
    std::queue<std::pair<BusStop*, std::vector<Edge*>>> queue;
    
    // for(auto edge : start->edges) {
    //     queue.push({start, std::vector<Edge*>(1, edge)});
    // }
    queue.push({start, std::vector<Edge*>()});

    while(queue.size() > 0) {
        // BusStop* stop; int transfers;
        auto current = queue.front();
        auto current_stop = current.first;
        auto current_path = current.second;
        queue.pop();
        if(current_stop == end) {
            Path p(start, current_path);
            std::cout << p;
            return;
        }
        for(auto edge : current_stop->edges) {
            auto neighbour = edge->other(current_stop);
            if(!edge->was_travelled()) {
                edge->travel();
                std::vector<Edge*> new_path(current_path);
                new_path.push_back(edge);
                queue.push({neighbour, new_path});
            }
        }
    }
    throw std::out_of_range("Didn't find an answer");
}

void LeastTransfersPathStrategy::constructPath(BusStop* start, BusStop* end) {
    
}

Path::Path(BusStop* start, std::vector<Edge*> edges) {
    // stop_ids[0].push_front(start->getId());
    BusStop* prev = start;
    for(auto edge : edges) {
        lines.push_back(edge->getLine()->getName());
        stop_ids.push_back(edge->getLine()->travel(prev, edge->other(prev)));
        prev = edge->other(prev);
    }
}

std::ostream& operator<<(std::ostream& os, Path& path) {
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

