#include "graphs.hpp"
void add_edge(vector<int> adj[], int u, int v)
{
    // int size = adj[u].size();
    // for (int i = 0; i < size; i++)
    // {
    //     if (adj[u][i] == v)
    //         return;
    // }
    // size = adj[v].size();f
    // for (int i = 0; i < size; i++)
    // {
    //     if (adj[v][i] == u)
    //         return;
    // }

    adj[u].push_back(v);
    // adj[v].push_back(u);
}
void print_graph(const vector<int> adj[], const int &V)
{
    for (int i = 0; i < V; ++i)
    {
        cout << "\n Adjacency list of vertex " << i
             << "\n head ";
        for (auto x : adj[i])
            cout << "-> " << x;
        cout << '\n';
    }
}
int to_degree(int num, int deg)
{
    if (deg == 0)
    {
        return 1;
    }
    return num * to_degree(num, deg - 1);
}
void sub_matrix(int matr[V][V], int tmp[V][V], int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                tmp[i][j++] = matr[row][col];
            }
            if (j == n - 1)
            {
                j = 0;
                i++;
            }
        }
    }
}
double det_matr(int matr[V][V], int n)
{
    double det = 0;
    if (n == 1)
    {
        return matr[0][0];
    }
    else if (n == 2)
    {
        return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
    }
    int temp[V][V], sign = 1;
    for (int i = 0; i < n; i++)
    {
        sub_matrix(matr, temp, 0, i, n);
        det += sign * matr[0][i] * det_matr(temp, n - 1);
        sign *= -1;
    }
    return det;
}
void get_deter(int matr[V][V], vector<int> adj[])
{
    for (int i = 0; i < V; i++)
    {
        int size = adj[i].size();
        for (int j = 0; j < size; j++)
        {
            int ind = adj[i][j];
            matr[ind][i] = matr[i][ind] = 1;
        }
    }
}
void print_matr(const int matr[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << matr[i][j] << ' ';
        }
        cout << endl;
    }
}
bool graph_read(char *path, int matr[V][V], vector<int> adj[])
{
    FILE *f = fopen(path, "r");
    if (f == nullptr)
    {
        return false;
    }
    int i = 0, j = 0, tmp;
    while (fscanf(f, "%i", &tmp))
    {
        matr[i][j++] = tmp;
        if (j == V)
        {
            j = 0;
            i++;
        }
        if (i == V)
        {
            break;
        }
    }
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (matr[i][j])
                add_edge(adj, i, j);
        }
    }
    fclose(f);
    return true;
}
void get_vertex(vertix arr[], vector<int> adj[], int V)
{
    for (int i = 0; i < V; i++)
    {
        arr[i].sets = adj[i].size();
        arr[i].key = i;
    }
}
void print_vertex(vertix arr[], int V)
{
    for (int i = 0; i < V; i++)
    {
        cout << "Vertix " << arr[i].key << " sets " << arr[i].sets << '\n';
        // cout << arr[i] << ' ';
    }
}
void sort_bubble(vertix arr[], int size)
{
    vertix swap;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j].sets > arr[j + 1].sets)
            {
                swap = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap;
            }
        }
    }
}
void sort_insertion(vertix arr[], int size)
{
    vertix swap;
    int j;
    for (int i = 1; i < size; i++)
    {
        swap = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].sets > swap.sets)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = swap;
    }
}
void sort_cocktail(vertix arr[], int size)
{
    vertix swap;
    bool swapped = true;
    int start = 0;
    int end = size - 1;
    while (swapped)
    {
        for (int i = 0; i < end; i++)
        {
            if (arr[i].sets > arr[i + 1].sets)
            {
                swap = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = swap;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
        swapped = false;
        end--;

        for (int i = end; i >= start; --i)
        {
            if (arr[i].sets < arr[i - 1].sets)
            {
                swap = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = swap;
                swapped = true;
            }
        }
        ++start;
    }
}
void sort_quick(vertix arr[], int size)
{
    qcksrt(arr, 0, size - 1);
}
void qcksrt(vertix arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        qcksrt(arr, low, pivot - 1);
        qcksrt(arr, pivot + 1, high);
    }
}
int partition(vertix arr[], int low, int high)
{
    vertix pivot = arr[high];
    int i = low;
    vertix swap;
    for (int j = low; j < high; j++)
    {
        if (arr[j].sets < pivot.sets)
        {
            swap = arr[j];
            arr[j] = arr[i];
            arr[i] = swap;
            ++i;
        }
    }
    swap = arr[i];
    arr[i] = arr[high];
    arr[high] = swap;
    return i;
}
void sort_merge(vertix arr[], int size)
{
    mrgsrt(arr, 0, size - 1);
}
void mrgsrt(vertix arr[], int low, int high)
{
    if (high > low)
    {
        int middle = low + (high - low) / 2;
        mrgsrt(arr, low, middle);
        mrgsrt(arr, middle + 1, high);
        merge(arr, low, middle, high);
    }
}
void merge(vertix arr[], int l, int m, int h)
{
    int const sub_arr_one = m - l + 1;
    int const sub_arr_two = h - m;
    vertix *l_arr = new vertix[sub_arr_one];
    vertix *r_arr = new vertix[sub_arr_two];
    for (int i = 0; i < sub_arr_one; i++)
    {
        l_arr[i] = arr[l + i];
    }
    for (int i = 0; i < sub_arr_two; i++)
    {
        r_arr[i] = arr[m + i + 1];
    }
    int index_sub_one = 0, index_sub_two = 0;
    int index_merge = l;
    while (index_sub_one < sub_arr_one && index_sub_two < sub_arr_two)
    {
        if (l_arr[index_sub_one].sets < r_arr[index_sub_two].sets)
        {
            arr[index_merge] = l_arr[index_sub_one];
            index_sub_one++;
        }
        else
        {
            arr[index_merge] = r_arr[index_sub_two];
            index_sub_two++;
        }
        index_merge++;
    }
    while (index_sub_one < sub_arr_one)
    {
        arr[index_merge] = l_arr[index_sub_one];
        index_merge++;
        index_sub_one++;
    }
    while (index_sub_two < sub_arr_two)
    {
        arr[index_merge] = r_arr[index_sub_two];
        index_merge++;
        index_sub_two++;
    }
}
void sort_shell(vertix arr[], int size)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            vertix temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].sets > temp.sets; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
