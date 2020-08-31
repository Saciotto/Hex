#include "graph.hpp"

#include <algorithm>

using namespace std;

graph::graph(unsigned int no_nodes):
    no_nodes(no_nodes)
{
    nodes = vector<vector<unsigned int>>(no_nodes, vector<unsigned int>());
}

void graph::insert_edge(unsigned int x, unsigned int y)
{
    if (x == y) return;
    if (has_edge(x, y)) return;
    nodes[x].push_back(y);
    nodes[y].push_back(x);
}

bool graph::has_edge(unsigned int x, unsigned int y) const
{
    auto it = find(nodes[x].begin(), nodes[x].end(), y); 
    return (it != nodes[x].end());
}

ostream& operator<<(ostream& os, const graph& g)
{
    for (unsigned int i = 0; i < g.nodes.size(); i++) {
        os << i;
        for (auto node: g.nodes[i]) {
            os << " -> " << node;
        }
        os << endl;
    }
    return os;
}
