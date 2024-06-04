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
int get_height(node *root, int height = 0)
{
    if (root == nullptr && height == 0)
    {
        return -1;
    }
    else if (root)
    {
        int l_height = get_height(root->left, height + 1);
        int r_height = get_height(root->right, height + 1);
        return (l_height > r_height) ? l_height : r_height;
    }
    else
    {
        return height - 1;
    }
}
node *get_min_value(node *node)
{
    if (node)
    {
        if (node->left)
        {
            return get_min_value(node->left);
        }
        else
        {
            return node;
        }
    }
    else
    {
        return nullptr;
    }
}
node *del_node(node *root, int key)
{
    if (root == nullptr)
        return nullptr;

    if (key > root->key)
    {
        root->right = del_node(root->right, key);
    }
    else if (key < root->key)
    {
        root->left = del_node(root->left, key);
    }
    else
    {
        if (root->right == nullptr)
        {
            node *pleft = root->left;
            delete root;
            return pleft;
        }
        else if (root->left == nullptr)
        {
            node *pright = root->right;
            delete root;
            return pright;
        }
        else if (root->right && root->left)
        {
            node *min_node = get_min_value(root->right);
            root->key = min_node->key;
            root->right = del_node(root->right, min_node->key);
        }
    }
    return root;
}
void del_nodes_in_average_height(node *tree, int height_of_tree, int curr_height = 0)
{
    if (tree)
    {
        if (curr_height < height_of_tree / 2)
        {
            del_nodes_in_average_height(tree->left, height_of_tree, curr_height + 1);
            del_nodes_in_average_height(tree->right, height_of_tree, curr_height + 1);
        }
        else if (curr_height == height_of_tree / 2)
        {
            int l_height = get_height(tree->left);
            int r_height = get_height(tree->right);
            if (l_height == r_height)
            {
                del_node(tree, tree->key);
            }
        }
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
    // add_node(tree, 10);
    // add_node(tree, 13);
    // add_node(tree, 12);
    // add_node(tree, 14);
    // print(tree);
    cout << "\n\n\n";
    print(tree);
    cout << "\n\n\n";
    int height = get_height(tree);
    cout << "Height of the tree: " << height << endl;
    // cout << "Minimum elemnt: " << min_value(tree)->key << endl;
    del_nodes_in_average_height(tree, height);

    cout << "\n\n\n";
    print(tree);
}
