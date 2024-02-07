
#include "game_of_life.hpp"

int main()
{
    GameOfLife *game = new GameOfLife(20, 40, 100);

    game->play();

    return 0;
}
