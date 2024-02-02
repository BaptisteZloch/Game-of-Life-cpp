#pragma once
#include "utils.hpp"
#include "option.hpp"
#include "market.hpp"

class TrinomialTree
{
public:
    const int n_days = 260; // Number of trading days in a year

    TrinomialTree(Market *market, int n_steps) : market(market), n_steps(n_steps){};

    double price(Option *opt);

    double getDeltaT() { return this->deltaT; };
    double getAlpha() { return this->alpha; };
    double getDiscountFactor() { return this->discount_factor; };
    Market *getMarket() { return this->market; };

private:
    Market *market;
    Node *root;
    int n_steps;
    double deltaT;
    double alpha;
    double discount_factor;

    void build_tree();
    Node *constructNextGeneration(Node *prev_trunc_node);
    void computeNextNodes(Node *current_node);
    void computeNextNodesUpward(Node *current_node);
    void computeNextNodesDownward(Node *current_node);
};
