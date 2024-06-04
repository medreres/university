#include "libr.hpp"
#include <iostream>
using namespace std;
void NodeList::add(const char *ch)
{
    Node *tmp = new Node;
    strcpy(tmp->symbol, ch);
    tmp->next = NULL;
    if (!head)
    {
        tmp->prev = NULL;
        head = tmp;
        tail = head;
    }
    else
    {
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }
}
void NodeList::print()
{
    Node *pv = head;
    while (pv)
    {
        cout << pv->symbol;
        if (pv->next)
            cout << "+";
        else
            cout << endl;
        pv = pv->next;
    }
    cout << endl;
}
NodeList::Node *NodeList::find(const char *ch)
{
    Node *pv = head;
    while (pv)
    {
        if (strcmp(pv->symbol, ch) == 0)
            return pv;
        pv = pv->next;
    }
    return NULL;
}
void NodeList::del()
{
    Node *pv;
    while (head)
    {
        pv = head;
        head = head->next;
        delete pv;
    }
}
bool NodeList::remove(char *ch)
{
    NodeList::Node *pv = find(ch);
    if (pv)
    {
        if (!pv->next && pv->prev)
        {
            tail = tail->prev;
            pv->prev->next = NULL;
            delete pv;
            return 1;
        }
        else if (!pv->prev && pv->next)
        {
            head = head->next;
            pv->next->prev = NULL;
            delete pv;
            return 1;
        }
        else if (!pv->prev && !pv->next)
        {
            head = tail = NULL;
            delete pv;
            return 1;
        }
        else
        {
            pv->prev->next = pv->next;
            pv->next->prev = pv->prev;
            delete pv;
            return 1;
        }
    }
    return 0;
}
bool NodeList::remove(NodeList::Node *pv)
{
    return remove(pv->symbol);
}
int NodeList::get_number()
{
    int i = 0;
    Node *pv = head;
    while (pv)
    {
        i++;
        pv = pv->next;
    }
    return i;
}
void get_polynom(char *ch, NodeList &zh)
{
    int len = strlen(ch);
    int beg = 0, end = 0;
    char *str;
    for (int i = 0; i < len; i++)
    {
        if (isdigit(ch[i]))
        {
            str = new char[4];
            str[0] = '1';
            str[1] = '\0';
            zh.add(str);
            // cout << str << endl;
            delete[] str;
            continue;
        }
        if (isalpha(ch[i]))
        {
            str = new char[4];
            beg = i;
            end = beg;
            for (int j = beg; j < len; j++)
            {

                if (isalpha(ch[j]))
                    end++;
                else
                    break;
            }
            for (int j = beg, ind = 0; j < end; j++, ind++) // copying string
            {
                str[ind] = ch[j];
            }
            // cout << str << endl;
            zh.add(str);
            delete[] str;
            i = end - 1;
        }
    }
}
void get_dnf(NodeList &zh, NodeList &dnf)
{
    const char x[] = "X", y[] = "Y", z[] = "Z", cnst[] = "1";
    const char *symb[] = {x, y, z, cnst};
    for (int i = 0; i < 5; i++)
    {
        // geting  denying
        get_den(zh, dnf, symb);
        // geting shepher
        get_shep(zh, dnf, symb);
        // getting disjunct
        get_disjunct(zh, dnf, symb);
        // geting implication
        get_equiv(zh, dnf, symb);
        // getting equivalence
    }
}
void get_den(NodeList &zh, NodeList &dnf, const char **symb)
{
    for (int i = 0; i < 3; i++)
    {
        if (zh.find(symb[i]) && zh.find("1"))
        {
            // cout << zh.find(*(symb + i))->symbol << '+' << zh.find("1")->symbol << endl;
            char str[4] = {"!"};
            strncat(str, symb[i], 4);
            dnf.add(str);
            // dnf.add("v");
            zh.remove(zh.find(*(symb + i)));
            zh.remove(zh.find("1"));
        }
    }
}
void get_shep(NodeList &zh, NodeList &dnf, const char **symb)
{
    char *str;
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            str = new char[3];
            strncat(str, symb[i], 3);
            strncat(str, symb[j], 3);
            // cout << *symb[i] << " + " << *symb[j] << " + " << str << endl;
            if (zh.find(symb[3]) && zh.find(str))
            {

                char tmp[4] = {};
                strncat(tmp, symb[i], 1);
                strncat(tmp, "|", 1);
                strncat(tmp, symb[j], 1);
                // cout << tmp << "   asdasd" << endl;
                dnf.add(tmp);
                zh.remove(zh.find(str));
                zh.remove(zh.find(symb[3]));
                break;
            }
            delete[] str;
        }
    }
}
void get_disjunct(NodeList &zh, NodeList &dnf, const char **symb)
{
    char *str;
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            str = new char[3];
            strncat(str, symb[i], 3);
            strncat(str, symb[j], 3);
            // cout << *symb[i] << " + " << *symb[j] << " + " << str << endl;
            if (zh.find(symb[i]) && zh.find(symb[j]) && zh.find(str))
            {
                char tmp[3] = {};
                // cout << *symb[i] << " + " << *symb[j] << " + " << str << endl;
                strncat(tmp, symb[i], 1);
                strncat(tmp, "v", 1);
                strncat(tmp, symb[j], 1);
                // cout << tmp ;
                dnf.add(tmp);
                // dnf.add(symb[i]);
                //  dnf.add("v");
                // dnf.add(symb[j]);

                zh.remove(zh.find(symb[i]));
                zh.remove(zh.find(symb[j]));
                zh.remove(zh.find(str));
                break;
            }
            delete[] str;
        }
    }
}
void get_impl(NodeList &zh, NodeList &dnf, const char **symb)
{
    char *str;
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            str = new char[3];
            strncat(str, symb[i], 3);
            strncat(str, symb[j], 3);
            // cout << *symb[i] << " + " << *symb[j] << " + " << str << endl;
            if (zh.find(symb[4]) && zh.find(str) && zh.find(symb[i]))
            {

                char tmp[4] = {};
                strncat(tmp, symb[i], 1);
                strncat(tmp, "->", 2);
                strncat(tmp, symb[j], 1);
                // cout << tmp << "   asdasd" << endl;
                dnf.add(tmp);
                zh.remove(zh.find(str));
                zh.remove(zh.find(symb[3]));
                zh.remove(zh.find(symb[i]));

                break;
            }
            delete[] str;
        }
    }
}
void get_equiv(NodeList &zh, NodeList &dnf, const char **symb)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (zh.find(symb[i]) && zh.find(symb[3]) && zh.find(symb[j]))
            {
                const int j1 = j;
                const int i1 = i;
                // cout << zh.find(symb[i])->symbol << '+' << zh.find("1")->symbol << " + " << zh.find(symb[j])->symbol << endl;
                char str[4] = {};
                strncat(str, *(symb + i1), 1);
                strncat(str, "≡", 4);
                strncat(str, symb[j1], 1);
                // cout << str << endl;

                dnf.add(str);
                // dnf.add("v");
                zh.remove(zh.find(*(symb + i)));
                zh.remove(zh.find("1"));
                // zh.find(*(symb+j));
                break;
            }
        }
    }
}
