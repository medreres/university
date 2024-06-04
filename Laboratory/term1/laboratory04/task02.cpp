//Дано два рядки. Знайти максимальний спільний підрядок для цих рядків.
//Приклад: для рядків «аббга» та «ббгпр» відповідь буде «ббг»
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string a, b, c;
    cin >> a >> b;
    int size(0), index(0);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
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
        c+=a[i];
    }
    cout << c <<  endl;
    cin.get();
}