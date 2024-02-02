#pragma once

class Market
{
public:
    Market(double interestRate, double volatility, double spotPrice)
        : interestRate(interestRate), volatility(volatility), spotPrice(spotPrice) {}

    double getInterestRate()
    {
        return this->interestRate;
    }

    double getVolatility()
    {
        return this->volatility;
    }

    double getSpotPrice()
    {
        return this->spotPrice;
    }

private:
    double interestRate;
    double volatility;
    double spotPrice;
};
