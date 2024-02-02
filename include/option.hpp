#pragma once
#include <iostream>
#include <ctime>
#include <variant>
#include <string>

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
    Option(OptionType optionType,
           ExerciseType exerciseType,
           double strikePrice,
           time_t maturityDate)
        : optionType(optionType),
          exerciseType(exerciseType),
          strikePrice(strikePrice),
          maturityDate(maturityDate) {}

    double payoff(double spot) const;
    int getTimeToMaturity() const;
    ExerciseType getExerciseType();
    double getStrikePrice() { return strikePrice; }
    time_t getMaturityDate() { return maturityDate; }
    std::string getMaturityDateAsString() { return ctime(&maturityDate); }

private:
    OptionType optionType;
    ExerciseType exerciseType;
    double strikePrice;
    time_t maturityDate;
};
