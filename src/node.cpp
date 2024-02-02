#include "node.hpp"

void Node::calculate_probabilities()
{
    variance = calculateVariance(spot_price,
                                 this->tree->getMarket()->getInterestRate(),
                                 this->tree->getMarket()->getVolatility(),
                                 this->tree->getDeltaT());
    p_down = calculateDownProbability(esperance,
                                      forward_price,
                                      variance,
                                      this->tree->getAlpha());

    p_up = calculateUpProbability(p_down, this->tree->getAlpha());

    p_mid = calculateMidProbability(p_up, p_down);
}

double Node::price(Option *opt)
{
    if (!next_mid_node.has_value())
    {
        option_price = opt->payoff(spot_price);
    }
    else if (!option_price.has_value())
    {
        option_price = tree->getDiscountFactor() * (p_up * next_upper_node->price(opt) +
                                                    p_mid * next_mid_node->price(opt) +
                                                    p_down * next_lower_node->price(opt));
    }

    if (opt->getExerciseType() == ExerciseType::American)
    {
        option_price = std::max(option_price.value(), opt->payoff(spot_price));
    }

    return option_price.value();
}
