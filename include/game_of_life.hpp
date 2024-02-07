
#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

class GameOfLife
{
public:
    GameOfLife()
    {
        // Allocate memory for grid
        this->grid = new std::vector<std::vector<bool>>(ROWS, std::vector<bool>(COLS, false));

        srand(time(0)); // Seed for random number generation

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                (*this->grid)[i][j] = rand() % 2 == 1;
            }
        }
    }

    ~GameOfLife()
    {
        delete grid;
    }

    void printGrid();
    void updateGrid();

private:
    std::vector<std::vector<bool>> *grid;
    const int ROWS = 20;
    const int COLS = 40;

    int countNeighbors(int row, int col)
    {
        int count = 0;
        int directions[] = {-1, 0, 1};

        for (int i : directions)
        {
            for (int j : directions)
            {
                if (i == 0 && j == 0)
                    continue; // Avoid error when checking boundaries

                int newRow = row + i;
                int newCol = col + j;

                if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS)
                {
                    count += (*grid)[newRow][newCol] ? 1 : 0; // Increment count if neighbor is alive
                }
            }
        }

        return count;
    }
};
