#include "Simulation.h"

#include <iostream>

std::string Simulation::default_output_path = "output/";
std::string Simulation::default_file_extension = ".txt";

Simulation& Simulation::getInstance() {
    static Simulation instance;
    return instance;
}


void Simulation::openTerminal() {
    try {
        Interface interface = Interface();
        if(interface.initialized == false) return;
        
        while(1) {
            try {
                interface.printOptions();
                if(interface.executeOption() == false) break;
            }
            catch(std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}


void Simulation::Interface::printOptions() {
    int count = 0;
    for(auto option : options) {
        std::cout << count++ << ". " << *option << std::endl;
    }
}

bool Simulation::Interface::executeOption() {
    int pos;
    if(std::cin >> pos){
        return options[pos]->execute();
        std::cin.clear();
    }
    else
        throw std::invalid_argument("Opcija koju ste izabrali nije validna.");
}


Simulation::Interface::Interface() : options() {
    options.push_back(new ExitOption());
    options.push_back(new LoadDataOption());
    
    std::cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju: " << std::endl;
    printOptions();
    if(executeOption() == false) {
        initialized = false;
        return;
    }
    delete options.back();
    options.pop_back();
    options.push_back(new BusStopInfoOption());
    options.push_back(new BusLineInfoOption());
    options.push_back(new FindPathOption());
    options.push_back(new ChangePathStrategyOption());
}

Simulation::Interface::~Interface() {
    for(auto option : options) {
        delete option;
    }
}

bool Simulation::ExitOption::execute() {
    return false;
}

bool Simulation::BusStopInfoOption::execute() {
    if(std::cin >> stop_id){
        std::string stop_id_str = std::to_string(stop_id);
        std::string file_path = default_output_path + "stajaliste_" + stop_id_str + default_file_extension;
        getInstance().printStopInfo(stop_id, file_path);
        return true;
    }
    else 
        throw std::invalid_argument("Sifra stanice koju ste uneli nije validna.");
}

void Simulation::printStopInfo(int id, const std::string& file_name) {
    graph.printStop(id, file_name);
}

bool Simulation::BusLineInfoOption::execute() {

    return true;
}

void Simulation::printLineInfo(const std::string& name, const std::string& file_name) {

}

bool Simulation::LoadDataOption::execute() {
    loadStopData();
    loadLineData();
    return true;
}

void Simulation::loadLineData(const std::string& file_path) {
    graph.loadLines(file_path);
}

void Simulation::loadStopData(const std::string& file_path) {
    graph.loadStops(file_path);
}


void Simulation::LoadDataOption::loadLineData() {
    std::cout << "Molimo vas unesite putanju do fajla sa linijama ili"
                "kliknite ENTER za ucitavanje podrazumevanog fajla (file/test/linije.txt)"
                << std::endl;
    // std::cin.clear();
    std::getline(std::cin, file_path);
    if(file_path.length() == 0) file_path = default_line_file_path;
    Simulation::getInstance().loadLineData(file_path);
}

void Simulation::LoadDataOption::loadStopData() {
    std::cout << "Molimo vas unesite putanju do fajla sa stajalistima ili"
                "kliknite ENTER za ucitavanje podrazumevanog fajla (file/test/stajalista.txt)"
                << std::endl;
    std::getline(std::cin, file_path);
    if(file_path.length() == 0) file_path = default_stop_file_path;
    Simulation::getInstance().loadStopData(file_path);
}

std::ostream& operator<<(std::ostream& os, const Simulation::Option& option) {
    return os << option.name;
}

bool Simulation::FindPathOption::execute() {
    return true;
}

bool Simulation::ChangePathStrategyOption::execute() {
    return true;
}
