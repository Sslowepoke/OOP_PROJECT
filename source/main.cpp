#include "Graph.h"


int main() {

    Graph g = Graph();
    g.loadStops("files/OOP_PROJ_2022_23_JavniTest/test/stajalista.txt");
    g.loadLines("files/OOP_PROJ_2022_23_JavniTest/test/linije.txt");
    g.printStop(154, "output/stajaliste_154.txt");
    g.printLine("12", "output/linija_12.txt");



    return 0;
}