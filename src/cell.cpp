#include "cell.hpp"

bool Cell::getState() const { return state; };
void Cell::setState(bool state) { this->state = state; };
std::string Cell::toString() const { return this->state ? "█" : " "; };