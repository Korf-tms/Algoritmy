import networkx as nx


def write_nx_graph_full(graph, filename):
    with open(filename, 'w') as my_file:
        for node in graph.nodes():
            friends = graph.neighbors(node)
            string_list = ", ".join(map(str, friends))
            my_file.write(f'{node}: {string_list}\n')


def write_nx_graph_pruned(graph, filename):
    with open(filename, 'w') as my_file:
        for line in nx.generate_adjlist(graph):
            # discard the lone vertex
            if line.find(' ') != -1:
                s_line = str(line)
                s_line = s_line.replace(' ', ', ').replace(',', ':', 1) + '\n'
                my_file.write(s_line)


if __name__ == '__main__':
    k6 = nx.complete_graph(6)
    write_nx_graph_pruned(k6, 'k6.txt')

    probabilies = [0.8, 0.4, 0.1]
    suffixes = ['g08', 'g04', 'g01']

    for p, suffix in zip(probabilies, suffixes):
        random_graph = nx.fast_gnp_random_graph(100, p)
        write_nx_graph_pruned(random_graph, f'random_{suffix}.txt')



