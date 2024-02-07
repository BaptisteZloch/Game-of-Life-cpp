
#include "game_of_life.hpp"

int main(int argc, char *argv[])
{

    // Check if there are enough arguments
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <int:rows> <int:cols> <int:n_generations>" << std::endl;
        return 1; // Return an error code
    }

    // Parse the three integer arguments
    int arg1, arg2, arg3;

    try
    {
        arg1 = std::stoi(argv[1]);
        arg2 = std::stoi(argv[2]);
        arg3 = std::stoi(argv[3]);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1; // Return an error code
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Out of range: " << e.what() << std::endl;
        return 1; // Return an error code
    }

    GameOfLife *game = new GameOfLife(arg1, arg2, arg3);

    game->play();

    return 0;
}
