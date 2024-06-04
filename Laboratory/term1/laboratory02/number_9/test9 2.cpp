#include <iostream>
#include <cmath>
using namespace std;
double length(double x1, double y1, double x2, double y2)
{
    double length_of_side = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return length_of_side;
}
int main()
{
    cout << "The sides of the first triangle(a,b,c): ";
    double a0[2] = {0, 0}, b0[2] = {0, 6}, c0[2] = {8, 0}; // координати вершин
    double a, b, c;
    a = length(a0[0], a0[1], b0[0], b0[1]);
    b = length(a0[0], a0[1], c0[0], c0[1]);
    c = length(c0[0], c0[1], b0[0], b0[1]);
    double ab[2] = {b0[0] - a0[0], b0[1] - a0[1]}; // вектор трикутника
    cout << a << " " << b << " " << c << endl;

    cout << "The sides of the second triangle(a1,b1,c1): ";
    double a1[2] = {3, 2}, b1[2] = {3, 14}, c1[2] = {19, 2}; // координати вершин
    double A, B, C;
    A = length(a1[0], a1[1], b1[0], b1[1]);
    B = length(c1[0], c1[1], a1[0], a1[1]);
    C = length(c1[0], c1[1], b1[0], b1[1]);
    double AB[2] = {b1[0] - a1[0], b1[1] - a1[1]}; // вектор трикутника
    cout << A << " " << B << " " << C << endl;

    double dx;
    if (a / A == b / B && b / B == c / C)
    {
        dx = a / A;
        cout << "they are similar, dx = " << dx << endl;
    }
    else
    {
        cout << "They aren`t similar" << endl;
    }

    double angle = acos((ab[0] * AB[0] + ab[1] * AB[1]) / (a * A)) / M_PI * 180;
    cout << "Degree between triangles = " << angle << endl;

    double vector[2] = {a1[0] - a0[0], a1[1] - a0[1]};
    cout << "The vector of move = (" << vector[0] << ";" << vector[1] << ") \n" << endl;

    {
        cout << "The sides of the first triangle(a,b,c): ";
        double a0[2] = {0, 0}, b0[2] = {0, 3}, c0[2] = {4, 0}; // координати вершин
        double a, b, c;
        a = length(a0[0], a0[1], b0[0], b0[1]);
        b = length(a0[0], a0[1], c0[0], c0[1]);
        c = length(c0[0], c0[1], b0[0], b0[1]);
        double ab[2] = {b0[0] - a0[0], b0[1] - a0[1]}; // вектор трикутника
        cout << a << " " << b << " " << c << endl;

        cout << "The sides of the second triangle(a1,b1,c1): ";
        double a1[2] = {3, 4}, b1[2] = {4.5, 4}, c1[2] = {3, 2}; // координати вершин
        double A, B, C;
        A = length(a1[0], a1[1], b1[0], b1[1]);
        B = length(c1[0], c1[1], a1[0], a1[1]);
        C = length(c1[0], c1[1], b1[0], b1[1]);
        double AB[2] = {b1[0] - a1[0], b1[1] - a1[1]}; // вектор трикутника
        cout << A << " " << B << " " << C << endl;

        double dx;
        if (a / A == b / B && b / B == c / C)
        {
            dx = a / A;
            cout << "they are similar, dx = " << dx << endl;
        }
        else
        {
            cout << "They aren`t similar" << endl;
        }

        double angle = acos((ab[0] * AB[0] + ab[1] * AB[1]) / (a * A)) / M_PI * 180;
        cout << "Degree between triangles = " << angle << endl;

        double vector[2] = {a1[0] - a0[0], a1[1] - a0[1]};
        cout << "The vector of move = (" << vector[0] << ";" << vector[1] << ")" << endl;
        cout << "" << endl;
    }

    {

        cout << "The sides of the first triangle(a,b,c): ";
        double a0[2] = {0, 1}, b0[2] = {2, 4}, c0[2] = {2.5, 0}; // координати вершин
        double a, b, c;
        a = length(a0[0], a0[1], b0[0], b0[1]);
        b = length(a0[0], a0[1], c0[0], c0[1]);
        c = length(c0[0], c0[1], b0[0], b0[1]);
        double ab[2] = {b0[0] - a0[0], b0[1] - a0[1]}; // вектор трикутника
        cout << a << " " << b << " " << c << endl;

        cout << "The sides of the second triangle(a1,b1,c1): ";
        double a1[2] = {3, 2}, b1[2] = {3, 1}, c1[2] = {19, 2}; // координати вершин
        double A, B, C;
        A = length(a1[0], a1[1], b1[0], b1[1]);
        B = length(c1[0], c1[1], a1[0], a1[1]);
        C = length(c1[0], c1[1], b1[0], b1[1]);
        double AB[2] = {b1[0] - a1[0], b1[1] - a1[1]}; // вектор трикутника
        cout << A << " " << B << " " << C << endl;

        double dx;
        if (a / A == b / B && b / B == c / C)
        {
            dx = a / A;
            cout << "they are similar, dx = " << dx << endl;
        }
        else
        {
            cout << "They aren`t similar" << endl;
        }

        double angle = acos((ab[0] * AB[0] + ab[1] * AB[1]) / (a * A)) / M_PI * 180;
        cout << "Degree between triangles = " << angle << endl;

        double vector[2] = {a1[0] - a0[0], a1[1] - a0[1]};
        cout << "The vector of move = (" << vector[0] << ";" << vector[1] << ")" << endl;
    }
    cin.get();
}