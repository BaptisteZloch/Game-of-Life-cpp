#pragma once
#include <iostream>
#include <chrono>

class Market {
public:
    Market(double interestRate, double volatility, double spotPrice, double dividendPrice, std::chrono::system_clock::time_point dividendExDate)
        : interestRate(interestRate), volatility(volatility), spotPrice(spotPrice), dividendPrice(dividendPrice), dividendExDate(dividendExDate) {}

private:
    double interestRate;
    double volatility;
    double spotPrice;
    double dividendPrice;
    std::chrono::system_clock::time_point dividendExDate;
};
