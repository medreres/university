//Вивести значення елементів масиву по спіралі (скатертина Улама)
#include <iostream>
using namespace std;
int main()
{
    cout << "Type a number :";
    int a;
    while (!(cin >> a))
    {
        cout << "You haven`t typed a number.Type a number : ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    
    const int A = a;
    int array[A][A];
    int num = A * A;

    for (int i = A - 1, j = A - 1, n = 0; i > -1; i--, j--, n++)
    {

        for (int k = j; k >= n; k--) // вліво
        {
            array[i][k] = num--;
        }

        for (int k = i - 1; k > n; k--) //вгору
        {
            array[k][n] = num--;
        }

        for (int k = n; k < j; k++) //вправо
        {
            array[n][k] = num--;
        }

        for (int k = n; k < i; k++) //вниз
        {
            array[k][i] = num--;
        }
    }

    for (int i = 0; i < A; i++)
    {
        for (int j = 0; j < A; j++)
        {
            cout << array[i][j] << "     ";
        }
        cout << endl;
    }
}