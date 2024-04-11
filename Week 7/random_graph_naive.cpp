#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>


struct Graph {
    std::unordered_map<int, std::vector<int>> adjacency_list;
};

// Function to generate a random graph
std::unordered_map<int, std::vector<int>> generateRandomGraph(int number_of_vertices, double edge_probability, unsigned int seed) {
    std::unordered_map<int, std::vector<int>> adj_list;

    // Explicit seed
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Iterate over all pairs of vertices and add edges with probability edge_probability
    for (int i = 0; i < number_of_vertices; ++i) {
        for (int j = i + 1; j < number_of_vertices; ++j) {
            if (dis(gen) < edge_probability) {
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }
    }

    return adj_list;
}

void printGraph(const Graph& graph) {
    std::cout << "Graph:\n";
    for (const auto& [vertex, neighbours] : graph.adjacency_list) {
        std::cout << vertex << ": ";
        for( int neighbour : neighbours) {
            std::cout << neighbour << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main() {
    Graph g;
    int n = 100;
    std::vector<double> probabilities{1, 0, 0.5};

    for (double p : probabilities){
        g.adjacency_list = generateRandomGraph(n, p, 22);
        printGraph(g);
    }
}
