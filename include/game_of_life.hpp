
#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

class GameOfLife
{
public:
    /// @brief Constructor of the GameOfLife class
    /// @param rows The number of rows in the grid
    /// @param cols The number of columns in the grid
    /// @param n_generations The number of generations to simulate
    GameOfLife(int rows = 20, int cols = 40, int n_generations = 100) : rows(rows), cols(cols), n_generations(n_generations)
    {
        if (rows <= 0 || cols <= 0)
        {
            throw std::invalid_argument("Invalid grid size");
        }
        if (rows > 100 || cols > 100)
        {
            throw std::invalid_argument("Grid size too large");
        }
        if (n_generations <= 0 || n_generations > 500)
        {
            throw std::invalid_argument("Invalid number of generations");
        }
        // Allocate memory for grid
        this->grid = new std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

        srand(time(0)); // Seed for random number generation

        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; ++j)
            {
                (*this->grid)[i][j] = rand() % 2 == 1;
            }
        }
    }

    /// @brief Destructor, free memory
    ~GameOfLife()
    {
        delete grid;
    }

    void play();

    int getRows() const { return rows; }
    int getCols() const { return cols; }

private:
    std::vector<std::vector<bool>> *grid;
    int rows = 20;
    int cols = 40;
    int n_generations = 100;

    void printGrid();
    void updateGrid();
    short countNeighbors(int row, int col);
};
