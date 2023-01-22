// #include "Graph.h"
#include "Simulation.h"
#include <iostream>

int main() {

    // Graph g = Graph();
    // g.loadStops("files/OOP_PROJ_2022_23_JavniTest/test/stajalista.txt");
    // g.loadLines("files/OOP_PROJ_2022_23_JavniTest/test/linije.txt");
    // g.printStop(154, "output/stajaliste_154.txt");
    // g.printLine("12", "output/linija_12.txt");
    // try{
    //     g.findPath(1221, 12);
    // }
    // catch(std::exception& e) {
    //     std::cout << e.what();
    // }
    Simulation& s = Simulation::getInstance();
    s.openTerminal();


    return 0;
}