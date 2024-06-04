#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;
int getPriority(const char &ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
        return 0;
    default:
        cerr << "Undefined symbol" << endl;
        return -1;
    }
}
stringstream getInfix()
{

    double val;
    char ch;
    std::stringstream buffer;
    stack<char> opStck;
    while (true)
    {
        ch = cin.peek();
        if (ch == '\n')
            break;
        if (ch == ' ')
        {
            cin.ignore();
            continue;
        }
        if (ch > 47 && ch < 58)
        {
            cin >> val;
            buffer << val << ' ';
            continue;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (opStck.size() == 0)
            {
                cin.ignore();
                opStck.push(ch);
            }
            else if (opStck.size() != 0 && getPriority(ch) > getPriority(opStck.top()))
            {
                cin.ignore();
                opStck.push(ch);
            }
            else if (opStck.size() != 0 && getPriority(ch) <= getPriority(opStck.top()))
            {
                while (opStck.size() != 0 && getPriority(ch) <= getPriority(opStck.top()))
                {
                    char oper = opStck.top();
                    if (oper != '(' && oper != ')')
                        buffer << oper << ' ';
                    opStck.pop();
                }
                cin.ignore();
                opStck.push(ch);
            }
        }
        if (ch == '(' || ch == ')')
        {
            if (ch == '(')
            {
                cin.ignore();
                opStck.push(ch);
            }
            else if (ch == ')')
            {
                char op;
                while (opStck.size() != 0 && opStck.top() != '(')
                {
                    op = opStck.top();
                    if (op != '(' && op != ')')
                        buffer << op << ' ';
                    opStck.pop();
                }
                opStck.pop();
                cin.ignore();
            }
        }
    }
    while (opStck.size() != 0)
    {
        ch = opStck.top();
        if (ch != '(' && ch != ')')
            buffer << ch << ' ';
        opStck.pop();
    }
    return buffer;
}
struct Node
{
    double val;
    char op;
    Node *right;
    Node *left;
    Node(double data)
    {
        right = left = nullptr;
        val = data;
        op = 0;
    }
    Node(char data)
    {
        right = left = nullptr;
        val = 0;
        op = data;
    }
    Node(char data, Node *l, Node *r)
    {
        op = data;
        val = 0;
        this->left = l;
        this->right = r;
    }
};
void print(Node *root, int level = 0)
{
    if (root)
    {
        print(root->right, level + 1);
        for (int i = 0; i < level; i++)
            cout << '\t';
        if (root->op != 0)
            cout << root->op << endl;
        else
            cout << root->val << endl;
        print(root->left, level + 1);
    }
}
void delTree(Node *root, int level = 0)
{
    if (root)
    {
        delTree(root->right, level + 1);
        delTree(root->left, level + 1);
        delete root;
    }
}
Node *exprTree(stringstream &buff)
{
    // cout << "The result is \n";
    cout << "Postfix notation: " << buff.str() << endl;
    char ch;
    double val;
    stack<Node *> treeStck;
    Node *root = nullptr;
    while (!buff.eof())
    {
        ch = buff.peek();
        if (ch == ' ')
        {
            buff.ignore();
            continue;
        }
        if (ch > 47 && ch < 58)
        {
            buff >> val;
            treeStck.push(new Node(val));
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            Node *left = treeStck.top();
            treeStck.pop();
            Node *right = treeStck.top();
            treeStck.pop();
            treeStck.push(new Node(ch, left, right));
            buff.ignore();
            continue;
        }
    }
    // root = treeStck.top();
    // cout << "\nPrintning tree\n";
    return treeStck.top();
}
double math(double x, double y, char op)
{
    switch (op)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    }
}
void mathNodes(Node *root)
{
    if (root->right && root->left)
    {
        mathNodes(root->right);
        mathNodes(root->left);
        root->val = math(root->right->val, root->left->val, root->op);
    }
}
double getResult(Node *root)
{
    mathNodes(root);
    return root->val;
}
int main()
{
    stringstream buff = getInfix();
    Node *root = exprTree(buff);
    print(root);
    cout << endl
         << endl;
    double res = 0;
    res = getResult(root);
    cout << "\n\nResult : " << res << endl;
    delTree(root);
}