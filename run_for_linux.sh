# Create the out directory if not exists
[ -d "out" ] || mkdir "out"
# Compiling the project
g++ -I./include -std=c++20 -Wall -g -O3 src/game_of_life.cpp src/cell.cpp src/main.cpp  -o out/main.out -march=native -fopenmp 
# Running the project with rows cols n_generation arguments.
out/main.out 50 50 100
