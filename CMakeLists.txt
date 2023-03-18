cmake_minimum_required(VERSION 3.24)
project(hex_game VERSION 1.0 LANGUAGES CXX)
add_executable(hex_game graph.cpp hex_board.cpp hex_game.cpp hex_random_ai.cpp hex_montecarlo_ai.cpp)
