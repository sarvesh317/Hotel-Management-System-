#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

void intro()
{
    cout << "\n\n\t            ";
    cout << "     C++ Project On Hotel Management System";
    cout << "\n\n\t\t\t\t     MADE BY";
    cout << "\n--------------------------------------------";
    cout << "----------------------------------------";
    cout << "\n||\t\t\t\t\t\t\t\t      ||";
    cout << "\n||\t\t\t\tSarvesh Suresh Howale\t\t      ||";
    cout << "\n--------------------------------------------";
    cout << "----------------------------------------";
}

void head()
{
    cout << "--------------------------------------------";
    cout << "----------------------------------------";
    cout << "\n\t\t\t   Git-Hub Hotel \t\t       ";
    cout << "\n--------------------------------------------";
    cout << "----------------------------------------";
}

void time_delay()
{
    cout << "\n\n\n\tConnecting to Server\n\tSyncing Data";
    for (int i = 0; i < 10; ++i)
    {
        cout << ".";
        for (volatile long long j = 0; j < 9999999; ++j)
            ; // simple delay
    }
}

// Hotel class definition
class Hotel
{
private:
    int room_no;
    char name[30];
    char address[50];
    char phone[15];
    int days;
    float fare;

public:
    void main_menu();     // to display the main menu
    void add();           // to book a room
    void display();       // to display the customer record
    void rooms();         // to display allotted rooms
    void edit();          // to edit the customer record
    int check(int);       // to check room status
    void modify(int);     // to modify the record
    void delete_rec(int); // to delete the record
};

void Hotel::main_menu()
{
    int choice;
    while (choice != 5)
    {
        system("clear"); // Use system("cls") on Windows
        head();
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *"; //\n: Moves to a new line.
                                           //\t: Pushes the text to the right by adding tab spaces, helping you adjust the alignment.
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            display();
            break;
        case 3:
            rooms();
            break;
        case 4:
            edit();
            break;
        case 5:
            break;
        default:
        {
            cout << "\n\n\t\t\tWrong choice.....!!!";
            cout << "\n\t\t\tPress any key to continue....!!";
            cin.ignore();
            cin.get();
        }
        }
    }
}

void Hotel::add()
{
    system("clear");
    head();
    int r, flag;
    ofstream fout("Record.dat", ios::app);
    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;
    flag = check(r);
    if (flag)
    {
        cout << "\n Sorry..!!! Room is already booked";
    }
    else
    {
        room_no = r;
        cout << " Name: ";
        cin.ignore();
        cin.getline(name, 30);
        cout << " Address: ";
        cin.getline(address, 50);
        cout << " Phone No: ";
        cin.getline(phone, 15);
        cout << " No of Days to Checkout: ";
        cin >> days;
        fare = days * 900; // assuming fare is 900 per day
        fout.write(reinterpret_cast<char *>(this), sizeof(Hotel));
        cout << "\n Room is booked...!!!";
    }
    cout << "\n Press any key to continue.....!!";
    cin.ignore();
    cin.get();
    fout.close();
}

void Hotel::display()
{
    system("clear");
    head();
    ifstream fin("Record.dat", ios::in);
    int r, flag = 0;
    cout << "\n Enter room no: ";
    cin >> r;
    while (fin.read(reinterpret_cast<char *>(this), sizeof(Hotel)))
    {
        if (room_no == r)
        {
            system("clear");
            head();
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "\n Sorry, Room no. not found or vacant....!!";
    }
    cout << "\n\n Press any key to continue....!!";
    cin.ignore();
    cin.get();
    fin.close();
}

void Hotel::rooms()
{
    system("clear");
    head();
    ifstream fin("Record.dat", ios::in);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    while (fin.read(reinterpret_cast<char *>(this), sizeof(Hotel)))
    {
        cout << "\n Room no: " << room_no;
        cout << "\n Name: " << name;
        cout << "\n Address: " << address;
        cout << "\n Phone: " << phone;
        cout << "\n Days: " << days;
        cout << "\n Total: " << fare;
        cout << "\n**********************************";
    }
    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    cin.ignore();
    cin.get();
    fin.close();
}

void Hotel::edit()
{
    system("clear");
    head();
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;

    system("clear");
    head();
    cout << "\n Enter room no: ";
    cin >> r;
    switch (choice)
    {
    case 1:
        modify(r);
        break;
    case 2:
        delete_rec(r);
        break;
    default:
        cout << "\n Wrong Choice.....!!";
    }
    cout << "\n Press any key to continue....!!!";
    cin.ignore();
    cin.get();
}

int Hotel::check(int r)
{
    int flag = 0;
    ifstream fin("Record.dat", ios::in);
    while (fin.read(reinterpret_cast<char *>(this), sizeof(Hotel)))
    {
        if (room_no == r)
        {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

void Hotel::modify(int r)
{
    system("clear");
    head();
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read(reinterpret_cast<char *>(this), sizeof(Hotel)))
    {
        pos = file.tellg();
        if (room_no == r)
        {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cout << "\n Name: ";
            cin.ignore();
            cin.getline(name, 30);
            cout << " Address: ";
            cin.getline(address, 50);
            cout << " Phone no: ";
            cin.getline(phone, 15);
            cout << " Days: ";
            cin >> days;
            fare = days * 900;
            file.seekp(pos - sizeof(Hotel));
            file.write(reinterpret_cast<char *>(this), sizeof(Hotel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "\n Sorry, Room no. not found or vacant...!!";
    }
    file.close();
}

void Hotel::delete_rec(int r)
{
    system("clear");
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in);
    ofstream fout("temp.dat", ios::out);
    while (fin.read(reinterpret_cast<char *>(this), sizeof(Hotel)))
    {
        if (room_no == r)
        {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            cout << "\n\n Do you want to delete this record (y/n): ";
            cin >> ch;
            if (ch == 'n')
            {
                fout.write(reinterpret_cast<char *>(this), sizeof(Hotel));
            }
            flag = 1;
        }
        else
        {
            fout.write(reinterpret_cast<char *>(this), sizeof(Hotel));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
    {
        cout << "\n Sorry, room no. not found or vacant...!!";
    }
    else
    {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
        cout << "\n Record deleted...!!";
    }
}

int main()
{
    system("clear");
    intro();
    time_delay();
    Hotel h;
    h.main_menu();
    return 0;
}
