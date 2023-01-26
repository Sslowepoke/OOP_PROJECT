#pragma once

#include "Graph.h"

class Simulation {
public:
    static Simulation& getInstance();

    Simulation(const Simulation &) = delete;
    void operator=(const Simulation &) = delete;

    void openTerminal();

    void loadLineData(const std::string& file_path);
    void loadStopData(const std::string& file_path);

    void printStopInfo(int id);
    void printLineInfo(const std::string& name);

    void findPath(int start_id, int end_id);
    void changePathStrategy();

private:
    Simulation() : graph() {}
    Graph graph;

    class Option {
    public:
        virtual ~Option() = default;
        Option(const std::string& name) : name(name) {}
        std::string name;
        virtual bool execute() = 0;
        friend std::ostream& operator<<(std::ostream& os, const Simulation::Option& option);
    };
    friend std::ostream& operator<<(std::ostream& os, const Simulation::Option& option);

    class ExitOption : public Option {
    public:
        ExitOption() : Option("Kraj rada") {}
        bool execute() override;

    };

    class BusStopInfoOption : public Option {
    public:
        BusStopInfoOption() : 
            Option("Prikaz informacija o stajalistu"){}
        bool execute() override;
    };

    class BusLineInfoOption : public Option {
    public:
        BusLineInfoOption() :
            Option("Prikaz informacija o liniji gradskog prevoza") {}
        bool execute() override;
    };

    class FindPathOption : public Option {
    public:
        FindPathOption() : 
            Option("Pronalazak putanje izmedju dva stajalista") {}
        bool execute() override;
    };

    class ChangePathStrategyOption : public Option {
    public:
        ChangePathStrategyOption() :
            Option("Promena strategije za trazenje putanje") {}
        bool execute() override;
    };

    class LoadDataOption : public Option {
    public:
        LoadDataOption() : Option("Ucitavanje podataka o mrezi gradskog prevoza") {}
        bool execute() override;

    private:
        std::string file_path;
        static constexpr std::string_view default_line_file_path = "files/test/linije.txt";
        static constexpr std::string_view default_stop_file_path = "files/test/stajalista.txt";
        void loadLineData();
        void loadStopData();
    };

    class Interface {
    public:
        Interface();
        ~Interface();
        void printOptions();
        bool executeOption();
        bool initialized = true;

    private:
        std::vector<Option*> options;
    };

};
