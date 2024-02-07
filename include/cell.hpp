#pragma once
#include <string>

class Cell
{
public:
    Cell(bool state = false) : state(state){};
    bool getState() const;
    void setState(bool state);
    std::string toString() const;

private:
    bool state;
};