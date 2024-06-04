#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include <iostream>
using namespace std;
const int LEN = 30;
struct User
{
    char name[LEN];
    char passw[LEN];
    double money;
    bool is_admin;
    int power_of_horse;
};
struct Race
{
    double coeff;
    unsigned horses;
    char name[LEN];
    bool is_deleted;
};
char *input(const char *, char *, const bool &i = 0);
unsigned &input(const char *, unsigned &);
double &input(const char *, double &);
struct NodeList
{
    struct Node
    {
        Race *data;
        Node *next;
        Node *prev;
    };
    Node *head = NULL;
    Node *tail = NULL;
    void print_all(const bool &is_delete = 0)
    {
        system("clear");
        if (!head)
        {
            cout << "There aren`t any races!" << endl;
            return;
        }
        int i = 1;
        Node *r = head;

        while (r)
        {
            if (is_delete && r->data->is_deleted)
            {
                cout << i++ << ". The race`s name : " << r->data->name;
                cout << "\n\tThe coefficient : " << r->data->coeff;
                cout << "\n\tThe quantity of horses : " << r->data->horses;
                cout << endl;
            }
            else if (!is_delete && !r->data->is_deleted)
            {
                cout << i++ << ". The race`s name : " << r->data->name;
                cout << "\n\tThe coefficient : " << r->data->coeff;
                cout << "\n\tThe quantity of horses : " << r->data->horses;
                cout << endl;
            }
            r = r->next;
        }
    }
    void del()
    {
        Node *pv;
        while (head)
        {
            pv = head;
            head = head->next;
            delete pv;
        }
    }
    void print(Node *pv)
    {
        cout << "\t1. The race`s name : " << pv->data->name;
        cout << "\n\t2. The coefficient : " << pv->data->coeff;
        cout << "\n\t3. The quantity of horses : " << pv->data->horses;
        cout << endl;
    }
    void add()
    {
        char choice = 'y';
        Race r;
        while (choice == 'y')
        {
            system("clear");
            // cout << "Enter the name of the race :";
            // cin.getline(r.name, LEN);
            input("name of the race", r.name, 1);
            input("coefficient", r.coeff);
            input("quantity of horses", r.horses);
            r.is_deleted = 0;
            Node *pv = new Node;
            pv->data = new Race;
            *(pv->data) = r;
            pv->next = NULL;
            if (!head)
            {
                pv->prev = NULL;
                head = pv;
                tail = head;
            }
            else
            {
                pv->prev = tail;
                tail->next = pv;
                tail = pv;
            }

            cout << "\nDo you want to add another race?(y/n) : ";
            (cin >> choice).get();
        }
    }
    void add(Race &r)
    {
        Node *pv = new Node;
        pv->data = new Race;
        *(pv->data) = r;
        pv->next = NULL;
        if (!head)
        {
            pv->prev = NULL;
            head = pv;
            tail = head;
        }
        else
        {
            pv->prev = tail;
            tail->next = pv;
            tail = pv;
        }
    }
    Node *find(const char *name)
    {
        Node *pv = head;
        while (pv)
        {
            if (strcmp(pv->data->name, name) == 0)
                break;
            pv = pv->next;
        }
        return pv;
    }
    void read()
    {
        FILE *f;
        if ((f = fopen("races.txt", "rb")))
        {
            Race pv;
            while (fread(&pv, sizeof(Race), 1, f))
            {
                // cout << pv.name << endl;
                add(pv);
            }
        }
        else
        {
            cout << "File \"races.txt\" is not found!" << endl;
        }
        fclose(f);
    }
    void save()
    {
        FILE *f = fopen("races.txt", "w+b");
        NodeList::Node *pv = head;
        while (pv)
        {
            fwrite(pv->data, sizeof(Race), 1, f);
            pv = pv->next;
        }
        fclose(f);
        cout << "All the data saved succesfully!" << endl;
    }
};
template <typename T>
void choose(T &choice, const int &range = 3);
User *sign_in(const char *nick, const char *passw);
bool interact_menu(User *pv);
bool sign_up();
#endif