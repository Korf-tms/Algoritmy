#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using std::unordered_map, std::vector, std::string, std::ifstream;


struct Graph {
    unordered_map<int, vector<int>> adjacency_list;
    unordered_map<int, string> vertex_names;
    unordered_map<int, int> vertex_to_mat_index;
    int no_of_vertices;
    int no_of_edges;
};


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

Graph readGraphFromFile(const string& filename) {
    Graph graph;
    ifstream inputFile(filename);
    if (not inputFile){
        std::cerr << "Unable to open the input file" << std::endl;
        return graph;
    }

    string line;
    int vertex_label, friend_label;
    int num_edges = 0;
    int index = 0;
    char colon;
    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        ss >> vertex_label >> colon;
        // TODO: Cover the case of isolated vertex v1:(nothing)
        while(ss >> friend_label) {
            // check if the edge is already there
            if (find(graph.adjacency_list[vertex_label].begin(), graph.adjacency_list[vertex_label].end(), friend_label)
                    == graph.adjacency_list[vertex_label].end()) {
                graph.adjacency_list[vertex_label].emplace_back(friend_label);
                // edge of type (v, v) needs special treatment
                if( friend_label != vertex_label) {
                    graph.adjacency_list[friend_label].emplace_back(vertex_label);
                }
            num_edges += 1;}
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
        printGraph(graph);
    }
    inputFile.close();
    graph.no_of_edges = num_edges;
    graph.no_of_vertices = graph.adjacency_list.size();
    return graph;
}

void constructIndexingMap(Graph& graph) {
    int index = 0;
    unordered_map<int, int> res;
    for (const auto& kv: graph.adjacency_list) {
        res[kv.first] = index;
        index += 1;
    }
    graph.vertex_to_mat_index = res;
}


void printGraphIndexingMap(const Graph& graph) {
    std::cout << "Graph vertex to index map:\n";
    for (const auto& [vertex, index] : graph.vertex_to_mat_index) {
        std::cout << vertex << ": " << index << ", ";
    }
    std::cout << std::endl;
}

vector<vector<int>> createAdjacencyMatrix(const Graph& graph) {
    int n = graph.no_of_vertices;
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for(const auto& [vertex, friends] : graph.adjacency_list) {
        for(int friend_ : friends) {
            matrix[graph.vertex_to_mat_index.at(vertex)][graph.vertex_to_mat_index.at(friend_)] = 1;
            matrix[graph.vertex_to_mat_index.at(vertex)][graph.vertex_to_mat_index.at(friend_)] = 1;
        }
    }
    return matrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (auto& line: matrix) {
        for(int val: line) {
            std:: cout << val << " ";
        }
        std::cout << "\n";
    }
}


int main(){
    Graph test_g;
    string infile_name = "test_g.txt";
    vector<vector<int>> adjacency_mat;

    test_g = readGraphFromFile(infile_name);
    printGraph(test_g);
    constructIndexingMap(test_g);
    printGraphIndexingMap(test_g);
    adjacency_mat = createAdjacencyMatrix(test_g);
    printMatrix(adjacency_mat);
    return 0;
}
