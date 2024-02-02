#include <ctime>
#include "utils.hpp"
#include "option.hpp"
#include "market.hpp"
#include "tree.hpp"
#include "node.hpp"

double TrinomialTree::price(Option *opt)
{
    this->deltaT = opt->getTimeToMaturity() / (n_steps * this->n_days);
    this->alpha = calculateAlpha(this->market->getVolatility(), deltaT);
    this->discount_factor = calculateDiscountFactor(this->market->getInterestRate(), deltaT);
    this->build_tree();
    double option_price = this->root->price(opt);
    return option_price;
}

void TrinomialTree::build_tree()
{
    this->root = new Node(this->market->getSpotPrice(), *this);
    Node *current_mid = root;

    for (int i = 0; i < n_steps; ++i)
    {

        current_mid = constructNextGeneration(current_mid);
    }
}

Node *TrinomialTree::constructNextGeneration(Node *prev_trunc_node)
{
    computeNextNodes(prev_trunc_node);

    auto current_upper_neighbours = prev_trunc_node->node_up.get();
    while (current_upper_neighbours)
    {
        computeNextNodesUpward(current_upper_neighbours);
        current_upper_neighbours = current_upper_neighbours->node_up.get();
    }

    auto current_lower_neighbours = prev_trunc_node->node_down.get();
    while (current_lower_neighbours)
    {
        computeNextNodesDownward(current_lower_neighbours);
        current_lower_neighbours = current_lower_neighbours->node_down.get();
    }

    return prev_trunc_node->next_mid_node.get();
}

void TrinomialTree::computeNextNodes(Node *current_node)
{
    Node n(current_node->forward_price, *this);
    current_node->next_mid_node = std::make_unique<Node>(n);
    Node n_up(current_node->up_price, *this);
    current_node->next_upper_node = std::make_unique<Node>(n_up);
    current_node->next_upper_node->node_down = current_node->next_mid_node.get();
    current_node->next_mid_node->node_up = current_node->next_upper_node.get();
    Node n_down(current_node->down_price, *this);
    current_node->next_lower_node = std::make_unique<Node>(n_down);
    current_node->next_lower_node->node_up = current_node->next_mid_node.get();
    current_node->next_mid_node->node_down = current_node->next_lower_node.get();
}

void TrinomialTree::computeNextNodesUpward(Node *current_node)
{
    current_node->next_lower_node = current_node->node_down->next_mid_node.get();
    current_node->next_mid_node = current_node->node_down->next_upper_node.get();
    current_node->next_upper_node = std::make_unique<Node>(Node(current_node->up_price, *this));
    current_node->next_upper_node->node_down = current_node->next_mid_node.get();
    current_node->next_mid_node->node_up = current_node->next_upper_node.get();
}

void TrinomialTree::computeNextNodesDownward(Node *current_node)
{
    current_node->next_mid_node = current_node->node_up->next_lower_node.get();
    current_node->next_upper_node = current_node->node_up->next_mid_node.get();
    current_node->next_lower_node = std::make_unique<Node>(Node(current_node->down_price, *this));
    current_node->next_lower_node->node_up = current_node->next_mid_node.get();
    current_node->next_mid_node->node_down = current_node->next_lower_node.get();
}