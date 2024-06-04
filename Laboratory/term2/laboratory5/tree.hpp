#ifndef TREE_HPP_
#define TREE_HPP_
#include <iostream>
struct data
{
    std::string word;
    std::string transl;
    int times;
};
struct node
{
    data *dat;
    node *right;
    node *left;
    node(const std::string &s, const std::string &t, int tm);
    ~node() { delete dat; }
};
class dict
{
private:
    node *root;
    void prnt(const node *n, int deep) const;
    node *deleteNode(node *n, const std::string &s);
    void rm_node(node *n);
    node *min(node *n);
    void find_max(node *root, data &b);

public:
    dict();
    dict(node *root);
    void add(const std::string &s, const std::string &t, int tm);
    void add(const data &n);
    void print() const;
    void del(const std::string &s);
    void del_node(const std::string &s);
    friend void create_tree(dict &a, dict &b);
    ~dict();
};
#endif
