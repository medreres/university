/* 4)	В тексті зустрічаються числа від 0 до 999, але записані англійськими словами. Замінити їх на числа.
 Наприклад «… one hundred seventeen …» замінити на …117… Записати результуючий текст у інший файл. */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
void print(std::ostream &fnew, string str)
{
    cout << str;
    fnew << str;
}
void num(int temp, std::ostream &fnew)
{
    if (temp == 1)
    {
        print(fnew, "one");
    }
    if (temp == 2)
    {
        print(fnew, " two");
    }
    if (temp == 3)
    {
        print(fnew, " three");
    }
    if (temp == 4)
    {
        print(fnew, " four");
    }
    if (temp == 5)
    {
        print(fnew, " five");
    }
    if (temp == 6)
    {
        print(fnew, " six");
    }
    if (temp == 7)
    {
        print(fnew, " seven");
    }
    if (temp == 8)
    {
        print(fnew, " eight");
    }
    if (temp == 9)
    {
        print(fnew, " nine");
    }
    if (temp == 10)
    {
        print(fnew, " ten");
    }
    if (temp == 11)
    {
        print(fnew, " eleven");
    }
    if (temp == 12)
    {
        print(fnew, " twelve");
    }
    if (temp == 13)
    {
        print(fnew, " thirteen");
    }
    if (temp == 18)
    {
        print(fnew, " eighteen");
    }
    if (temp > 13 && temp < 20 && temp != 15 && temp != 18)
    {
        num(temp % 10, fnew);
        print(fnew, "teen");
    }
    if (temp == 15)
    {
        print(fnew, " fifteen");
    }
    if (temp >= 40 && temp <= 90)
    {
        num(temp / 10, fnew);
        print(fnew, "ty ");
    }
    if (temp == 20)
    {
        print(fnew, " twenty");
    }
    if (temp == 30)
    {
        print(fnew, " thirty");
    }
    if (temp >= 100 && temp < 1000)
    {
        num(floor(temp / 100), fnew);
        print(fnew, " hundred");
    }
}
void eng(int length, int temp, std::ostream &fnew)
{
    if (temp > 10 && temp < 20)
    {
        num(temp, fnew);
        return;
    }
    if (length == 1)
    {
        num(temp, fnew);
    }
    if (length == 2)
    {

        num(round(temp / 10) * 10, fnew);
        length--;
        eng(length, temp % 10, fnew);
    }
    if (length == 3)
    {
        num(temp, fnew);
        length--;
        eng(length, temp % 100, fnew);
    }
}
int main()
{
    char ch;
    ifstream fout;
    ofstream fnew;
    string path = "task04.txt";
    string path1 = "task04_1.txt";
    int length = 0, temp = 0;
    fout.open(path);
    fnew.open(path1);
    if (fout.is_open())
    {
        cout << "Succeed" << endl;
        while (!fout.eof())
        {

            ch = fout.peek();
            if (ch == '\n')
            {
                fout.ignore();
                continue;
            }
            if (ch == ' ')
            {
                fout.ignore();
                continue;
            }
            if (ch >= 48 && ch <= 57)
            {
                length = 0;
                int temp1;
                fout >> temp;
                temp1 = temp;
                do
                {
                    length++;
                    temp1 /= 10;
                } while (temp1);
                cout << temp << endl;
                eng(length, temp, fnew);
                cout << "\n";
                fnew << "\n";
            }
        }
        fout.close();
    }
    else
    {
        cout << "fail" << endl;
        return 0;
    }
}