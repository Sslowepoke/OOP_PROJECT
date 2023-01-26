#include <exception>
#include <string>

class SimulationException : public std::exception {
public:
    std::string whatstr;
    SimulationException(const std::string& what) : whatstr(what) {}
    const char* what() const noexcept override {
        return whatstr.c_str();
    } 
};

class InvalidOptionException : public SimulationException {
public:
    InvalidOptionException() 
    : SimulationException("Opcija koju ste izabrali nije validna, molimo pokusajte ponovo.") {}
};

class InvalidStationCodeException : public SimulationException {
public:
    InvalidStationCodeException() 
    : SimulationException("Sifra stanice koju ste uneli nije validna.") {}
};

class FailedToOpenFileException : public SimulationException {
public:
    FailedToOpenFileException() 
    : SimulationException("Neuspesno otvaranje fajla.") {}
};

class StationDoesNotExistException : public SimulationException {
public:
    StationDoesNotExistException()
    : SimulationException("Stajaliste sa tom sifrom ne postoji.") {}
};

class LineDoesNotExistException : public SimulationException {
public:
    LineDoesNotExistException()
    : SimulationException("Linija sa tom sifrom ne postoji.") {}
};

class PathDoesNotExistException : public SimulationException {
public:
    PathDoesNotExistException()
    : SimulationException("Nije moguce doci sa zadatog pocetnog stajalista do krajnjeg.") {}
};




