#ifndef HEX_BOARD_HPP
#define HEX_BOARD_HPP

#include "graph.hpp"

enum piece {
    EMPTY,
    RED,
    BLUE
};

class hex_board : public graph
{
public:

    // Creates a hsize x hsize hex board.
    hex_board(unsigned int hsize);

    // Copy constructor.
    hex_board(hex_board& b) = default;

    // Returns the game winner.
    piece who_won() const;

    // Tests whether there is an edge of pieces from node x to node y.
    bool has_edge(piece piece_color, unsigned int x, unsigned int y) const;

    // Tests whether there is a path of a piece connecting x and y.
    bool are_connected(piece piece_color, unsigned int x, unsigned int y) const;

    // Executes a move, returns true if the move is valid.
    bool play(unsigned int pos);
    bool play(unsigned int row, unsigned int col);
    bool play(piece player, unsigned int pos);
    bool play(piece player, unsigned int row, unsigned int col);

    // Gets the player that has the turn.
    piece turn_of_who() const;

    // Gets the size of the board.
    unsigned int size() const;

    // Gets the current turn number.
    unsigned int turn() const;

    // Outputs a string representation of the graph.
    friend std::ostream& operator<<(std::ostream& os, const hex_board& h);

private:

    //Sside size.
    unsigned int hsize;

    // Turn number
    unsigned int turn_count = 0;

    // Nodes linked to all nodes of an edge.
    // If left_edge node has a path to right_edge node so there is a path
    // between left and right edges.
    unsigned int left_edge;
    unsigned int right_edge;
    unsigned int top_edge;
    unsigned int botton_edge;

    // Color of the player that has the turn.
    piece player_turn = RED;

    // Piece distribution in the board.
    std::vector<piece> pieces;
};

#endif // HEX_BOARD_HPP
