#include "Option.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>

TEST(OptionCall, Price) {
    Option call(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    EXPECT_NEAR(call.price(), 10.4506, 1e-4);
}

TEST(OptionCall, Delta) {
    Option call(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    EXPECT_NEAR(call.delta(), 0.636831, 1e-5);
}

TEST(OptionPut, Price) {
    Option put(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    EXPECT_NEAR(put.price(), 5.57353, 1e-4);
}

TEST(OptionParity, CallMinusPut) {
    Option call(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    Option put(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    double expected = 100 - 100 * std::exp(-0.05);
    EXPECT_NEAR(call.price() - put.price(), expected, 1e-10);
}

TEST(OptionCallPut, Gamma) {
    Option put(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    EXPECT_NEAR(put.gamma(), 0.018762, 1e-5);
}

TEST(OptionCallPut, Vega) {
    Option put(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    EXPECT_NEAR(put.vega(), 37.524, 1e-2);
}

TEST(OptionCall, Theta) {
    Option call(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    EXPECT_NEAR(call.theta(), -6.41403, 1e-4);
}

TEST(OptionPut, Theta) {
    Option put(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    EXPECT_NEAR(put.theta(), -1.65788, 1e-5);
}

TEST(OptionCall, Rho) {
    Option call(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    EXPECT_NEAR(call.rho(), 53.2325, 1e-4);
}

TEST(OptionPut, Rho) {
    Option put(100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    EXPECT_NEAR(put.rho(), -41.8905, 1e-4);
}

TEST(OptionValidation, NegativeSigmaThrows) {
    EXPECT_THROW(Option(100.0, 100.0, 1.0, 0.05, -0.2, OptionType::Call),
                std::invalid_argument);
}

TEST(OptionValidation, NullSpotThrows) {
    EXPECT_THROW(Option(0.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call),
                std::invalid_argument);
}

TEST(OptionValidation, NullStrikeThrows) {
    EXPECT_THROW(Option(100.0, 0.0, 1.0, 0.05, 0.2, OptionType::Call),
                std::invalid_argument);
}

TEST(OptionValidation, NullTimeThrows) {
    EXPECT_THROW(Option(100.0, 100.0, 0.0, 0.05, 0.2, OptionType::Call),
                std::invalid_argument);
}

TEST(OptionCall, PriceSAndkDifferent) {
    Option call(150.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    EXPECT_NEAR(call.price(), 54.9701, 1e-4);
}

TEST(OptionPut, PriceSAndkDifferent) {
    Option put(150.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    EXPECT_NEAR(put.price(), 0.093083, 1e-6);
}

TEST(OptionCall, Delta2) {
    Option call(150.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    EXPECT_NEAR(call.delta(), 0.9912, 1e-4);
}

TEST(OptionPut, Delta) {
    Option put(150.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    EXPECT_NEAR(put.delta(), -0.008719, 1e-6);
}