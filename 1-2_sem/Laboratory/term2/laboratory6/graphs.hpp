#ifndef GRAPHS_HPP
#define GRAPHS_HPP
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
const int V = 5;
struct vertix
{
    int key;
    int sets;
};
void add_edge(vector<int> adj[], int u, int v);
void print_graph(const vector<int> adj[], const int &V);
int to_degree(int num, int deg);
void sub_matrix(int matr[V][V], int tmp[V][V], int p, int q, int n);
double det_matr(int matr[V][V], int n);
void get_deter(int matr[V][V], vector<int> adj[]);
void print_matr(const int matr[V][V]);
bool graph_read(char *path, int matr[V][V], vector<int> adj[]);
void get_vertex(vertix arr[], vector<int> adj[], int V);
void print_vertex(vertix arr[], int V);
void sort_bubble(vertix arr[], int size);
void sort_insertion(vertix arr[], int size);
void sort_cocktail(vertix arr[], int size);
void sort_quick(vertix arr[], int size);
void qcksrt(vertix arr[], int low, int high);
int partition(vertix arr[], int low, int high);
void sort_merge(vertix arr[],int size);
void mrgsrt(vertix arr[], int l, int h);
void merge(vertix arr[], int l, int m, int h);
void sort_shell(vertix arr[], int size);
#endif
