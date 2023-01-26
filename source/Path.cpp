#include "Path.h"

int Path::getStartId() const{
    return stop_ids.front().front();
}

int Path::getEndId() const {
    return stop_ids.back().back();
}

bool Path::goesThrough(BusStop* stop) {
    int stop_id = stop->getId();
    for(auto& list : stop_ids) {
        for(auto id : list) {
            if(id == stop_id) return true;
        }
    }
    return false;
}

Path& Path::operator+=(const Path& rhs) {
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

std::ostream& operator<<(std::ostream& os, const Path& path) {
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

Path::Path(BusStop* start, std::vector<Edge*> edges){
    BusStop* prev = start;
    for(auto edge : edges) {
        lines.push_back(edge->getLine()->getName());
        stop_ids.push_back(edge->getLine()->travel(prev, edge->other(prev)));
        prev = edge->other(prev);
    }
}
