#include <iostream>
#include <fstream>
#include "libr.hpp"
using namespace std;
int main()
{
    NodeList zh;
    NodeList dnf;
    fstream fout;
    char string[30];
    fout.open("bool.txt");
    if (fout.is_open())
    {
        fout.getline(string, 30);
    }
    else
    {
        cout << "File is not found!" << endl;
        return 0;
    }
    fout.close();
    get_polynom(string, zh);
    zh.print();
    get_dnf(zh, dnf);
    zh.print();
    dnf.print();

    zh.del();
}
 