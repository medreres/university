#include <iostream>
using namespace std;
struct node
{
    int key;
    node *left;
    node *right;
};
node *create_tree(int key)
{
    node *pnew = new node;
    pnew->key = key;
    pnew->right = pnew->left = nullptr;
    return pnew;
}
void add_node(node *root, int key)
{
    node *pnode = root, *pprev;
    node *p_new_node = new node;
    p_new_node->key = key;
    p_new_node->left = p_new_node->right = nullptr;
    while (pnode != nullptr)
    {
        pprev = pnode;
        if (key > pnode->key)
        {
            pnode = pnode->right;
        }
        else
        {
            pnode = pnode->left;
        }
    }
    if (key > pprev->key)
    {
        pprev->right = p_new_node;
    }
    else
    {
        pprev->left = p_new_node;
    }
}
void print(node *pnode, int h = 0)
{
    if (pnode)
    {
        print(pnode->right, h + 1);
        for (int i = 0; i < h; i++)
            cout << '\t';
        cout << pnode->key << '\n';
        print(pnode->left, h + 1);
    }
}
void swap_leaves(node *root)
{
    if (root)
    {
        if (root->left && root->right)
        {
            int k_left = root->left->key, k_right = root->right->key;
            root->left->key = k_right;
            root->right->key = k_left;
        }
        swap_leaves(root->left);
        swap_leaves(root->right);
    }
}
int main()
{
    node *tree;
    tree = create_tree(4);
    cout << '\n';
    add_node(tree, 2);
    add_node(tree, 6);
    add_node(tree, 7);
    add_node(tree, 5);
    add_node(tree, 1);
    add_node(tree, 3);
    add_node(tree, 10);
    add_node(tree, 13);
    add_node(tree, 12);
    add_node(tree, 14);
    print(tree);
    cout << "\n\n\n";
    swap_leaves(tree);
    print(tree);
}
