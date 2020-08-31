
#include "graph.hpp"
#include "hex_board.hpp"
#include "hex_random_ai.hpp"
#include "hex_montecarlo_ai.hpp"

#include <iostream>

using namespace std;

static void clear_scr()
{    
#ifdef __linux
    cout << "\033c";
#elif defined _WIN32
    // This is bad, but this is easy.
    cout << flush;
    system("cls");
#endif
}

static void show_board(const hex_board& b)
{
    clear_scr();
    cout << "   ##################" << endl;
    cout << "   ##   Hex game   ##" << endl;
    cout << "   ##################" << endl << endl;
    cout << "The player tries to make a path from top to bottom, while the" << endl;
    cout << "AI tries to make a path from left to right." << endl << endl;
    cout << b << endl;
}

int main()
{
    hex_board b(7);
    hex_montecarlo_ai ai;

    while (b.who_won() == EMPTY) {

        show_board(b);


        unsigned int row, col;

        bool valid_move;
        do {
            cout << "Type a row and a col (e.g.: 2 5): ";
            cin >> row >> col;
            valid_move = b.play(row, col);
        } while (!valid_move);

        if (b.who_won() != EMPTY)
            break;

        show_board(b);
        cout << "Thinking..." << endl;

        ai.play(b);
    }

    show_board(b);
    cout << ((b.who_won() == RED) ? "You won" : "You lost") << endl;
    return 0;
}
