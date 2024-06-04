/* 8)	У текстовому файлі зберігається послідовність довгих чисел,
 розділена знаками + та -. Вивести на екран результат виразу. */
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
int main()
{

    string path = "myFile.txt";
    string str;
    stack<char> operations;
    stack<long int> num;
    char ch;
    long int temp = 0, result = 0;
    bool is_first = 1;
    ifstream fs;
    fs.open(path, fstream::out); // 27
    if (!fs.is_open())
    {
        cout << "fail!" << endl;
        return 0;
    }
    else
    {
        cout << "success" << endl;
        while (!fs.eof())
        {
            ch = fs.peek();
            if (is_first)
            {
                fs >> result;
                num.push(temp);
                cout << result;
                is_first = 0;
                continue;
            }
            if (ch >= 48 && ch <= 57)
            {
                fs >> temp;
                num.push(temp);
                cout << temp;
                continue;
            }
            if (ch == '+')
            {
                cout << ch;
                operations.push(ch);
                fs.ignore();
                continue;
            }
        }
        /* cout << "ok" << endl; */
        while (operations.size() != 0)
        {
            long int a;
            a = num.top();
            // cout << a << endl;
            num.pop();
            ch = operations.top();
            operations.pop();
            // cout << ch;
            if (ch == '+')
            {
                result += a;
                continue;
            }
            if (ch == '-')
            {
                result -= a;
                continue;
            }
        }
    }
    cout << "\nresult = " << result;
    fs.close();
    cout << "\nclosing" << endl;
}