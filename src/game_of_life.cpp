#include <chrono>
#include <omp.h>
#include "game_of_life.hpp"

/// @brief Compute the number of alive neighbors for a given cell
/// @param row The row of the cell
/// @param col The column of the cell
/// @return The number of alive neighbors
short GameOfLife::countNeighbors(int row, int col)
{
    short count = 0;
    short directions[] = {-1, 0, 1};

    for (int i : directions)
    {
        for (int j : directions)
        {
            if (i == 0 && j == 0)
                continue; // Avoid error when checking boundaries

            int newRow = row + i;
            int newCol = col + j;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
            {
                count += (*grid)[newRow][newCol].getState() ? 1 : 0; // Increment count if neighbor is alive
            }
        }
    }
    return count;
}

/// @brief Display the grid on the console
void GameOfLife::printGrid()
{
    system("clear"); // clear console, might be system("cls") on windows

    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            std::cout << ((*this->grid)[i][j].toString());
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/// @brief Update the grid according to the rules of the game
void GameOfLife::updateGrid()
{

#pragma omp parallel for
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            short neighbors = this->countNeighbors(i, j);

            if ((*this->grid)[i][j].getState())
            {
                // Cellule vivante
                (*this->grid)[i][j].setState((neighbors == 2 || neighbors == 3));
            }
            else
            {
                // Cellule morte
                (*this->grid)[i][j].setState(neighbors == 3);
            }
        }
    }
}

/// @brief Start and play the game
void GameOfLife::play()
{
    omp_set_num_threads(4); // comment this line to use the maximum number of cores
    auto start = std::chrono::high_resolution_clock::now();
    for (int generation = 1; generation <= this->n_generations; ++generation)
    {
        this->printGrid();
        this->updateGrid();
        usleep(100000); // Pause de 100 millisecondes entre les générations
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Playing the game took: "
              << (std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()) / 1000000
              << " seconds with " << omp_get_max_threads()
              << " cores in parallel (via OpenMP)"
              << std::endl;
}