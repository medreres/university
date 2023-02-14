#include <iostream>
#include "datetime.hpp"
#include "list.hpp"
#include <fstream>
using namespace std;
void printMenu();
void addNewDate();
int input();
void printList(List<DateTime> &t1);
const char *PATH = "datetime.txt";
enum
{
    ALL = 1,
    ADD,
    DELETE,
    EDIT,
    SAVE,
    READ,
    FORMAT,
    SORT_ASC,
    EXIT
};
int main()
{
    bool numeric = true;
    // list of datetimes events
    List<DateTime> timesList;

    // print menu for user, check if input is correct

    while (true)
    {
        system("clear");
        printMenu();
        int choice = input();
        switch (choice)
        {
        case SORT_ASC:
        {
            if (timesList.size() == 0)
            {
                cout << "List is empty. Nothing to sort!" << endl;
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }
            timesList.mergeSort();
            cout << "List sorted successfully!" << endl;
            cin.get();
            cin.ignore(1000, '\n');
            break;
        }
        case EDIT:
        {
            if (timesList.size() == 0)
            {
                cout << "List is empty. Nothing to edit!" << endl;
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }

            printList(timesList);

            cout << "Enter index of date to edit, 'q' to quit" << endl;
            char ind;
            cin >> ind;
            if (ind == 'q')
            {
                cout << "Quitting..." << endl;
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }
            else if (ind - 48 > -1 && ind - 48 < timesList.size())
            {
                DateTime dt, old = timesList[ind - 48];
                cout << "Enter new value: (yy:mm:dd:hh:mm:ss): ";
                cin >> dt;
                timesList[ind - 48] = dt;
                cout << "Edited " << old << " to " << timesList[ind - 48] << " successfully!" << endl;
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }
            break;
        }
        case SAVE:
        {
            if (numeric == false)
                for (int i = 0; i < timesList.size(); i++)
                    timesList[i].numericView();

            if (timesList.size() == 0)
            {
                cout << "Nothing to save!" << endl;
                cin.ignore(1000, '\n');
                cin.get();
                break;
            }
            ofstream file(PATH);
            if (!file)
            {
                cout << "Can't find file with such name" << endl;
                cin.ignore(1000, '\n');
                cin.get();
                break;
            }

            for (int i = 0; i < timesList.size(); i++)
            {
                file << timesList[i] << endl;
            }
            cout << "Saved successfully!" << endl;
            cin.ignore(1000, '\n');
            cin.get();
            break;
            file.close();
            break;
        }
        case READ:
        {

            ifstream file(PATH);
            if (!file)
            {
                cout << "Can't find file with such name" << endl;
                cin.ignore(1000, '\n');
                cin.get();
                break;
            }
            DateTime dt;
            while (!file.eof())
            {
                try
                {
                    file >> dt;
                    timesList.append(dt);
                }
                catch (std::invalid_argument &e)
                {
                    break;
                }
            }

            file.close();

            cout << "File read successfully!" << endl;
            cin.ignore(1000, '\n');
            cin.get();
            break;
            break;
        }
        case FORMAT:
        {
            if (numeric)
                for (int i = 0; i < timesList.size(); i++)
                    timesList[i].stringView();
            else
                for (int i = 0; i < timesList.size(); i++)
                    timesList[i].numericView();

            numeric = !numeric;
            cout << "Format changed successfully!" << endl;
            cin.ignore(1000, '\n');
            cin.get();
            break;
        }
        case ADD:
        {
            cout << "Enter your date: (yy:mm:dd:hh:mm::ss)" << endl;
            DateTime t1;
            cin >> t1;
            timesList.append(t1);
            cout << "Added successfully!";
            cin.get();
            cin.ignore(1000, '\n');
            break;
        }
        case ALL:
        {
            if (timesList.size() == 0)
            {
                cout << "List is empty. Nothing to show!" << endl;
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }
            printList(timesList);

            cin.get();
            cin.ignore(1000, '\n');
            break;
        }
        case DELETE:
        {
            if (timesList.size() == 0)
            {
                cout << "List is empty, nothing to remove!";
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }
            printList(timesList);

            cout << "Enter index of date to delete, 'q' to quit" << endl;
            char ind;
            cin >> ind;
            if (ind == 'q')
            {
                cout << "Quitting..." << endl;
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }
            else if (ind - 48 > -1 && ind - 48 < timesList.size())
            {
                DateTime copy = timesList[ind - 48];
                timesList.remove(ind - 48);
                cout << "Removed " << copy << " successfully!" << endl;
                cin.get();
                cin.ignore(1000, '\n');
                break;
            }
        }
        case EXIT:
            cout << "See you soon" << endl;
            return 0;
        }
    }
}

int input()
{
    cout << "Your choice: ";
    int ch;
    cin >> ch;
    while (ch > EXIT && ch < ALL)
    {
        cout << "Error! Invalid input. Try again: ";
        cin.ignore(100000, '\n');
        cin >> ch;
    }
    return ch;
}
void printList(List<DateTime> &t1)
{
    for (int i = 0; i < t1.size(); i++)
    {
        cout << i << ". " << t1.operator[](i) << endl;
    }
}

void printMenu()
{
    cout << "1. View all dates\n2. Add new date\n3. Delete date\n4. Edit date\n5. Save to file\n6. Read from file\n7. Change form(string/numeric)\n8. Sort ascending \n9. Exit" << endl;
}
