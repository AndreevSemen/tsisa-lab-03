// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <simulated_annealing.hpp>
#include <fstream>
#include <iomanip>

template < typename Logger >
void LogSimulatedAnnealingResults(Logger& logger, std::vector<SimulatedAnnealingResult>& results);

double UnimodalFunction(double x) {
    return std::cos(x)*std::tanh(x);
}

double MultimodalFunction(double x) {
    return std::cos(x)*std::tanh(x)*std::sin(5*x);
}

int main() {
    double a = -2;
    double b = 0;
    double maxT = 10000;
    double minT = 0.01;

    auto unimodalResults = SimulatedAnnealingSearch(UnimodalFunction, a, b, maxT, minT);
    auto multimodalResults = SimulatedAnnealingSearch(MultimodalFunction, a, b, maxT, minT);

    std::ofstream unimodalfile{"../search_results/unimodal_simulated_annealing.csv", std::ios::trunc};
    LogSimulatedAnnealingResults(unimodalfile, unimodalResults);
    unimodalfile.close();

    std::ofstream multimodalfile{"../search_results/multimodal_simulated_annealing.csv", std::ios::trunc};
    if (!multimodalfile.is_open()) {
        return 1;
    }
    LogSimulatedAnnealingResults(multimodalfile, multimodalResults);
    multimodalfile.close();

    return 0;
}

template < typename Logger >
void LogSimulatedAnnealingResults(Logger& logger, std::vector<SimulatedAnnealingResult>& results) {
    size_t cellSize = 6;

    SimulatedAnnealingResult::LogHeader(logger);
    for (const auto& result : results) {
        result.LogResult(logger);
    }
}
