// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <simulated_annealing.hpp>
#include <fstream>
#include <iomanip>

template < typename Logger >
void LogSimulatedAnnealingResults(Logger& logger, std::vector<SimulatedAnnealingResult>& results);

double func(double x) {
    return std::cos(x)*std::tanh(x);
}

int main() {
    double a = -2;
    double b = 0;
    double maxT = 10000;
    double minT = 0.01;

    auto results = SimulatedAnnealingSearch(func, a, b, maxT, minT);

    std::ofstream file{"simulated_annealing.txt", std::ios::trunc};
    LogSimulatedAnnealingResults(file, results);
    file.close();

    return 0;
}

template < typename Logger >
void LogSimulatedAnnealingResults(Logger& logger, std::vector<SimulatedAnnealingResult>& results) {
    size_t cellSize = 6;

    SimulatedAnnealingResult::LogHeader(logger);
    for (const auto& result : results) {
        result.LogResult(logger);
    }
    SimulatedAnnealingResult::LogFooter(logger);
}
