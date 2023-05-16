#include <fstream>
#include <sstream>

#include <iostream>
#include <vector>
#include <set>
#include <random>
using namespace std;
std::vector<std::pair<int, int>> generateRandomGraph(int numNodes, int numEdges) {
    std::vector<std::pair<int, int>> edges;
    std::set<std::pair<int, int>> edgeSet;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, numNodes);

    // Generate random edges
    while (edges.size() < numEdges) {
        int from = dist(gen);
        int to = dist(gen);

        // Skip self-loops and duplicate edges
        if (from != to && edgeSet.count({from, to}) == 0) {
            edges.push_back({from, to});
            edgeSet.insert({from, to});
        }
    }

    return edges;
}

int main() {
    int numNodes = 20;  // Number of nodes in the graph
    int numEdges = 40;  // Number of edges in the graph

    // Generate random graph
    std::vector<std::pair<int, int>> graph = generateRandomGraph(numNodes, numEdges);

    fstream output_file;
    output_file.open("1.in", fstream::in | fstream::out | fstream::trunc);

    output_file << numNodes << endl << numEdges << endl;
    // Print the generated edges
    for (const auto& edge : graph) {
        output_file << edge.first << " " << edge.second << std::endl;
    }

output_file.close();
    return 0;
}
