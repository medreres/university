#ifndef LIBR_H
#define LIBR_H
struct NodeList
{
    public:
    struct Node
    {
        char symbol[4];
        Node *next;
        Node *prev;
    };
    Node *head;
    Node *tail ;
    Node *find(const char *ch);
    void add(const char *);
    void print();
    void del();
    int get_number();
    bool remove(char *);
    bool remove(NodeList::Node *);
};
void get_polynom(char *, NodeList &);
void get_dnf(NodeList &, NodeList &);
void get_den(NodeList &, NodeList &, const char **);
void get_shep(NodeList &, NodeList &, const char **);
void get_disjunct(NodeList &, NodeList &, const char **);
void get_impl(NodeList &, NodeList &, const char **);
void get_equiv(NodeList &, NodeList &, const char **);
#endif
