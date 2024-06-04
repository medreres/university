#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int number(0), num(0), r, number_1(0);
    cout << "Type number : ";
    cin >> number;
    vector<int> a(0);
    for (int i = 1; i < number; i++)
    {
        if (number % i == 0)
        {
            a.push_back(i); // присвоюю значенню масивові
            num++;

        }
    }
    for (int i = 0; i < num; i++)
    {
        number_1 += a[i];
    }
    if (number_1 == number) //перевіряю чи є число ідеальним
    {
        cout << "this is perfect number" << endl;
    }
    else { cout << "This number isn`t perfect" << endl;
    }
}