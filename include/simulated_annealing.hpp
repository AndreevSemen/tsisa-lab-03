// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#ifndef INCLUDE_SIMULATED_ANNEALING_HPP_
#define INCLUDE_SIMULATED_ANNEALING_HPP_

#include <random>
#include <stdexcept>
#include <iomanip>

void IfInvalidBoundsThrow(double a, double b);
double Random(double a, double b);

class SimulatedAnnealingResult {
private:
    size_t _N;
    double _T;
    double _x;
    double _F_x;
    double _min_F_x;
    double _P;
    bool _passed;

public:
    SimulatedAnnealingResult(size_t N, double T, double x, double F_x, double min_F_x, double P, bool passed);

    double GetT() const;
    double GetX() const;
    double GetF_x() const;

    template < typename Logger >
    static void LogHeader(Logger& logger) {
        size_t cellSize = 9;

        logger << std::setw(cellSize) << "N" << ",";
        logger << std::setw(cellSize) << "T" << ",";
        logger << std::setw(cellSize) << "X" << ",";
        logger << std::setw(cellSize) << "F(x)" << ",";
        logger << std::setw(cellSize) << "minimum" << ",";
        logger << std::setw(cellSize) << "P" << ",";
        logger << std::setw(cellSize) << "passed";
        logger << std::endl;
    }

    template < typename Logger >
    void LogResult(Logger& logger) const {
        size_t cellSize = 9;
        size_t precision = 4;

        logger << std::setw(cellSize) << _N  << ",";
        logger << std::setw(cellSize) << std::setprecision(precision) << std::fixed << _T << ",";
        logger << std::setw(cellSize) << std::setprecision(precision) << std::fixed << _x << ",";
        logger << std::setw(cellSize) << std::setprecision(precision) << std::fixed << _F_x << ",";
        logger << std::setw(cellSize) << std::setprecision(precision) << std::fixed << _min_F_x << ",";
        logger << std::setw(cellSize) << std::setprecision(precision) << std::fixed << _P << ",";
        logger << std::setw(cellSize) << std::setprecision(precision) << std::boolalpha << _passed;
        logger << std::endl;
    }
};

double CalculateP(double deltaF, double T);

template < typename Func >
std::vector<SimulatedAnnealingResult> SimulatedAnnealingSearch(Func func,
                           double a, double b, double maxT, double minT) {
    IfInvalidBoundsThrow(a, b);

    std::vector<SimulatedAnnealingResult> results;

    double F_x = std::numeric_limits<double>::max();
    double currentT = maxT;

    for (size_t N = 1; currentT >= minT; ++N) {
        double x = Random(a, b);

        double newF_x = func(x);
        double deltaF_x = newF_x - F_x;

        double P = CalculateP(deltaF_x, currentT);
        bool passed = false;
        if (Random(0, 1) < CalculateP(deltaF_x, currentT)) {
            F_x = newF_x;
            passed = true;
        }

        results.emplace_back(SimulatedAnnealingResult{N, currentT, x, newF_x, F_x, P, passed});

        currentT *= 0.95;
    }

    return results;
}

#endif // INCLUDE_SIMULATED_ANNEALING_HPP_
