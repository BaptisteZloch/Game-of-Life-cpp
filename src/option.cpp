#include "option.hpp"

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
