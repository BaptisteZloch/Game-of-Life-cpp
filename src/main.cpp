// #include "option.hpp"

#include <iostream>
#include <chrono>
#include <variant>
#include <cmath>
#include "utils.hpp"
#include "option.hpp"
#include "market.hpp"

int main()
{
    // Example usage:
    Option callOption(OptionType::Call, ExerciseType::European, 100.0, std::chrono::system_clock::now());
    double spotPrice = 110.0;
    double interestRate = 5.0;
    double volatility = 10.0;
    double dividendPrice = 2.0;

    double optionPayoff = callOption.payoff(spotPrice);
    std::cout << "Option Payoff: " << optionPayoff << std::endl;

    std::chrono::system_clock::time_point dividendExDate = std::chrono::system_clock::now();

    Market market(interestRate, volatility, spotPrice, dividendPrice, dividendExDate);

    return 0;
}
