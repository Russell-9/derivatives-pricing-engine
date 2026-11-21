#include "Validation.hpp"
#include <iostream>
#include <cmath>

void requirePositiveFinite(double x, const char* name) {
        if (!(std::isfinite(x) && x > 0.0)) {
            throw std::invalid_argument(std::string(name) + " doit etre fini et strictement positif");
        }
    }