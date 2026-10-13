#include "Option.hpp"
#include <cmath>
#include <string>
#include <stdexcept>

namespace {
    constexpr double PI = 3.14159265358979323846;
    double normCDF(double x) { return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0))); }
    double normPDF(double x) { return std::exp(-0.5 * x * x) / std::sqrt(2.0 * PI); }
    void requirePositiveFinite(double x, const char* name) {
        if (!(std::isfinite(x) && x > 0.0)) {
            throw std::invalid_argument(std::string(name) + " doit etre fini et strictement positif");
        }
    } 
}

Option::Option(double S, double K, double T, double r, double sigma, OptionType type) : S_(S), K_(K), T_(T), r_(r), sigma_(sigma), 
            type_(type) {
                requirePositiveFinite(S, "S");
                requirePositiveFinite(K, "K");
                requirePositiveFinite(T, "T");
                requirePositiveFinite(sigma, "sigma");

                if (!(std::isfinite(r))) {
                    throw std::invalid_argument("r doit etre fini");
                }
                
                
                this->d1_ = (std::log(S/K) + (r + (sigma * sigma)/2) * T)/(sigma * std::sqrt(T));
                this->d2_ = d1_ - sigma * std::sqrt(T);
}

double Option::price() const {
    if (type_ == OptionType::Call ) {
        
        double C = S_ * normCDF(d1_) - K_ * std::exp(-r_ * T_) * normCDF(d2_);

        return C;
    }
    
    else {
        double P =  K_ * std::exp(-r_ * T_) * normCDF(-d2_) - S_ * normCDF(-d1_);

        return P;
    }
}

double Option::delta() const {
    if (type_ == OptionType::Call) {

        return normCDF(d1_);
    }
    else {
        return normCDF(d1_) - 1.0;
    }
}

double Option::gamma() const {
    return normPDF(d1_)/(S_ * sigma_ * std::sqrt(T_));
}

double Option::vega() const { 
    return S_ * normPDF(d1_) * std::sqrt(T_);
}

double Option::theta() const {
    if (type_ == OptionType::Call) {

        return -(S_ * normPDF(d1_) * sigma_)/(2 * std::sqrt(T_)) -r_ *  K_ * std::exp(- r_ * T_) * normCDF(d2_);
    }
    else {
        return -(S_ * normPDF(d1_) * sigma_)/(2 * std::sqrt(T_)) + r_ *  K_ * std::exp(- r_ * T_) * normCDF(- d2_);
    }
}

double Option::rho() const {
    if (type_ == OptionType::Call) {

        return K_ * T_ *std::exp(- r_ * T_) * normCDF(d2_);
    }
    else {
        return -K_ * T_ *std::exp(- r_ * T_) * normCDF(-d2_);
    }
}