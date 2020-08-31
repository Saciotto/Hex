#include "hex_board.hpp"

using namespace std;

#include <algorithm>

static const int no_edges = 4;

template <class T>
static bool contains(const vector<T>& set, T value)
{
    if (find(set.begin(), set.end(), value) != set.end()) {
        return true;
    }
    return false;
}

static unsigned int min_distance(const vector<int>& dist, const vector<unsigned int>& closed_set)
{
    int min = numeric_limits<int>::max();
    unsigned int min_index = 0;

    for (unsigned int i = 0; i < dist.size(); i++) {
        if (contains(closed_set, i)) {
            continue;
        }
        if (dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

hex_board::hex_board(unsigned int hsize):
    graph(hsize * hsize + no_edges), hsize(hsize)
{
    pieces = vector<piece>(no_nodes, piece());

    // Top-left corner.
    insert_edge(0, 1);
    insert_edge(0, hsize);

    // Botton-right corner.
    insert_edge(hsize * hsize - 1, hsize * (hsize - 1) - 1);
    insert_edge(hsize * hsize - 1, hsize * hsize - 2);

    // Top-right corner.
    insert_edge(hsize - 1, hsize - 2);
    insert_edge(hsize - 1, 2 * hsize - 2);
    insert_edge(hsize - 1, 2 * hsize - 1);

    // Botton-left corner.
    insert_edge(hsize * (hsize - 1), hsize * (hsize - 2));
    insert_edge(hsize * (hsize - 1), hsize * (hsize - 2) + 1);
    insert_edge(hsize * (hsize - 1), hsize * (hsize - 1) + 1);

    // Left edge
    for (unsigned int i = 1; i < hsize - 1; i++) {
        unsigned int idx = i * hsize;
        insert_edge(idx, idx - hsize);
        insert_edge(idx, idx + hsize);
        insert_edge(idx, idx + 1);
        insert_edge(idx, idx + 1 - hsize);
    }

    // Right edge
    for (unsigned int i = 1; i < hsize - 1; i++) {
        unsigned int idx = (i + 1) * hsize - 1;
        insert_edge(idx, idx - hsize);
        insert_edge(idx, idx + hsize);
        insert_edge(idx, idx - 1);
        insert_edge(idx, idx - 1 + hsize);
    }

    // Top edge
    for (unsigned int i = 1; i < hsize - 1; i++) {
        insert_edge(i, i - 1);
        insert_edge(i, i + 1);
        insert_edge(i, i + hsize);
        insert_edge(i, i + hsize - 1);
    }

    // Bottom edge
    for (unsigned int i = 1; i < hsize - 1; i++) {
        unsigned int idx = i + hsize * (hsize - 1);
        insert_edge(idx, idx - 1);
        insert_edge(idx, idx + 1);
        insert_edge(idx, idx - hsize);
        insert_edge(idx, idx - hsize + 1);
    }

    // Internal nodes
    for (unsigned int i = 1; i < hsize - 1; i++) {
        for (unsigned int j = 1; j < hsize - 1; j++) {
            unsigned int idx = i * hsize + j;
            insert_edge(idx, idx + 1);
            insert_edge(idx, idx - 1);
            insert_edge(idx, idx + hsize);
            insert_edge(idx, idx + hsize - 1);
            insert_edge(idx, idx - hsize);
            insert_edge(idx, idx - hsize + 1);
        }
    }

    // Edges
    unsigned int board_size = hsize * hsize;
    left_edge = board_size;
    pieces[left_edge] = BLUE;
    right_edge = board_size + 1;
    pieces[right_edge] = BLUE;
    top_edge = board_size + 2;
    pieces[top_edge] = RED;
    botton_edge = board_size + 3;
    pieces[botton_edge] = RED;

    // Link left edge to a winning condition node
    for (unsigned int i = 0; i < hsize; i++) {
        unsigned int idx = i * hsize;
        insert_edge(idx, left_edge);
    }

    // Link right edge to a winning condition node
    for (unsigned int i = 0; i < hsize; i++) {
        unsigned int idx = (i + 1) * hsize - 1;
        insert_edge(idx, right_edge);
    }

    // Link top edge to a winning condition node
    for (unsigned int i = 0; i < hsize; i++)  {
        insert_edge(i, top_edge);
    }

    // Link botton edge to a winning condition node
    for (unsigned int i = 0; i < hsize; i++)  {
        unsigned int idx = i + hsize * (hsize - 1);
        insert_edge(idx, botton_edge);
    }
}

piece hex_board::who_won() const
{
    if (are_connected(RED, top_edge, botton_edge)) {
        return RED;
    } else if (are_connected(BLUE, left_edge, right_edge)) {
        return BLUE;
    }
    return EMPTY;
}

bool hex_board::has_edge(piece piece_color, unsigned int x, unsigned int y) const
{
    if (pieces[x] != piece_color || pieces[y] != piece_color)
        return false;
    return graph::has_edge(x, y);
}

bool hex_board::are_connected(piece piece_color, unsigned int x, unsigned int y) const
{
    vector<int> distances(no_nodes, numeric_limits<int>::max());
    vector<int> parents(no_nodes, -1);
    vector<unsigned int> closed_set;

    distances[x] = 0;

    for (unsigned int i = 0; i < no_nodes - 1; i++) {

        unsigned int u = min_distance(distances, closed_set);

        closed_set.push_back(u);

        for (unsigned int v = 0; v < no_nodes; v++) {
            if (contains(closed_set, v)) {
                continue;
            }

            if (!has_edge(piece_color, u, v)) {
                continue;
            }

            if (distances[u] + 1 < distances[v]) {
                parents[v] = static_cast<int>(u);
                distances[v] = distances[u] + 1;
            }
        }
    }

    for (int parent = parents[y]; parent >= 0; parent = parents[static_cast<unsigned int>(parent)]) {
        if (parent == static_cast<int>(x))
            return true;
    }

    return false;
}

unsigned int hex_board::turn() const
{
    return turn_count;
}

bool hex_board::play(unsigned int pos)
{
    return play(player_turn, pos);
}

bool hex_board::play(unsigned int row, unsigned int col)
{
    return play(player_turn, row, col);
}

bool hex_board::play(piece player, unsigned int pos)
{
    if (pos >= no_nodes)
        return false;
    if (pieces[pos] != EMPTY)
        return false;
    pieces[pos] = player;
    player_turn = (player == RED) ? BLUE : RED;
    turn_count++;
    return true;
}

bool hex_board::play(piece player, unsigned int row, unsigned int col)
{
    if (row > hsize || col > hsize)
        return false;
    unsigned int pos = (row - 1) * hsize + (col - 1);
    return play(player, pos);
}

piece hex_board::turn_of_who() const
{
    return player_turn;
}

unsigned int hex_board::size() const
{
    return hsize * hsize;
}

std::ostream& operator<<(std::ostream& os, const hex_board& h)
{
    for (unsigned int j = 0; j < h.hsize; j++) {
        os << "   ";
        if (j == 0) {
            for (unsigned int i = 0; i < h.hsize; i++) {
                os << i + 1 << (i + 1>= 10 ? "  " : "   ");
            }
            os << endl;
        } else {
            for (unsigned int idx = 0; idx < j; idx++) {
                os << ((idx + 1 == j) ? " " : "  ");
            }

            for (unsigned int i = 0; i < h.hsize; i++) {
                if (i != 0) {
                    os << "/ ";
                }
                os << "\\ ";
            }
            os << endl;
        }
        os << j + 1 << (j + 1 >= 10 ? " " : "  ");
        for (unsigned int i = 0; i < j; i++) {
            os << "  ";
        }
        for (unsigned int i = 0; i < h.hsize; i++) {
            if (i != 0) {
                os << " - ";
            }

            unsigned int pos = j * h.hsize + i;
            switch(h.pieces[pos]) {
            case EMPTY:
                os << ".";
                break;
            case RED:
                os << "X";
                break;
            case BLUE:
                os << "O";
            }
        }
        os << endl;
    }
    return os;
}
