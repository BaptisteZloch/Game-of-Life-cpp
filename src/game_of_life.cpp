#include "game_of_life.hpp"

void GameOfLife::printGrid()
{
    system("clear"); // Efface l'écran pour une meilleure visibilité (Linux/Mac)
    // system("cls");  // Utiliser cette ligne pour Windows

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            std::cout << ((*this->grid)[i][j] ? "█" : " ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GameOfLife::updateGrid()
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            int neighbors = this->countNeighbors(i, j);

            if ((*this->grid)[i][j])
            {
                // Cellule vivante
                (*this->grid)[i][j] = (neighbors == 2 || neighbors == 3);
            }
            else
            {
                // Cellule morte
                (*this->grid)[i][j] = (neighbors == 3);
            }
        }
    }
}