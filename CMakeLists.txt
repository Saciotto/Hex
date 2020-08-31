cmake_minimum_required (VERSION 2.6)
project (hex_game)
add_executable(hex_game graph.cpp hex_board.cpp hex_game.cpp hex_random_ai.cpp hex_montecarlo_ai.cpp)