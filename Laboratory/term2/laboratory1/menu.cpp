#include <iostream>
#include "menu.hpp"
using namespace std;
enum MENU_RACE {ADD_RACE = 1,DELETE_RACE};
char *input(const char *ch, char *inp, const bool &i)
{
    cout << "Enter your " << ch << " : ";
    bool is_good = 1;
    while (true)
    {
        is_good = 1;
        cin.getline(inp, LEN);
        if (inp[0] == ' ')
        {
            cout << '\n'
                 << ch << " must not containt any spaces! : ";
            continue;
        }
        int len = strlen(inp);
        for (int i = 0; i < len; i++)
        {
            if (i && isprint(inp[i]))
                continue;
            if (!isgraph(inp[i]))
            {
                is_good = 0;
                cout << ch << " must containt only letters and numbers! : ";
                break;
            }
        }
        if (is_good)
            break;
    }
    return inp;
}
unsigned &input(const char *ch, unsigned &inp)
{
    cout << "Enter " << ch << " : ";
    while (true)
    {
        cin >> inp;
        if (inp > 0)
        {
            cin.get();
            break;
        }
        cin.clear();
        cin.ignore(100, '\n');

        cout << "You have to enter a number ( > 0) :";
        continue;
    }
    return inp;
}
double &input(const char *ch, double &inp)
{
    cout << "Enter " << ch << " : ";
    while (true)
    {
        cin >> inp;
        if (inp > 0)
        {
            cin.get();
            break;
        }
        cin.clear();
        cin.ignore(100, '\n');

        cout << "You have to enter a number ( > 0) :";
        continue;
    }
    return inp;
}
template <typename T>
void choose(T &choice, const int &range)
{
    while (true)
    {
        cin >> choice;
        if (choice > 0 && choice < range + 1)
        {
            cin.get();
            return;
        }
        cin.clear();
        cin.ignore(100, '\n');
        cout << "You have to type a number ( from 1 to " << range << ") : ";
        continue;
    }
}
User *sign_in(const char *nick, const char *passw)
{
    User *ptv = new User;
    FILE *f;
    bool is_authorized = 0;
    if ((f = fopen("data.txt", "rb")))
    {
        while (fread(ptv, sizeof(User), 1, f))
        {
            if (strcmp(ptv->name, nick) == 0 && strcmp(ptv->passw, passw) == 0)
            {
                is_authorized = 1;
                break;
            }
        }
    }
    else
    {
        cout << "Error opening data-file!" << endl;
    }
    fclose(f);
    if (!is_authorized)
    {
        delete ptv;
        return NULL;
    }
    return ptv;
}
bool sign_up()
{
    FILE *f;                            // ofstream fout("data.txt", ofstream::app);
    if ((f = fopen("data.txt", "a+b"))) // fout.is_open()
    {
        User usr;
        input("nick", usr.name);
        input("password", usr.passw);
        input("money", usr.money);
        cout << "Enter power of horse (from 1 to 100) : ";
        choose(usr.power_of_horse, 100);
        /* cout << "Are ou admin : ";
        choose(usr.is_admin); */
        usr.is_admin = 0;
        fseek(f, 0, SEEK_END);
        fwrite((char *)&usr, 1, sizeof(User), f); // fout.write((char *)&usr, sizeof(User));
        cout << "Succesfully registered!" << endl;
        cin.get();
        fclose(f); // fout.close();
        return 1;
    }
    else
    {
        cout << "Error! File \"data.txt\" is not found!" << endl;
        fclose(f); // fout.close();
        cin.get();
        return 0;
    }
}
bool interact_menu(User *pv)
{
    NodeList races;
    races.read();
    while (true)
    {
        system("clear");
        int choice;
        if (pv->is_admin == 1)
        {
            cout << "1. Create race\n";
            cout << "2. Change race\n";
            cout << "3. Delete race\n";
            cout << "4. Restore race\n";
            cout << "5. Show races\n";
            cout << "6. Sign out\n";
            cout << "7. Quit\n";
        }
        else
        {
            cout << "1. Lay a bet\n";
            cout << "2. Check the balance\n";
            cout << "3. Sign out\n";
            cout << "4. Quit\n";
        }
        cout << "What would you like to do? : ";
        if (pv->is_admin)
            choose(choice, 7);
        else
            choose(choice, 4);
        switch (choice)
        {
        case MENU_RACE::ADD_RACE:
            if (pv->is_admin)
                races.add();
            else
            {
                races.print_all();
                cout << "Enter  which race you want to bet on :";
                char name[LEN];
                cin.getline(name, LEN);
                NodeList::Node *pr = races.find(name);
                if (!pr)
                {
                    cout << "Race was not found!" << endl;
                    cin.get();
                    break;
                }
                cout << "Enter what sum do you want to bet : ";
                double sum;
                choose(sum, pv->money);
                pv->money -= sum;
                bool arr[100] = {};
                srand(time(NULL));
                for (int i = 0; i < pv->power_of_horse; i++)
                {
                    int x = rand() % (101);
                    if (!arr[i])
                        arr[i] = 1;
                }

                int x = rand() % (101);
                if (arr[x])
                {
                    sum *= pr->data->coeff;
                    cout << "You won : $" << sum << endl;
                    pv->money += sum;
                }
                else
                {
                    cout << "You loose!" << endl;
                }
                FILE *f;
                if ((f = fopen("data.txt", "r+b")))
                {
                    User tmp;
                    while (fread((char *)&tmp, sizeof(User), 1, f))
                    {
                        if (strcmp(pv->name, tmp.name) == 0)
                        {
                            fseek(f, -sizeof(User), SEEK_CUR);
                            fwrite((char *)pv, sizeof(User), 1, f);
                            break;
                        }
                    }
                    fclose(f);
                    delete pv;
                    pv = new User(tmp);
                    cin.get();
                }
                else
                {
                    cout << "Error opening \"data.txt\"" << endl;
                    cin.get();
                    break;
                }
            }
            break;
        case 2:
            if (pv->is_admin)
            {
                races.print_all();
                cout << "Enter the name of the race to be changed : ";
                char name[LEN];
                cin.getline(name, LEN);
                NodeList::Node *pv = races.find(name);
                if (!pv)
                {
                    cout << "Race is not found!" << endl;
                    break;
                }
                system("clear");
                races.print(pv);
                cout << "What would you like to change? : ";
                int choice;
                choose(choice);
                switch (choice)
                {
                case 1:
                    cout << "Enter new name : ";
                    cin.getline(pv->data->name, LEN);
                    break;
                case 2:
                    cout << "Enter new coefficient : ";
                    choose(pv->data->coeff, 5);
                    break;
                case 3:
                    cout << "Enter new quantity of horses : ";
                    choose(pv->data->horses, 7);
                    break;
                }
                cout << "Changed succesfully!" << endl;
                cin.get();
                system("clear");
            }
            else
            {
                char name[LEN], passw[LEN];
                strcpy(name, pv->name);
                strcpy(passw, pv->passw);
                delete pv;
                pv = sign_in(name, passw);
                cout << "Your balance is : " << pv->money << endl;
                cout << "Your horse power is : " << pv->power_of_horse << endl;
                cin.get();
                continue;
            }
            break;
        case 3:
            if (pv->is_admin)
            {
                races.print_all();
                cout << "Enter the name of the race to be deleted : ";
                char name[LEN];
                cin.getline(name, LEN);
                Race r;
                NodeList::Node *pv = races.find(name);
                if (!pv)
                {
                    cout << "Race was not found!" << endl;
                    cin.get();
                    break;
                }
                if (!pv)
                {
                    cout << "The race is not found!" << endl;
                    break;
                }
                cout << "To delete enter 'y', to leave 'n' : ";
                char choice;
                bool deleted;
                while (true)
                {
                    cin >> choice;
                    if (choice == 'y')
                    {
                        deleted = 1;
                        break;
                    }
                    else if (choice == 'n')
                    {
                        deleted = 0;
                        break;
                    }
                    cin.ignore(100, '\n');
                    cin.clear();
                    continue;
                }
                if (deleted)
                    pv->data->is_deleted = 1;
                else
                    pv->data->is_deleted = 0;

                cin.get();
            }
            else
            {
                races.save();
                cin.get();
                delete pv;
                return 1;
            }
            break;
        case 4:
            if (pv->is_admin)
            {
                races.print_all(1);
                cout << "Enter the name of the race to be restored : ";
                char name[LEN];
                cin.getline(name, LEN);
                Race r;
                NodeList::Node *pv = races.find(name);
                if (!pv)
                {
                    cout << "The race is not found!" << endl;
                    cin.get();
                    break;
                }
                cout << "To restore enter 'y', to leave 'n' : ";
                char choice;
                bool deleted;
                while (true)
                {
                    cin >> choice;
                    if (choice == 'y')
                    {
                        deleted = 0;
                        break;
                    }
                    else if (choice == 'n')
                    {
                        deleted = 1;
                        break;
                    }
                    cin.ignore(100, '\n');
                    cin.clear();
                    continue;
                }
                if (deleted)
                    pv->data->is_deleted = 1;
                else
                    pv->data->is_deleted = 0;
                cin.get();
            }
            else
            {
                races.save();
                cout << "Goodbye!" << endl;
                delete pv;
                return 0;
            }
            break;
        case 5:
            if (pv->is_admin)
            {
                races.print_all();
                cin.get();
            }
            break;
        case 6:
            if (pv->is_admin)
            {
                races.save();
                cin.get();
                delete pv;
                return 1;
            }
            break;
        case 7:
            races.save();
            cout << "Goodbye!" << endl;
            delete pv;
            return 0;
            break;
        }
    }
    return 0;
}