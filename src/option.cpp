#include "option.hpp"
#include <ctime>

double Option::payoff(double spot) const
{
    if (this->optionType == OptionType::Call)
    {
        return std::max(spot - this->strikePrice, 0.0);
    }
    else
    {
        return std::max(this->strikePrice - spot, 0.0);
    }
};

int Option::getTimeToMaturity() const
{
    return (this->maturityDate - time(0)) / 60 / 60 / 24;
}