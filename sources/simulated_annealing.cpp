// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <simulated_annealing.hpp>

SimulatedAnnealingResult::SimulatedAnnealingResult(size_t N, double T, double x, double F_x, double P, bool passed)
  : _N(N)
  , _T(T)
  , _x(x)
  , _F_x(F_x)
  , _P(P)
  , _passed(passed)
{}

double CalculateP(double deltaF, double T) {
    if (deltaF <= 0) {
        return 1.;
    }
    return std::exp(-deltaF/T);
}

double Random(double a, double b) {
    static std::mt19937 rng{std::random_device{}()};
    return (b - a) * double(rng())/std::mt19937::max() + a;
}

void IfInvalidBoundsThrow(double a, double b) {
    if (a >= b) throw std::invalid_argument{
                "Left interval bound must be less than right bound"
        };
}

