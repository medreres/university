#include "tree.hpp"
node::node(const std::string &s, const std::string &t, int tm)
{
    right = left = nullptr;
    dat = new data;
    dat->word = s;
    dat->transl = t;
    dat->times = tm;
}
dict::dict() : root(nullptr)
{
}
dict::dict(node *root) : root(root) {}
void dict::add(const std::string &s, const std::string &t, int tm)
{
    if (root == nullptr)
    {
        root = new node(s, t, tm);
    }
    else
    {
        node *pv = root, *prev;
        int isright;
        while (pv)
        {
            isright = s > pv->dat->word;
            prev = pv;
            if (isright)
            {
                pv = pv->right;
            }
            else
            {
                pv = pv->left;
            }
        }
        if (isright)
        {
            prev->right = new node(s, t, tm);
        }
        else
        {
            prev->left = new node(s, t, tm);
        }
    }
}
void dict::add(const data &n)
{
    this->add(n.word, n.transl, n.times);
}
void dict::prnt(const node *n, int deep) const
{
    if (n)
    {
        prnt(n->right, deep + 1);
        for (int i = 0; i < deep; i++)
            std::cout << '\t';
        std::cout << n->dat->word << ' ' << n->dat->transl << ' '
                  << n->dat->times << std::endl;

        prnt(n->left, deep + 1);
    }
}
void dict::print() const
{
    prnt(root, 0);
}
void dict::find_max(node *root, data &b)
{
    if (root)
    {
        find_max(root->right, b);
        find_max(root->left, b);
        if (root->dat->times > b.times)
        {
            b = *root->dat;
        }
    }
}
void dict::rm_node(node *n)
{
    if (n)
    {
        rm_node(n->right);
        rm_node(n->left);
        n->~node();
    }
}
dict::~dict()
{
    rm_node(root);
}
void dict::del_node(const std::string &s)
{
    node *pv = root, *prev;
    int isright = -1; //-1 means the root;
    while (pv)
    {
        prev = pv;
        if (s > pv->dat->word)
        {
            isright = 1;
            pv = pv->right;
        }
        else if (s < pv->dat->word)
        {
            isright = 0;
            pv = pv->left;
        }
        else
            break;
    }
    node *righest = root, *prevr;
    bool isrright = 0;
    while (true)
    {
        prevr = righest;
        if (righest->right)
        {
            righest = righest->right;
            isrright = 1;
        }
        else
        {
            righest = righest->left;
            isright = 0;
        }
    }
    if (isrright)
        prevr->right = nullptr;
    else
        prev->left = nullptr;
    righest->right = pv->right;
    righest->left = pv->left;
    if (isright == 1)
    {
        prev->right = righest;
    }
    else if (isright == 0)
    {
        prev->left = 0;
    }
    else
    {
        root = righest;
    }
    delete pv;
}
node *dict::min(node *n)
{
    while (n && n->left)
    {
        n = n->left;
    }
    return n;
}
node *dict::deleteNode(node *n, const std::string &s)
{
    if (s > n->dat->word)
        n->right = deleteNode(n->right, s);
    else if (s < n->dat->word)
        n->left = deleteNode(n->left, s);
    else
    {
        if (n->left == nullptr && n->right == nullptr)
        {
            delete n;
            return nullptr;
        }
        else if (n->left == nullptr)
        {
            node *tmp = n->right;
            delete n;
            return tmp;
        }
        else if (n->right == nullptr)
        {
            node *tmp = n->left;
            delete n;
            return tmp;
        }

        node *tmp = min(n->right);
        *n->dat = *tmp->dat;
        n->right = deleteNode(n->right, tmp->dat->word);
    }
    return n;
}
void dict::del(const std::string &s)
{
    deleteNode(root, s);
}
