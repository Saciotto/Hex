#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <ostream>

class graph
{
public:

    // Creates a graph based on number of nodes.
    graph(unsigned int no_nodes);

    // Adds to graph the edge from x to y, if it is not there.
    void insert_edge(unsigned int x, unsigned int y);

    // Tests whether there is an edge from node x to node y.
    bool has_edge(unsigned int x, unsigned int y) const;

protected:

    // Number of nodes
    unsigned int no_nodes;

    // List of all nodes and its neighbors.
    std::vector<std::vector<unsigned int>> nodes;

    // Outputs a string representation of the graph.
    friend std::ostream& operator<<(std::ostream& os, const graph& g);
};

#endif // GRAPH_HPP
