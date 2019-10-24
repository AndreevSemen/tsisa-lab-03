// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <simulated_annealing.hpp>

SimulatedAnnealingResult::SimulatedAnnealingResult(size_t N, double T, double x, double F_x)
  : _N(N)
  , _T(T)
  , _x(x)
  , _F_x(F_x)
{}

double SimulatedAnnealingResult::GetT() const {
    return _T;
}

double SimulatedAnnealingResult::GetX() const {
    return _x;
}

double SimulatedAnnealingResult::GetF_x() const {
    return _F_x;
}

double CalculateP(double deltaF, double T) {
    return std::exp(-deltaF/T);
}

double RandomFrom0To1(std::mt19937_64& generator) {
    return double(generator())/std::mt19937_64::max();
}

void IfInvalidBoundsThrow(double a, double b) {
    if (a >= b) throw std::invalid_argument{
                "Left interval bound must be less than right bound"
        };
}

