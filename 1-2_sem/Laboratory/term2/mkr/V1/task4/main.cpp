#include <iostream>
#include <fstream>
using namespace std;
struct pair
{
    int winner;
    int loser;
};
bool read_from_file(int **graph, const int size, ifstream &f)
{
    // FILE *f = fopen("graph.txt", "r");
    int tmp;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // fread(&graph[i][j], 1, sizeof(int), f);
            f >> tmp;
            graph[i][j] = tmp;
        }
    }

}
void print(int **graph, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
}
bool if_cyclic(int **graph, int size, int winner, int loser)
{
    for (int i = 0; i < size; i++)
    {
        if (graph[loser][i])
            if ((i == winner) || (i == loser))
                return true;
            else if (graph[loser][i] && graph[i][loser])
                return true;
            else if (if_cyclic(graph, size, winner, i))
                return true;
    }
    return false;
}
bool check_for_cycle(int **graph, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (graph[i][j])
                if (i == j)
                    return true;
                else if (graph[j][i])
                    return true;
                else if (if_cyclic(graph, size, i, j))
                {
                    return true;
                }
        }
    }
    return false;
}
int main()
{
    ifstream f("graph.txt");
    int size;
    f >> size;
    int **graph = new int *[size];
    for (int i = 0; i < size; i++)
        graph[i] = new int[size];

    read_from_file(graph, size, f);
    print(graph, size);
    if (check_for_cycle(graph, size))
        cout << "The graph is cycled!\n";
    else
        cout << "The graph isn't cycled\n";

    for (int i = 0; i < size; i++)
        delete[] graph[i];
    delete[] graph;
    f.close();
    return 0;
}
