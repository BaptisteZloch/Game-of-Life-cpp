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
    ExerciseType getExerciseType() { return this->exerciseType; };
    OptionType getOptionType() { return this->optionType; };
    std::string getExerciseTypeAsString()
    {
        switch (this->exerciseType)
        {
        case ExerciseType::American:
            return "American";
            break;
        case ExerciseType::European:
            return "European";
            break;
        default:
            return "European";
            break;
        }
    };
    std::string getOptionTypeAsString()
    {
        switch (this->optionType)
        {
        case OptionType::Call:
            return "Call";
            break;
        case OptionType::Put:
            return "Put";
            break;
        default:
            return "Call";
            break;
        }
    };
    double getStrikePrice() { return strikePrice; }
    time_t getMaturityDate() { return maturityDate; }

    std::string getMaturityDateAsString() { return ctime(&maturityDate); }

private:
    OptionType optionType;
    ExerciseType exerciseType;
    double strikePrice;
    time_t maturityDate;
};
