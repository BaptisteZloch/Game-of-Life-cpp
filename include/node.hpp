#include <iostream>
#include <cmath>
#include <chrono>
#include <optional>
#include "utils.hpp"
#include "option.hpp"
#include "tree.hpp"

class Node
{
public:
    static int nb_nodes; // Static variable to count the number of nodes created
    std::optional<Node> node_up, node_down, next_lower_node, next_upper_node, next_mid_node;
    std::optional<double> option_price;

    // Constructor
    Node(double spot_price, TrinomialTree *tree)
        : spot_price(spot_price), tree(tree)
    {
        Node::nb_nodes++;
        forward_price = calculateForwardPrice(spot_price,
                                              this->tree->getMarket()->getInterestRate(),
                                              this->tree->getDeltaT());

        esperance = forward_price;
        calculate_probabilities();

        up_price = this->tree->getAlpha() * forward_price;
        down_price = forward_price / this->tree->getAlpha();
    }

    void calculate_probabilities()
    {
        variance = calculateVariance(spot_price,
                                     this->tree->getMarket()->getInterestRate(),
                                     this->tree->getMarket()->getVolatility(),
                                     tree->getDeltaT());

        p_down = calculateDownProbability(esperance,
                                          forward_price,
                                          variance,
                                          this->tree->getAlpha());

        p_up = calculateUpProbability(p_down,
                                      this->tree->getAlpha());

        p_mid = calculateMidProbability(p_up,
                                        p_down);
    }

    double price(Option *opt)
    {
        if (!next_mid_node.has_value())
        {
            option_price = opt->payoff(spot_price);
        }
        else if (!option_price.has_value())
        {
            option_price = this->tree->getDiscountFactor() * (p_up * next_upper_node->price(opt) +
                                                              p_mid * next_mid_node->price(opt) +
                                                              p_down * next_lower_node->price(opt));
        }

        if (opt->getExerciseType() == ExerciseType::American)
        {
            option_price = std::max(option_price.value(), opt->payoff(spot_price));
        }

        return option_price.value();
    }

private:
    double spot_price;
    TrinomialTree *tree;
    double forward_price;
    double esperance;
    double variance;
    double p_down;
    double p_up;
    double p_mid;
    double up_price;
    double down_price;
};
