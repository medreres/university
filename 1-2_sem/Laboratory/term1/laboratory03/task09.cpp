//	Визначити довжину кривої, заданої у полярних координатах.
// Початковий і кінцевий кути a,b задаються користувачем. Формула
#include <iostream>
#include <cmath>
using namespace std;
double f(double x)
{
    return 3 * (1 + sin(x));
}
double f_derivative(double x)
{
    return 3 * cos(x);
}
double length(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i <= n - 1; i++)
    {
        sum += h * sqrt(f_derivative(a + i * h) * f_derivative(a + i * h) + f(a + i * h) * f(a + i * h));
    }
    return sum;
}
int main()
{
    double a, b;
    int n;
    a = -3.14159 / 6;
    b = 0;
    n = 100;
    cout << "by left rect : " << length(a, b, n) << endl;
    cin.get();
}