// https://www.geeksforgeeks.org/graph-and-its-representations/
#include <iostream>
#include <vector>
#include "graphs.hpp"
using namespace std;
int main()
{
    vector<int> adj[V];
    // add_edge(adj, 0, 1);
    // add_edge(adj, 0, 4);
    // add_edge(adj, 1, 2);
    // add_edge(adj, 1, 3);
    // add_edge(adj, 1, 4);
    // add_edge(adj, 2, 3);
    // add_edge(adj, 3, 4); 
    // print_graph(adj, V);

    int matr[V][V] = {};
    if (!graph_read((char *)"graph.txt", matr, adj))
    {
        cout << "Err reading" << endl;
        return 1;
    }
    print_matr(matr);
    print_graph(adj, V);
    cout << '\n' << "Determinent of the matrix equals: "
         << det_matr(matr, V) << "\n\n";

    // getting vertixes of graph
    vertix arr[V]; // empty array
    get_vertex(arr, adj, V);
    cout << endl;
    print_vertex(arr, V);
    // sort_bubble(arr, V);
    // sort_insertion(arr, V);
    // sort_cocktail(arr, V);
     sort_quick(arr, V);
    // sort_merge(arr, V);
    // sort_shell(arr, V);

    cout << "\nSorted\n";
    print_vertex(arr, V);
}
