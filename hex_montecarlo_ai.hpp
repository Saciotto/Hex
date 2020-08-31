#ifndef HEX_MONTECARLO_AI_HPP
#define HEX_MONTECARLO_AI_HPP

#include "hex_board.hpp"

class hex_montecarlo_ai
{
public:

    // Plays using montecarlo strategy.
    void play(hex_board& b);

private:

    // Tests how many times this move can lead to a victory.
    int test_move(unsigned int move, hex_board& b);
};

#endif // HEX_MONTECARLO_AI_HPP
