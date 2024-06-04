#include <iostream>
#include "sparse_matrix.hpp"
int main()
{

    {
        using namespace std;
        Matrix matr(10, 10);
        matr.read("matrix1.txt");
        Matrix matr2(10, 10);
        matr2.read("matrix2.txt");
        cout << matr * matr2;
        cout << matr << endl;
        (matr2 * matr).save("save.txt");
        // cout << matr + matr2 << endl;
    }
}
