// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#ifndef INCLUDE_SIMULATED_ANNEALING_HPP_
#define INCLUDE_SIMULATED_ANNEALING_HPP_

#include <random>
#include <stdexcept>
#include <iomanip>

void IfInvalidBoundsThrow(double a, double b);
double RandomFrom0To1(std::mt19937_64& generator);

class SimulatedAnnealingResult {
private:
    size_t _N;
    double _T;
    double _x;
    double _F_x;

public:
    SimulatedAnnealingResult(size_t N, double T, double x, double F_x);

    double GetT() const;
    double GetX() const;
    double GetF_x() const;

    template < typename Logger >
    static void LogHeader(Logger& logger) {
        size_t cellSize = 9;

        for (size_t i = 0; i < 4*cellSize + 4; ++i) {
            logger << "_";
        }
        logger << std::endl;

        logger << "|" << std::setw(cellSize) << "N";
        logger << "|" << std::setw(cellSize) << "T";
        logger << "|" << std::setw(cellSize) << "X";
        logger << "|" << std::setw(cellSize) << "F(x)";
        logger << "|" << std::endl;
    }

    template < typename Logger >
    void LogResult(Logger& logger) const {
        size_t cellSize = 9;
        size_t precision = 4;

        LogFooter(logger);
        logger << "|" << std::setw(cellSize) << _N;
        logger << "|" << std::setw(cellSize) << std::setprecision(precision) << _T;
        logger << "|" << std::setw(cellSize) << std::setprecision(precision) << _x;
        logger << "|" << std::setw(cellSize) << std::setprecision(precision) << _F_x;
        logger << "|" << std::endl;
    }

    template < typename Logger >
    static void LogFooter(Logger& logger) {
        size_t cellSize = 9;

        for (size_t i = 0; i < 4; ++i) {
            logger << "|";
            for (size_t i = 0; i < cellSize; ++i) {
                logger << "_";
            }
        }
        logger << "|" << std::endl;
    }
};

double CalculateP(double deltaF, double T);

template < typename Func >
std::vector<SimulatedAnnealingResult> SimulatedAnnealingSearch(Func func,
                           double a, double b, double maxT, double minT) {
    IfInvalidBoundsThrow(a, b);

    std::vector<SimulatedAnnealingResult> results;

    std::mt19937_64 randomGenerator{std::random_device{}()};

    double F_x = std::numeric_limits<double>::max();
    double currentT = maxT;

    size_t N = 1;
    while (currentT >= minT) {

        double x = (b - a) * RandomFrom0To1(randomGenerator) + a;

        double newF_x = func(x);
        double deltaF_x = newF_x - F_x;
        if (newF_x < F_x ||
            RandomFrom0To1(randomGenerator) < CalculateP(deltaF_x, currentT)) {
            F_x = newF_x;
        }

        results.emplace_back(SimulatedAnnealingResult{N, currentT, x, F_x});

        currentT *= 0.95;
        ++N;
    }

    return results;
}

#endif // INCLUDE_SIMULATED_ANNEALING_HPP_
