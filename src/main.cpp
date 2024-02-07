#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "game_of_life.hpp"

int main()
{
    GameOfLife game;

    for (int generation = 1; generation <= 100; ++generation)
    {
        game.printGrid();
        game.updateGrid();
        usleep(100000); // Pause de 100 millisecondes entre les générations
    }

    return 0;
}
