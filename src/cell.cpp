#include "cell.hpp"

/// @brief Return the state of the cell
/// @return The state of the cell
bool Cell::getState() const
{
    return state;
};

/// @brief Set the state of the cell
/// @param state The new state of the cell
void Cell::setState(bool state)
{
    this->state = state;
};

/// @brief Print the cell to the console and it will print a black square if the cell is alive and a white square if the cell is dead
/// @return The string representation of the cell
std::string Cell::toString() const
{
    return this->state ? "█" : " ";
};