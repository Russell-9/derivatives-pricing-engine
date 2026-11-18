# Derivatives Pricing Engine

This project comprises a library for option pricing in C++17. Its computations are limited to the price and Greeks of European options such as Call and Put.

## Status

**Done**
- Black-Scholes pricing for European calls and puts
- The five Greeks: Delta, Gamma, Vega, Theta, Rho
- Immutable `Option` class with input validation (invalid inputs throw `std::invalid_argument`)
- 15 unit tests (GoogleTest), including put-call parity
- Benchmark (see below)

**Planned**
- Binomial trees
- Monte Carlo
- Exotic options
- Production-ready version

## Requirements

- C++17 compiler (tested with g++ 15.2.0)
- CMake 3.16 or later (tested with 4.2.3)
- Internet connection on first build (GoogleTest 1.15.2 is downloaded from GitHub)
- Tested on WSL Ubuntu

## Build and run

```bash
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
./build-release/pricer
```

## Tests

```bash
ctest --test-dir build-release --output-on-failure
```

The 15 tests check prices and Greeks against reference values, put-call parity, and the rejection of invalid inputs.

## Formulas

With $N$ the standard normal CDF and $\varphi$ its density:

$$d_1 = \frac{\ln(S/K) + (r + \sigma^2/2)\,T}{\sigma\sqrt{T}}, \qquad d_2 = d_1 - \sigma\sqrt{T}$$

$$C = S\,N(d_1) - K e^{-rT} N(d_2)$$

$$P = K e^{-rT} N(-d_2) - S\,N(-d_1)$$

| Greek | Call | Put |
|---|---|---|
| Delta | $N(d_1)$ | $N(d_1) - 1$ |
| Gamma | $\dfrac{\varphi(d_1)}{S\sigma\sqrt{T}}$ | same as call |
| Vega | $S\,\varphi(d_1)\sqrt{T}$ | same as call |
| Theta | $-\dfrac{S\varphi(d_1)\sigma}{2\sqrt{T}} - rKe^{-rT}N(d_2)$ | $-\dfrac{S\varphi(d_1)\sigma}{2\sqrt{T}} + rKe^{-rT}N(-d_2)$ |
| Rho | $KTe^{-rT}N(d_2)$ | $-KTe^{-rT}N(-d_2)$ |

Variables: $S$ spot price, $K$ strike, $T$ time to expiry in years, $r$ risk-free rate, $\sigma$ volatility (annualized). Theta is per year and Vega is per unit of volatility (not per 1%).

## Usage

```cpp
#include "Option.hpp"
#include <iostream>

int main() {
    Option call(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    std::cout << "Price: " << call.price() << '\n';  // 10.4506
    std::cout << "Delta: " << call.delta() << '\n';  // 0.636831

    try {
        Option bad(100.0, 100.0, 1.0, 0.05, -0.2, OptionType::Call);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
```

## Benchmark

About 9.4 million prices per second in Release mode (minimum of 5 runs, 1 million options per run, WSL). Each price includes construction, validation and `price()`. Unoptimized builds reach about 5.6 to 6.8 million per second. Results are noisy under WSL and depend on the machine.

## Limitations

- European options only, no early exercise
- Constant volatility and interest rate, no dividends
- Black-Scholes assumptions (log-normal underlying)

## Project structure

```
include/Option.hpp     Option class declaration
src/Option.cpp         Implementation
src/main.cpp           Manual checks
src/benchmark.cpp      Benchmark
tests/test_option.cpp  GoogleTest unit tests
CMakeLists.txt         Build configuration
```