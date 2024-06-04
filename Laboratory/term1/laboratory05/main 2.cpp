#include <iostream>
#include <stack>
#include <cmath>
using namespace std;
long int fact(int n)
{
    if (n == 1 || n == 0)
    {
        return 1;
    }
    else
        return n * fact(n - 1);
}
struct leksema
{
    double value;
    char type; // 0 for num,'+' for adding etc.
};
bool math(stack<leksema> &stack_n, stack<leksema> &stack_o, leksema &item)
{
    const char ch = stack_o.top().type;
    stack_o.pop();
    double a = stack_n.top().value, b = 0;
    stack_n.pop();
    switch (ch)
    {
    case 'l':
        if (a < 0)
        {
            cerr << "taking ln of number < 0" << endl;
            return 0;
        }
        item.value = log(a);
        item.type = 0;
        stack_n.push(item);
        return 1;
    case 's':
        item.value = round(sin(a) * 1000000) / 1000000;
        item.type = '0';
        stack_n.push(item);
        ;
        return 1;
    case 'c':
        item.value = round(cos(a) * 1000000) / 1000000;
        item.type = 0;
        stack_n.push(item);
        return 1;
    case '!':
        item.value = fact(a);
        item.type = 0;
        stack_n.push(item);
        return 1;
    case '^':
        b = stack_n.top().value;
        stack_n.pop();
        item.value = pow(b, a);
        item.type = 0;
        stack_n.push(item);
        return 1;
    case '+':
        b = stack_n.top().value;
        stack_n.pop();
        item.value = a + b;
        item.type = 0;
        stack_n.push(item);
        return 1;
    case '-':
        b = stack_n.top().value;
        stack_n.pop();
        item.value = b - a;
        item.type = 0;
        stack_n.push(item);
        return 1;
    case '*':
        b = stack_n.top().value;
        stack_n.pop();
        item.value = b * a;
        item.type = 0;
        stack_n.push(item);
        return 1;
    case '/':
        b = stack_n.top().value;
        stack_n.pop();
        item.value = b / a;
        item.type = 0;
        stack_n.push(item);
        return 1;
    default:
        return 0;
    }
}
int getRange(const char &ch) // the priority of operation
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    if (ch == '*' || ch == '/')
    {
        return 2;
    }
    if (ch == '!' || ch == '^')
    {
        return 3;
    }
    if (ch == 's' || ch == 'c' || ch == 'l')
    {
        return 4;
    }
    else
    {
        return 0;
    }
}
bool choic()
{
    char choice;
    while (cin >> choice)
    {
        if (choice == 'y')
        {
            cin.ignore(100, '\n');
            return 1;
        }
        else if (choice == 'n')
        {
            cout << "Goodbye then!" << endl;
            return 0;
        }
        cout << "You should write 'y' or 'n' : ";
        cin.ignore(1000, '\n');
    }
}
int main()
{
    char ch, choice;
    double val;
    stack<leksema> stack_o;
    stack<leksema> stack_n;
    leksema item;
    bool f;

    cout << "Type sth" << endl;

    do
    {
        stack_o.empty();
        stack_n.empty();
        cin.clear();
        f = 1;

        while (1)
        {
            ch = cin.peek();
            if (ch == '\n') // if the end of sentence
            {
                break;
            }
            if (ch == ' ') // if space
            {
                cin.ignore();
                continue;
            }
            if (ch == 'e')
            {
                cout << "e";
                cin.ignore();
                item.value = M_E;
                item.type = 0;
                stack_n.push(item);
                continue;
            }
            if (ch == 'p') // for 3.14
            {
                char ch[2];
                for (int i = 0; i < 2; i++)
                {
                    ch[i] = cin.peek();
                    cin.ignore();
                }
                if (ch[0] == 'p' && ch[1] == 'i')
                {
                    item.value = M_PI;
                    item.type = 0;
                    stack_n.push(item);
                    cout << "pi";
                    continue;
                }
                else
                {
                    cerr << "unknown symbol " << ch;
                    return -1;
                }
            }
            if (ch >= 48 && ch <= 57 || (ch == '-' && f == 1)) // in case of number
            {
                cin >> val;
                cout << val;
                item.value = val;
                item.type = 0;
                stack_n.push(item);
                f = 0;
                continue;
            }
            if (ch == 's' || ch == 'c' || ch == 'l')
            {
                char fo[3];
                for (size_t i = 0; i < 3; i++)
                {
                    fo[i] = cin.peek();
                    cin.ignore();
                }
                if (fo[0] == 's' && fo[1] == 'i' && fo[2] == 'n')
                {
                    item.type = 's';
                    item.value = 0;
                    stack_o.push(item);
                    // cin.ignore();
                    f = 1;
                    continue;
                }
                else if (fo[0] == 'c' && fo[1] == 'o' && fo[2] == 's')
                {
                    item.type = fo[0];
                    item.value = 0;
                    stack_o.push(item);
                    // cin.ignore();
                    f = 1;
                    continue;
                }
                else if (fo[0] == 'l' && fo[1] == 'o' && fo[2] == 'g')
                {
                    item.type = fo[0];
                    item.value = 0;
                    stack_o.push(item);
                    // cin.ignore();
                    f = 1;
                    continue;
                }
                else
                {
                    cerr << "Unknown symbol : " << fo[0] << endl;
                    return -1;
                }
            }
            if (ch == '+' || (ch == '-' && f == 0) || ch == '*' || ch == '/' || ch == '^' || ch == '!') // in case of operation
            {
                if (stack_o.size() == 0)
                {
                    item.type = ch;
                    item.value = 0;
                    stack_o.push(item);
                    cin.ignore();
                    f = 1;
                    continue;
                }
                if (stack_o.size() != 0 && getRange(ch) <= getRange(stack_o.top().type))
                {
                    cout << stack_o.top().type;
                    if (math(stack_n, stack_o, item) != 1)
                    {
                        cerr << "Err" << endl;
                        return -1;
                    }
                    continue;
                }
                if (stack_o.size() != 0 && getRange(ch) > getRange(stack_o.top().type))
                {
                    // cout << stack_n.top().value;
                    item.type = ch;
                    item.value = 0;
                    stack_o.push(item);
                    cin.ignore();
                    continue;
                }
            }
            if (ch == '(')
            {
                item.type = ch;
                item.value = 0;
                stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (ch == ')')
            {
                cin.ignore();
                while (stack_o.top().type != '(')
                {
                    cout << stack_o.top().type;
                    if (math(stack_n, stack_o, item) == 1)
                    {
                        continue;
                    }
                }
                stack_o.pop();
                continue;
            }
        } 
        while (1)
        {
            if (stack_o.size() == 0)
            {
                break;
            }
            cout << stack_o.top().type;
            if (math(stack_n, stack_o, item) != 1)
            {
                cerr << "Err" << endl;
                return -1;
            }
        }
        cout << "\nresult = " << stack_n.top().value << endl;
        cout << "\nWanna try again? (y/n) :";
    } while (choic());

    // cout << "result = " << stack_n.top().value;
    return 0;
}
