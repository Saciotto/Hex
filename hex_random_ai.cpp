#include "hex_random_ai.hpp"

#include <random>

using namespace std;

void hex_random_ai::play(hex_board& b)
{
    bool valid_move;
    std::random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<unsigned int> distribution(0, b.size() - 1);
    do {
        valid_move = b.play(distribution(generator));
    } while (valid_move == false);
}
