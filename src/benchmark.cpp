#include "Option.hpp"
#include <iostream>
#include <chrono>

double average_price(int N, double S, double K, double T, double r, double  sigma, OptionType Type) {
    double sum = 0.0;
    double S_i = S;
    for (int i = 0; i < N; i++) {
        Option Call = Option(S_i, K, T, r, sigma, Type);
        sum += Call.price();
        S_i = S + ((i + 1) %100) * 0.05;

    }
    return sum/double(N);
}

int main() {

    int  N = 10000;
    double S = 150.0;
    double K = 100.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;
    OptionType Type = OptionType::Call;
    
    auto debut = std::chrono::steady_clock::now();


    double a = average_price(N, S, K, T, r, sigma, Type);

    auto fin = std::chrono::steady_clock::now();

    std::cout << "Price average : " << a << std::endl;

    auto dureeUs = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);

    std::cout << "Execution duration : " << dureeUs.count() << std::endl;
    std::cout<< "Prix par seconde : " << double(N)/(dureeUs.count() * 1e-6) << std::endl;

    return 0;
}
