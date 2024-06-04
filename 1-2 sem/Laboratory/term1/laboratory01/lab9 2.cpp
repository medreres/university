#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    const int R = 10;
    int x, y, left_over[R] = {0}, division, whole_part[R] = {0}, num = 0;
    bool is_periodic = false;
    cout << "type number a and b " << endl;
    cin >> x >> y;
    if (x > y)                                                                                //Знаходжу цілу частину від ділення й підготовлюю до другої умови
    {
        for (int i = 0; x > y; i++)
        {
            whole_part[i] = x / y;
            x = x - whole_part[i] * y;
        }                                              
    }
    if (x < y)                                                                                 //Шукаю частку і додаю в масив
    {
        for (int i = 0; i < R; i++)
        {
            division = 10 * x / y;
            left_over[i] = division;
            //cout << left_over[i] << endl;
            x = 10 * x - y * division;
        }
    }
    cout << "" << endl;
    int period;                                                                                 // /period - відстань між однаковими елементами, період > 1 бо бувають два числа не в періоді
    for (int i = 1; i < R; i++)
    {
        for (int i2 = i - 1; i2 > -1; i2--)
        {
            if (left_over[i] == left_over[i2] && abs(i2 - i) > 1)                                   // номер елемента з якого починається період
            {
                is_periodic = true;
                num = i;
                period = abs(i2 - i);
                break;
            }
        }
        if (is_periodic)
            break;
    }
    if (whole_part[0] == 0)                                                                                 // для x<y
    {
        cout << "0.";
        for (int i = 0; i < num; i++)
        {
            if (i == num - period)
            {
                cout << "(";
            }
            cout << left_over[i];
        }
        cout << ")" << endl;
    }
    else                                                                                                    // для x>y
    {
        for (int i = 0; whole_part[i] != 0; i++)
        {
            cout << whole_part[i];
        }
        cout << ".";
        for (int i = 0; i < num; i++)
        {
            if (i == num - period)
            {
                cout << "(";
            }
            cout << left_over[i];
        }
        cout << ")" << endl;
    }
}