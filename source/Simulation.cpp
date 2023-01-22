#include "Simulation.h"

#include <iostream>


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
        std::cin.ignore();
        return options[pos]->execute();
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
    int stop_id;
    std::cout << "Molimo Vas, unesite sifru stajalista cije informacije zelite da prikazete." << std::endl;
    if(std::cin >> stop_id){
        std::cin.ignore();
        getInstance().printStopInfo(stop_id);
        return true;
    }
    else 
        throw std::invalid_argument("Sifra stanice koju ste uneli nije validna.");
}

void Simulation::printStopInfo(int id) {
    graph.printStop(id);
}

bool Simulation::BusLineInfoOption::execute() {
    std::string line_name;
    std::cout << "Molimo Vas, unesite oznaku linije cije informacije zelite da prikazete." << std::endl;
    if(std::cin >> line_name) {
        std::cin.ignore();
        getInstance().printLineInfo(line_name);
        return true;
    }
    else
        throw std::invalid_argument("Ime linije koje ste uneli nije validno");
}

void Simulation::printLineInfo(const std::string& line_name) {
    graph.printLine(line_name);
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
    std::cout << "Molimo vas unesite putanju do fajla sa linijama ili "
                "kliknite ENTER za ucitavanje podrazumevanog fajla (file/test/linije.txt)"
                << std::endl;
    // std::cin.clear();
    std::getline(std::cin, file_path);
    if(file_path.length() == 0) file_path = default_line_file_path;
    Simulation::getInstance().loadLineData(file_path);
}

void Simulation::LoadDataOption::loadStopData() {
    std::cout << "Molimo vas unesite putanju do fajla sa stajalistima ili "
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
    int start_id, end_id;
    std::cout << "Molimo vas unesite pocetno stajaliste." << std::endl;
    if(std::cin >> start_id) 
        std::cin.ignore();
    else
        throw std::invalid_argument("Uneli ste nevalidnu sifru pocetnog stajalista.");
    std::cout << "Molimo vas unestie krajnje stajaliste." << std::endl;
    if(std::cin >> end_id) 
        std::cin.ignore();
    else
        throw std::invalid_argument("Uneli ste nevalidnu sifru krajnjeg stajalista.");
    getInstance().findPath(start_id, end_id);
    return true;
}

void Simulation::findPath(int start_id, int end_id) {
    graph.findPath(start_id, end_id);
    graph.printPath();
}

bool Simulation::ChangePathStrategyOption::execute() {

    return true;
}
