#pragma once
#include <cmath>
#include <ctime>

double calculateDiscountFactor(double interest_rate, double deltaT)
{
    return exp(-interest_rate * deltaT);
}

double calculateForwardPrice(double spot_price, double interest_rates, double deltaT)
{
    return spot_price * exp(interest_rates * deltaT);
}

double discountValue(
    double value_to_discount, double interest_rates, double deltaT)
{
    return value_to_discount * calculateDiscountFactor(
                                   interest_rates, deltaT);
}
double calculateAlpha(double volatility, double deltaT, int factor = 3)
{
    return exp(volatility * sqrt(factor * deltaT));
}

double calculateVariance(double spot_price,
                         double interest_rate,
                         double volatility, double deltaT)
{
    return ((pow(spot_price, 2)) * exp(2 * interest_rate * deltaT) * (exp((pow(volatility, 2)) * deltaT) - 1));
}

double calculateDownProbability(double esperance,
                                double forward_price,
                                double variance,
                                double alpha)
{
    return ((pow(esperance, -2)) * (variance + pow(forward_price, 2)) - 1 - (alpha + 1) * ((pow(esperance, -1)) * forward_price - 1)) / ((1 - alpha) * ((pow(alpha, -2)) - 1));
}

double calculateUpProbability(double down_probability,
                              double alpha)
{
    return down_probability / alpha;
}

double calculateUpProbabilityWithDividend(double down_probability,
                                          double alpha,
                                          double esperance,
                                          double forward_price)
{
    return (pow((alpha - 1), -1)) * ((pow(esperance, -1)) * forward_price - 1 - ((pow(alpha, -1)) - 1) * down_probability);
}

double calculateMidProbability(double up_probability,
                               double down_probability)
{
    return 1 - (down_probability + up_probability);
}

time_t convertDateStringToCtime(const char *date_string)
{
    // Create a std::tm structure
    std::tm parsedTime = {};

    // Define the format string for parsing
    const char *format = "%Y-%m-%d";

    // Use strptime to parse the date string
    if (strptime(date_string, format, &parsedTime) == nullptr)
    {
        std::cerr << "Failed to parse the date string." << std::endl;
    }
    return std::mktime(&parsedTime);
}