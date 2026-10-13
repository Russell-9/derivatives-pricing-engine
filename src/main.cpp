#include "Option.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

// Tente de construire une option ; affiche l'erreur si le constructeur refuse.
void tryBuild(const std::string& label, double S, double K, double T,
              double r, double sigma) {
    try {
        Option opt(S, K, T, r, sigma, OptionType::Call);
        std::cout << label << " : ACCEPTE (inattendu !) prix = "
                  << opt.price() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << label << " : Erreur : " << e.what() << std::endl;
    }
}

int main() {
    std::cout << std::setprecision(8);

    // ---------- 1. Call de reference : les six valeurs ----------
    Option call(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    std::cout << "=== Call reference ===" << std::endl;
    std::cout << "price : " << call.price() << "  (attendu 10.4506)" << std::endl;
    std::cout << "delta : " << call.delta() << "  (attendu 0.636831)" << std::endl;
    std::cout << "gamma : " << call.gamma() << "  (attendu 0.018762)" << std::endl;
    std::cout << "vega  : " << call.vega()  << "  (attendu 37.524)" << std::endl;
    std::cout << "theta : " << call.theta() << "  (attendu -6.41403)" << std::endl;
    std::cout << "rho   : " << call.rho()   << "  (attendu 53.2325)" << std::endl;

    // ---------- 2. Put de reference : les six valeurs ----------
    Option put(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    std::cout << "\n=== Put reference ===" << std::endl;
    std::cout << "price : " << put.price() << "  (attendu 5.57353)" << std::endl;
    std::cout << "delta : " << put.delta() << "  (attendu -0.363169)" << std::endl;
    std::cout << "gamma : " << put.gamma() << "  (attendu 0.018762)" << std::endl;
    std::cout << "vega  : " << put.vega()  << "  (attendu 37.524)" << std::endl;
    std::cout << "theta : " << put.theta() << "  (attendu -1.65788)" << std::endl;
    std::cout << "rho   : " << put.rho()   << "  (attendu -41.8905)" << std::endl;

    // ---------- 3. Autres cas valides (non-regression) ----------
    std::cout << "\n=== Autres cas ===" << std::endl;
    Option callVol(100.0, 100.0, 1.0, 0.05, 0.4, OptionType::Call);
    Option putVol(100.0, 100.0, 1.0, 0.05, 0.4, OptionType::Put);
    Option callShort(100.0, 100.0, 0.1, 0.05, 0.2, OptionType::Call);
    Option putShort(100.0, 100.0, 0.1, 0.05, 0.2, OptionType::Put);
    Option callItm(150.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    Option putItm(150.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    Option putDeep(50.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);

    std::cout << "call sigma=0.4  : " << callVol.price()   << "  (attendu 18.023)" << std::endl;
    std::cout << "put  sigma=0.4  : " << putVol.price()    << "  (attendu 13.1459)" << std::endl;
    std::cout << "call T=0.1      : " << callShort.price() << "  (attendu 2.77365)" << std::endl;
    std::cout << "put  T=0.1      : " << putShort.price()  << "  (attendu 2.2749)" << std::endl;
    std::cout << "call S=150      : " << callItm.price()   << "  (attendu 54.9701)" << std::endl;
    std::cout << "put  S=150      : " << putItm.price()    << "  (attendu 0.0930826)" << std::endl;
    std::cout << "theta put S=50  : " << putDeep.theta()   << "  (attendu 4.73842, positif)" << std::endl;

    // ---------- 4. Verifications croisees ----------
    std::cout << "\n=== Verifications croisees ===" << std::endl;
    double parity = call.price() - put.price();
    double expected = 100.0 - 100.0 * std::exp(-0.05 * 1.0);
    std::cout << "C - P          : " << parity << std::endl;
    std::cout << "S - K*exp(-rT) : " << expected << std::endl;
    std::cout << "ecart parite   : " << std::fabs(parity - expected) << "  (attendu ~1e-14)" << std::endl;
    std::cout << "delta C - P    : " << call.delta() - put.delta() << "  (attendu 1)" << std::endl;

    // ---------- 5. Cas invalides (chacun doit etre refuse) ----------
    std::cout << "\n=== Cas invalides ===" << std::endl;
    const double nan = std::nan("");
    const double inf = std::numeric_limits<double>::infinity();

    tryBuild("sigma = -0.2", 100.0, 100.0, 1.0, 0.05, -0.2);
    tryBuild("sigma = 0   ", 100.0, 100.0, 1.0, 0.05, 0.0);
    tryBuild("S = 0       ", 0.0,   100.0, 1.0, 0.05, 0.2);
    tryBuild("K = -50     ", 100.0, -50.0, 1.0, 0.05, 0.2);
    tryBuild("T = 0       ", 100.0, 100.0, 0.0, 0.05, 0.2);
    tryBuild("S = NaN     ", nan,   100.0, 1.0, 0.05, 0.2);
    tryBuild("sigma = inf ", 100.0, 100.0, 1.0, 0.05, inf);
    tryBuild("r = NaN     ", 100.0, 100.0, 1.0, nan,  0.2);

    // ---------- 6. Test du terminate (decommente UNE fois, puis remets en commentaire) ----------
    // Option bad(100.0, 100.0, 1.0, 0.05, -0.2, OptionType::Call);

    return 0;
}