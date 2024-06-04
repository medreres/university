//Дано функцію f(x), що всюди на [a,b] має похідну. Визначити всі нулі функції на відрізку [a,b]
#include <iostream>
#include <cmath>
using namespace std;
double f(double x)
{
    return sin(x);
}
int main()
{
    double a, b;
    a = -10;
    b = 10;
    for (double x = a; x <= b; x += 0.01)
    {
        if (round(f(x) * 100) / 100 == 0)
        {
            cout << "when x = " << round(x * 100) / 100 << " f(x)= " << round(f(x) * 100) / 100 << endl;
        }
    }
}