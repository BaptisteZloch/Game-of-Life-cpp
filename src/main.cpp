#include <iostream>
#include <chrono>
#include <ctime>
#include <variant>
#include <cmath>
#include "utils.hpp"
#include "option.hpp"
#include "market.hpp"

int main()
{

    double spotPrice = 110.0;
    Option *callOption = new Option(OptionType::Call, ExerciseType::European, 100.0, convertDateStringToCtime("2024-12-26"));

    double optionPayoff = callOption->payoff(spotPrice);

    std::cout << callOption->getExerciseTypeAsString() << " " << callOption->getOptionTypeAsString() << " Option maturing on: " << callOption->getMaturityDateAsString() << "\tPayoff now: " << optionPayoff << "\tCurrent time to maturity: " << callOption->getTimeToMaturity() << std::endl;
    double interestRate = 0.04;
    double volatility = 0.25;
    Market market(interestRate, volatility, spotPrice);

    // int main() {
    //     // Example usage:
    //     Market market(/* initialize market parameters */);
    //     std::chrono::system_clock::time_point pricing_date = std::chrono::system_clock::now();
    //     int n_steps = 100;

    //     TrinomialTree trinomial_tree(market, pricing_date, n_steps);
    //     Option option(/* initialize option parameters */);

    //     double option_price = trinomial_tree.price(option, true);
    //     std::cout << "Option Price: " << option_price << std::endl;

    //     return 0;
    // }

    return 0;
}
