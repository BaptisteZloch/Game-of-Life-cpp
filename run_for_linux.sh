g++ -I./include -std=c++20 -Wall -g -O3 src/game_of_life.cpp src/cell.cpp src/main.cpp  -o out/main.out -march=native -fopenmp 
out/main.out 50 50 100