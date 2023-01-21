#include "Simulation.h"

#include <iostream>

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
                std::cout << e.what();
            }
        }
    }
    catch(std::exception& e) {
        std::cout << e.what();
    }

}


void Simulation::Interface::printOptions() {
    for(auto& option : options) {
        std::cout << count << ". " << option << std::endl;
    }
}

bool Simulation::Interface::executeOption() {
    int pos;
    if(!std::cin >> pos) throw std::invalid_argument("Opcija koju ste izabrali nije validna.");
    return options[pos].execute();
}


Simulation::Interface::Interface() : count(1), options() {
    options.emplace_back(ExitOption());
    options.emplace_back(LoadDataOption());
    
    std::cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju: " << std::endl;
    printOptions();
    if(executeOption()) {
        initialized = false;
        return;
    }
    options.pop_back();
    options.emplace_back(BusStopInfoOption());
    options.emplace_back(BusLineInfoOption());
    options.emplace_back(FindPathOption());
    options.emplace_back(ChangePathStrategyOption());
}

bool Simulation::ExitOption::execute() {
    return false;
}

bool Simulation::BusStopInfoOption::execute() {
    if(!std::cin >> stop_id) throw std::invalid_argument("Sifra stanice koju ste uneli nije validna.");
    return true;
}

bool Simulation::LoadDataOption::execute() {
    loadLineData();
    loadStopData();
    return true;
}

void Simulation::LoadDataOption::loadLineData() {
    std::cout << "Molimo vas unesite putanju do fajla sa linijama ili"
                "kliknite ENTER za ucitavanje podrazumevanog fajla (file/test/linije.txt)"
                << std::endl;
    std::cin >> file_path;
    if(file_path == "") file_path = default_line_file_path;

}

void Simulation::LoadDataOption::loadStopData() {
    std::cout << "Molimo vas unesite putanju do fajla sa stajalistima ili"
                "kliknite ENTER za ucitavanje podrazumevanog fajla (file/test/stajalista.txt)"
                << std::endl;
    std::cin >> file_path;
    if(file_path == "") file_path = default_stop_file_path;

}

std::ostream& operator<<(std::ostream& os, const Simulation::Option& option) {
    return os << option.name;
}