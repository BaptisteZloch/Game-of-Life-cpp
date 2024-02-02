#pragma once
#include <cmath>

double calculateDiscountFactor(double interest_rate, double delta_t)
{
    return exp(-interest_rate * delta_t);
}

double calculateForwardPrice(double spot_price, double interest_rates, double delta_t)
{
    return spot_price * exp(interest_rates * delta_t);
}

double discountValue(
    double value_to_discount, double interest_rates, double delta_t)
{
    return value_to_discount * calculateDiscountFactor(
                                   interest_rates, delta_t);
}
double calculateAlpha(double volatility, double delta_t, int factor = 3)
{
    return exp(volatility * sqrt(factor * delta_t));
}

double calculateVariance(double spot_price, double interest_rate, double volatility, double delta_t)
{
    return ((pow(spot_price, 2)) * exp(2 * interest_rate * delta_t) * (exp((pow(volatility, 2)) * delta_t) - 1));
}

double calculateDownProbability(double esperance, double forward_price, double variance, double alpha)
{
    return ((pow(esperance, -2)) * (variance + pow(forward_price, 2)) - 1 - (alpha + 1) * ((pow(esperance, -1)) * forward_price - 1)) / ((1 - alpha) * ((pow(alpha, -2)) - 1));
}

double calculateUpProbability(double down_probability, double alpha)
{
    return down_probability / alpha;
}

double calculateUpProbabilityWithDividend(double down_probability, double alpha, double esperance, double forward_price)
{
    return (pow((alpha - 1), -1)) * ((pow(esperance, -1)) * forward_price - 1 - ((pow(alpha, -1)) - 1) * down_probability);
}

double calculateMidProbability(double up_probability,
                               double down_probability)
{
    return 1 - (down_probability + up_probability);
}
