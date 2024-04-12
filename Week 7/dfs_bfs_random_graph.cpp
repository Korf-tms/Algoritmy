#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <queue>

using std::vector, std::stack, std::unordered_map, std::cout, std::unordered_set, std::queue;

struct Graph
{
    unordered_map<int, vector<int>> adj_list;
    vector<vector<int>> adj_matrix;
    unordered_map<int, int> label_to_index_map;
};

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

// pruchod do hloubky
unordered_set<int> depthSearch(const Graph& g, int starting_point){
    stack<int> g_stack;
    unordered_set<int> visited;

    g_stack.push(starting_point);
    visited.insert(starting_point);

    while(not g_stack.empty()){
        int current = g_stack.top();
        g_stack.pop();

        // zpracovani vrcholu
        // cout << current << " ";

        for (int neighbour : g.adj_list.at(current)){
            if ( visited.find(neighbour) == visited.end() ){
                g_stack.push(neighbour);
                visited.insert(neighbour);
            }
        }
    }
    return visited;
}

// pruchod do hloubky
unordered_set<int> widthSearch(const Graph& g, int starting_point){
    queue<int> g_queue;
    unordered_set<int> visited;

    visited.insert(starting_point);
    g_queue.push(starting_point);

    while(not g_queue.empty()){
        int current = g_queue.front();
        g_queue.pop();

        for (int neighbour : g.adj_list.at(current)){
            if ( visited.find(neighbour) == visited.end() ){
                g_queue.push(neighbour);
                visited.insert(neighbour);
            }
        }
    }
    return visited;
}

int computeComponents(const Graph& g){
    if ( g.adj_list.empty() ){
        return 0;
    }
    int components = 1;
    unordered_set<int> visited, local_component;

    int starting_point = g.adj_list.begin()->first;

    while(true){
        local_component = depthSearch(g, starting_point);
        visited.insert(local_component.begin(), local_component.end());
        
        if ( visited.size() == g.adj_list.size()){
            break;
        }
        
        components += 1;
        // choose new starting point and repeat
        for (const auto& [vertex, others] : g.adj_list){ // spatne reseni, naslo by se snad i lepsi; jak implementovat navstivene?
            if (visited.find(vertex) == visited.end()){
                starting_point = vertex;
            }
        }
    }
    return components;
}

int main() {
    Graph graph;
    // Adding edges to the graph, super stupid way
    // should be implemented as member functon add_edge
    graph.adj_list[0] = {1, 2};
    graph.adj_list[1] = {0, 3, 4, 99};
    graph.adj_list[2] = {0, 4};
    graph.adj_list[3] = {1};
    graph.adj_list[4] = {1, 2};
    graph.adj_list[100] = {99, 1};
    graph.adj_list[99] = {100};

    graph.adj_list[55] = {66}; 
    graph.adj_list[66] = {55};

    // Starting vertex for DFS
    int start_vertex = 0;
    unordered_set<int> component;

    // find and print the component where start_vertex lies
    component =  depthSearch(graph, start_vertex);
    cout << "DFS given component:\n";
    for (auto item : component) { cout << item << " ";} cout << "\n";
    component = widthSearch(graph, start_vertex);
    cout << "BFS given component:\n";
    for (auto item : component) { cout << item << " ";} cout << "\n";

    cout << "Total number of components is: ";
    cout << computeComponents(graph) << "\n";

    // checking components in a random graph
    graph.adj_list = generateRandomGraph(100, 0.3, 4);

    for (const auto& [vertex, friends] : graph.adj_list) {
        cout << vertex << ": ";
        for (int item : friends){
            cout << item << " ";
        }
        cout << "\n";
    }

    cout << "Components in random graph: " << computeComponents(graph) << "\n";

    return 0;
}
