#include <iostream>
#include <stack>
#include <cmath>
using namespace std;
double Sin(double x)
{
    return round(sin(x) * 1000000) / 1000000;
}
double Cos(double x)
{
    return round(cos(x) * 1000000) / 1000000;
}
int fact(int n)
{
    if (n == 1 || n == 0)
        return 1;
    else
        return n * fact(n - 1);
}
struct leksema
{
    char type; // 0 for numbers,'+' for adding etc.
    double value;
};
bool math(stack<leksema> &Stack_n, stack<leksema> &Stack_o, leksema &item)
{

    double a, b, c;
    a = Stack_n.top().value;
    Stack_n.pop();
    switch (Stack_o.top().type)
    {
    case '+':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a + b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '-':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '*':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '/':
        b = Stack_n.top().value;
        Stack_n.pop();
        if (a == 0)
        {
            cout << "dividing by zero!";
            return 0;
            break;
        }
        else
        {
            c = b / a;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        }
    case '^':
        b = Stack_n.top().value;
        Stack_n.pop();
        if (a == 0 && b == 0)
        {
            cerr << "Err! 0^0";
            return 0;
            break;
        }
        c = pow(b, a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '!':
        // b = Stack_n.top().value;
        // Stack_n.pop();
        c = fact(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case 's':
        c = Sin(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case 'c':
        c = Cos(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case 't':
        c = tan(a * M_PI / 180);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;

    default:
        cerr << "Unknown operation";
        return 0;
        break;
    }

    return 1;
}
int getRang(char &ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else if (ch == '*' || ch == '/')
    {
        return 2;
    }
    else if (ch == '^' || ch == '!')
    {
        return 3;
    }
    if (ch == 's' || ch == 'c' || ch == 't')
    {
        return 4;
    }
    return 0;
}
bool choi()
{
    char choice;
    while (cin >> choice)
    {
        if (choice != 'y' && choice != 'n')
        {
            cout << "You should write (y/n): ";
            cin.ignore(1000, '\n');
            cin.bad();
            continue;
        }
        break;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    if (choice == 'y')
    {
        return 1;
    }
    else if (choice == 'n')
    {
        return 0;
    }
}
int main()
{
    cout << "Number 'Pi' is written - pi\n";
    cout << "Number 'e' is written - e\n";
    cout << "To take cos(x) you should write cos()\n";
    int quantity = 0;
    double value;
    char ch;
    bool flag = 1;
    stack<leksema> Stack_o;
    stack<leksema> Stack_n;
    leksema item;

    do
    {
        while (1)
        {
            ch = cin.peek();
            if (ch == '\n')
            {
                break;
            }
            if (ch == ' ')
            {
                cin.ignore();
                continue;
            }
            if (ch == 's' || ch == 'c' || ch == 't')
            {
                char foo[3];
                for (size_t i = 0; i < 3; i++)
                {
                    ch = cin.peek();
                    foo[i] = ch;
                    cin.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n')
                {
                    item.type = 's';
                    item.value = 0;
                    Stack_o.push(item);
                    // cin.ignore();
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's')
                {
                    item.type = 'c';
                    item.value = 0;
                    Stack_o.push(item);
                    // cin.ignore();
                    continue;
                }
                if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n')
                {
                    item.type = 'c';
                    item.value = 0;
                    Stack_o.push(item);
                    // cin.ignore();
                    continue;
                }
            }
            if (ch == 'p')
            {
                cin.ignore();
                cin.ignore();
                item.type = '0';
                item.value = M_PI;
                Stack_n.push(item);
                flag = 0;
                continue;
            }
            if (ch == 'e')
            {
                cin.ignore();
                item.type = '0';
                item.value = M_E;
                Stack_n.push(item);
                flag = 0;
                continue;
            }
            if ((ch >= 48 && ch <= 57) || (ch == '-' && flag == 1)) // if number
            {
                cin >> value;
                item.type = '0';
                item.value = value;
                Stack_n.push(item);
                flag = 0;
                continue;
            }
            if (ch == '+' || (ch == '-' && flag == 0) || ch == '*' || ch == '/' || ch == '^' || ch == '!') // in case of symbol
            {
                if (Stack_o.size() == 0)
                {

                    item.type = ch;
                    item.value = 0;
                    Stack_o.push(item);
                    cin.ignore();
                    flag = 1;
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(ch) > getRang(Stack_o.top().type))
                {
                    item.type = ch;
                    item.value = 0;
                    Stack_o.push(item);
                    cin.ignore();
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(ch) <= getRang(Stack_o.top().type))
                {
                    // item.type = ch;
                    if (math(Stack_n, Stack_o, item) == 0)
                    {
                        return 0;
                    }
                    continue;
                }
            }
            if (ch == '(')
            {
                // quantity++;
                item.type = ch;
                item.value = 0;
                Stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (ch == ')')
            {
                cin.ignore();
                while (Stack_o.top().type != '(')
                {
                    if (math(Stack_n, Stack_o, item) == 0)
                    {
                        return 0;
                    }
                }
                Stack_o.pop();
                continue;
            }
            else
            {
                cout << "Unknown symbol.";
                return 0;
            }
        }
        while (Stack_o.size() != 0)
        {
            if (math(Stack_n, Stack_o, item) == 0)
            {
                return 0;
            }
        }
        cout << "result = " << Stack_n.top().value;
        cout << "\nWould you like to repeat? (y/n) : ";
    } while (choi());
    cout << "goodbye then!" << endl;
    return 0;
}