#include "hex_montecarlo_ai.hpp"
#include "hex_random_ai.hpp"

using namespace std;

void hex_montecarlo_ai::play(hex_board& b)
{
    auto wins = vector<int>(b.size(), 0);

    for (unsigned int i = 0; i < b.size(); i++) {
        wins[i] = test_move(i, b);
    }

    unsigned int max = 0;
    for (unsigned int i = 0; i < b.size(); i++) {
        if (wins[i] > wins[max])
            max = i;
    }

    b.play(max);
}

int hex_montecarlo_ai::test_move(unsigned int move, hex_board &b)
{
    hex_random_ai rai;
    int wins = 0;

    int times = 4000 / (b.size() + 1 - b.turn());
    if (times > 200) times = 200;

    for (int i = 0; i < times; i++) {
        hex_board c(b);
        bool legal_move = c.play(move);
        if (!legal_move)
            return -1000;

        while (c.turn() < c.size()) {
            rai.play(c);
        }

        if (c.who_won() == b.turn_of_who()) {
            wins++;
        }
    }

    return wins;
}
