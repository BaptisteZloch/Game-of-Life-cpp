#pragma once
#include <iostream>
#include <chrono>
#include <variant>

enum class OptionType
{
    Call,
    Put
};
enum class ExerciseType
{
    American,
    European
};

class Option
{
public:
    Option(OptionType optionType, ExerciseType exerciseType, double strikePrice, std::chrono::system_clock::time_point maturityDate)
        : optionType(optionType), exerciseType(exerciseType), strikePrice(strikePrice), maturityDate(maturityDate) {}

    double payoff(double spot) const;

private:
    OptionType optionType;
    ExerciseType exerciseType;
    double strikePrice;
    std::chrono::system_clock::time_point maturityDate;
};
