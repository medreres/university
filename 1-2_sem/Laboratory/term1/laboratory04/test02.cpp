//Дано два рядки. Знайти максимальний спільний підрядок для цих рядків.
//Приклад: для рядків «аббга» та «ббгпр» відповідь буде «ббг»
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int main()
{
    char a[] = "abpbbgaa";
    char b[] = "asdonbbgaprabpbbga";
    string c;
    int size(0), index(0);
    cout << a << "\n"
         << b << endl;

    for (int i = 0; i < sizeof(a); i++)
    {
        for (int j = 0; j < sizeof(b); j++)
        {
            if (a[i] == b[j])
            {
                int dx = i - j;
                int size_temp(0);
                for (int k = i; a[k] == b[k - dx]; k++)
                {
                    size_temp++;
                }
                if (size_temp >= size)
                {
                    size = size_temp;
                    index = i;
                }
            }
        }
    }
    cout << "index = " << index << " size = " << size << endl;
    for (int i = index; i < size + index; i++)
    {
        cout << a[i];
    }
    cout << c << endl;
}