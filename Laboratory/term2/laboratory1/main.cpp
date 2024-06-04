//#include "menu.hpp"
#include "menu.hpp"
#include <iostream>
using namespace std;
int main()
{
    int choice;
    User *user = NULL;
    while (true)
    {
        system("clear");
        cout << "1. Sign in\n";
        cout << "2. Sign up\n";
        cout << "3. Quit\n";
        cout << "What would you like to do? : ";
        choose(choice);
        switch (choice)
        {
        case 1:
            char nick[LEN];
            char passw[LEN];
            system("clear");
            user = sign_in(input("nick", nick), input("password", passw));
            if (user)
            {
                cout << "Signed in succesfully!" << endl;
                cin.get();
                if (!interact_menu(user))
                    return 0;
            }
            else
            {
                cout << "User is nout found!" << endl;
                cin.get();
            }
            break;
        case 2:
            sign_up();
            break;
        case 3:
            //delete user;
            cout << "Goodbye!" << endl;
            //cout << user << endl;
            return 0;
        }
    }
}