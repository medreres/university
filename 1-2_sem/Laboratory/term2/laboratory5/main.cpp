#include <iostream>
#include "tree.hpp"
using namespace std;
void create_tree(dict &a, dict &b)
{
    data tmp;
    do
    {
        tmp.times = 0;
        b.find_max(b.root, tmp);
        a.add(tmp);

    } while ((b.root = b.deleteNode(b.root, tmp.word)));
}
int main()
{
    dict dct, copy;
    data tmp;
    dct.add("B", "Слово 1", 2);
    dct.add("A", "Слово 2", 3);
    dct.add("D", "Слово 3", 7);
    dct.add("F", "Слово 4", 5);
    dct.add("C", "Слово 5", 3);
    dct.print();
    printf("\n\n\n");
    create_tree(copy, dct);
    copy.print();
    printf("\n\n\n");
    dct.print();
}
