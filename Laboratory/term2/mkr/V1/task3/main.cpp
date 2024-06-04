#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
struct variable
{
    char var;
    double val;
    variable() {}
    variable(char var)
    {
        this->var = var;
    }
};
bool find(char ch, std::vector<variable> &var)
{
    for (size_t i = 0; i < var.size(); i++)
        if (ch == var[i].var)
            return true;
    return false;
}
int getPriority(const char &ch)
{
    switch (ch)
    {
    case '|':
        return 1;
    case '*':
    case '&':
        return 2;
    case '-':
    case '!':
        return 3;
    case '(':
        return 0;
    default:
        cerr << "Undefined symbol" << endl;
        return -1;
    }
}
stringstream getInfix(std::vector<variable> &var)
{

    double val;
    char variable;
    char ch;
    std::stringstream buffer;
    stack<char> opStck;
    cout << "Enter expression: ";
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
        if (tolower(ch) >= 'a' && tolower(ch) <= 'z')
        {
            if (!find(ch, var))
            {
                struct variable tmp;
                tmp.var = ch;
                var.push_back(tmp);
            }
            cin >> variable;
            buffer << variable << ' ';
            continue;
        }
        if (ch > 47 && ch < 58)
        {
            cin >> val;
            buffer << val;
            continue;
        }
        if (ch == '&' || ch == '*' || ch == '|' || ch == '-' || ch == '!')
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
    bool val;
    char op;
    Node *right;
    Node *left;
    Node(int data)
    {
        right = left = nullptr;
        val = data;
        op = 48;
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
    int val;
    stack<Node *> treeStck;
    // Node *root = nullptr;
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
            treeStck.push(new Node(char('0' + val)));
        }
        if (tolower(ch) >= 'a' && tolower(ch) <= 'z')
        {
            treeStck.push(new Node(ch));
            buff.ignore();
            continue;
        }
        if (ch == '*' || ch == '&' || ch == '|')
        {
            Node *left = treeStck.top();
            treeStck.pop();
            Node *right = treeStck.top();
            treeStck.pop();
            treeStck.push(new Node(ch, left, right));
            buff.ignore();
            continue;
        }
        if (ch == '-' || ch == '!')
        {
            Node *left = treeStck.top();
            treeStck.pop();
            treeStck.push(new Node(ch, left, nullptr));
            buff.ignore();
            continue;
        }
    }
    return treeStck.top();
}
int math(bool x, bool y, char op)
{
    switch (op)
    {
    case '*':
    case '&':
        return x && y;
    case '|':
    case '+':
        return x || y;
    case '-':
    case '!':
        return !x;
    }
    return 0;
}
void mathNodes(Node *root, vector<variable> &var)
{
    if (root->right && root->left)
    {
        mathNodes(root->right, var);
        mathNodes(root->left, var);
        root->val = math(root->right->val, root->left->val, root->op);
    }
    else if (root->left)
    {
        mathNodes(root->left, var);
        if (root->op == '-' || root->op == '!')
        {
            root->val = !(root->left->val);
        }
    }
}
double getResult(Node *root, vector<variable> &var)
{
    mathNodes(root, var);
    return root->val;
}
// for truth table
void initialize(vector<vector<int> > &matr, int n, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matr[i].push_back(0);
        }
    }
}
void print(vector<vector<int> > &matr, int n, std::vector<variable> &var)
{
    cout << "| ";
    for (int i = 0; i < var.size(); i++)
    {
        cout << var[i].var << " | ";
    }
    cout << "exp ";
    cout << endl;

    int quant = pow(2, n);
    for (int i = 0; i < quant; i++)
    {
        cout << "| ";
        int j = 0;
        for (j = 0; j < n; j++)
        {
            cout << matr[i][j] << " | ";
        }
        cout << matr[i][j] << " |";
        cout << endl;
    }
}
void fill(vector<vector<int> > &matr, int size, int j, int dx)
{
    if (dx)
    {
        for (int i = size - 1; i >= 0; i -= dx)
        {
            for (int k = 0; k < dx; k++)
            {
                matr[i--][j] = 1;
            }
        }
        fill(matr, size, j + 1, dx / 2);
    }
}
void sort_var(std::vector<variable> &var)
{
    variable tmp;
    for (int i = 0; i < var.size() - 1; i++)
    {
        for (int j = 0; j < var.size() - 1 - i; j++)
        {
            if (var[j].var > var[j + 1].var)
            {
                tmp = var[j].var;
                var[j].var = var[j + 1].var;
                var[j + 1] = tmp;
            }
        }
    }
}
/////

//------- traversal for subsituting variables with values
void subsitute(Node *root, std::vector<variable> &var)
{
    if (root)
    {
        subsitute(root->left, var);
        subsitute(root->right, var);
        if (tolower(root->op) >= 'a' && tolower(root->op) <= 'z')
            for (int i = 0; i < var.size(); i++)
            {
                if (var[i].var == root->op)
                {
                    root->val = var[i].val;
                    break;
                }
            }
        else if (root->op == '0' || root->op == '1')
        {
            root->val = root->op - 48;
        }
    }
}
//--------
int main()
{
    //-(y & x) | z * 0
    // (x | y) | (y & z)

    // char *str = "-(x * 1 & y) | z * 0";
    //--------------            getting expression
    std::vector<variable> var; // for counting variables
    stringstream buff = getInfix(var);
    Node *root = exprTree(buff);
    sort_var(var);
    //---------------

    //------------      truth table
    int n = var.size();
    int height = pow(2, n);
    vector<vector<int> > matr(height);
    initialize(matr, n, height);
    fill(matr, height, 0, height / 2);
    //------------

    //------------      printing root
    print(root);
    cout << "\n\n"
         << endl;
    double res = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < var.size(); j++)
        {
            var[j].val = matr[i][j];
        }
        subsitute(root, var);
        matr[i].push_back(getResult(root, var));
    }

    // res = getResult(root, var);
    print(matr, n, var);
    delTree(root);
}
