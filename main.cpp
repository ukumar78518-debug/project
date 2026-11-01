
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Item
{
    int id;
    string name, category, location, description;
    
};

Item lost[100], found[100];
int lostCount = 0, foundCount = 0;
int nextId = 1;

// Load records from file
void loadData()
{
    ifstream fin;

    fin.open("lost.txt");
    while (lostCount < 100 && fin >> lost[lostCount].id)
    {
        fin.ignore();
        getline(fin, lost[lostCount].name);
        getline(fin, lost[lostCount].category);
        getline(fin, lost[lostCount].location);
        getline(fin, lost[lostCount].description);

        nextId = max(nextId, lost[lostCount].id + 1);
        lostCount++;
    }
    fin.close();

    fin.open("found.txt");
    while (foundCount < 100 && fin >> found[foundCount].id)
    {
        fin.ignore();
        getline(fin, found[foundCount].name);
        getline(fin, found[foundCount].category);
        getline(fin, found[foundCount].location);
        getline(fin, found[foundCount].description);

        nextId = max(nextId, found[foundCount].id + 1);
        foundCount++;
    }
    fin.close();
}

// Save records in files
void saveData()
{
    ofstream fout;

    fout.open("lost.txt");
    for (int i = 0; i < lostCount; i++)
    {
        fout << lost[i].id << endl;
        fout << lost[i].name << endl;
        fout << lost[i].category << endl;
        fout << lost[i].location << endl;
        fout << lost[i].description << endl;
    }
    fout.close();

    fout.open("found.txt");
    for (int i = 0; i < foundCount; i++)
    {
        fout << found[i].id << endl;
        fout << found[i].name << endl;
        fout << found[i].category << endl;
        fout << found[i].location << endl;
        fout << found[i].description << endl;
    }
    fout.close();
}

// Student Login
void login()
{
    string name, studentID;

    cout << "\nEnter Student Name: ";
    getline(cin, name);

    cout << "Enter Student ID: ";
    getline(cin, studentID);

    cout << "\nWelcome " << name << "!\n";
}

// Report Lost Item
void reportLost()
{
    if (lostCount >= 100)
    {
        cout << "Lost record limit reached!\n";
        return;
    }

    lost[lostCount].id = nextId++;

    cout << "Enter Item Name: ";
    getline(cin, lost[lostCount].name);

    cout << "Enter Category: ";
    getline(cin, lost[lostCount].category);

    cout << "Enter Location: ";
    getline(cin, lost[lostCount].location);

    cout << "Enter Description: ";
    getline(cin, lost[lostCount].description);

    lostCount++;
    saveData();

    cout << "\nLost Item Reported Successfully!\n";
}

// Report Found Item
void reportFound()
{
    if (foundCount >= 100)
    {
        cout << "Found record limit reached!\n";
        return;
    }

    found[foundCount].id = nextId++;

    cout << "Enter Item Name: ";
    getline(cin, found[foundCount].name);

    cout << "Enter Category: ";
    getline(cin, found[foundCount].category);

    cout << "Enter Location: ";
    getline(cin, found[foundCount].location);

    cout << "Enter Description: ";
    getline(cin, found[foundCount].description);

    foundCount++;
    saveData();

    cout << "\nFound Item Reported Successfully!\n";
}

// Search Item
void searchItem()
{
    string keyword;
    bool flag = false;

    cout << "Enter Item Name to Search: ";
    getline(cin, keyword);

    cout << "\nLost Records:\n";

    for (int i = 0; i < lostCount; i++)
    {
        if (lost[i].name.find(keyword) != string::npos)
        {
            cout << lost[i].id << " - " << lost[i].name
                 << " - " << lost[i].location << endl;
            flag = true;
        }
    }

    cout << "\nFound Records:\n";

    for (int i = 0; i < foundCount; i++)
    {
        if (found[i].name.find(keyword) != string::npos)
        {
            cout << found[i].id << " - " << found[i].name
                 << " - " << found[i].location << endl;
            flag = true;
        }
    }

    if (!flag)
        cout << "No Item Found!\n";
}

// Auto Match Lost and Found Items
void autoMatch()
{
    bool match = false;

    cout << "\nMatching Records:\n";

    for (int i = 0; i < lostCount; i++)
    {
        for (int j = 0; j < foundCount; j++)
        {
            string a = lost[i].name;
            string b = found[j].name;

            transform(a.begin(), a.end(), a.begin(), ::tolower);
            transform(b.begin(), b.end(), b.begin(), ::tolower);

            if (a == b)
            {
                cout << "\nPossible Match Found!";
                cout << "\nLost Item: " << lost[i].name;
                cout << "\nFound Item: " << found[j].name;
                cout << "\nLost Location: " << lost[i].location;
                cout << "\nFound Location: " << found[j].location << endl;

                match = true;
            }
        }
    }

    if (!match)
        cout << "No Matching Items Found!\n";
}

// View All Records
void viewRecords()
{
    // Sort lost records by item name
    for (int i = 0; i < lostCount - 1; i++)
    {
        for (int j = i + 1; j < lostCount; j++)
        {
            if (lost[i].name > lost[j].name)
                swap(lost[i], lost[j]);
        }
    }

    cout << "\n--- LOST ITEMS ---\n";

    for (int i = 0; i < lostCount; i++)
    {
        cout << "\nID: " << lost[i].id;
        cout << "\nName: " << lost[i].name;
        cout << "\nCategory: " << lost[i].category;
        cout << "\nLocation: " << lost[i].location;
        cout << "\nDescription: " << lost[i].description << endl;
    }

    cout << "\n--- FOUND ITEMS ---\n";

    for (int i = 0; i < foundCount; i++)
    {
        cout << "\nID: " << found[i].id;
        cout << "\nName: " << found[i].name;
        cout << "\nCategory: " << found[i].category;
        cout << "\nLocation: " << found[i].location;
        cout << "\nDescription: " << found[i].description << endl;
    }

    saveData();
}

// Delete Record
void deleteRecord()
{
    int type, id;
    bool deleted = false;

    cout << "\n1. Delete Lost Record";
    cout << "\n2. Delete Found Record";
    cout << "\nEnter Choice: ";
    cin >> type;

    cout << "Enter Record ID: ";
    cin >> id;
    cin.ignore();

    if (type == 1)
    {
        for (int i = 0; i < lostCount; i++)
        {
            if (lost[i].id == id)
            {
                for (int j = i; j < lostCount - 1; j++)
                    lost[j] = lost[j + 1];

                lostCount--;
                deleted = true;
                break;
            }
        }
    }
    else if (type == 2)
    {
        for (int i = 0; i < foundCount; i++)
        {
            if (found[i].id == id)
            {
                for (int j = i; j < foundCount - 1; j++)
                    found[j] = found[j + 1];

                foundCount--;
                deleted = true;
                break;
            }
        }
    }

    saveData();

    if (deleted)
        cout << "Record Deleted Successfully!\n";
    else
        cout << "Record Not Found!\n";
}

// Item Statistics
void statistics()
{
    cout << "\n--- ITEM STATISTICS ---\n";
    cout << "Total Lost Items: " << lostCount << endl;
    cout << "Total Found Items: " << foundCount << endl;
    cout << "Total Records: " << lostCount + foundCount << endl;
}

// Export Report
void exportReport()
{
    ofstream fout("report.txt");

    fout << "--- LOST ITEMS ---\n";

    for (int i = 0; i < lostCount; i++)
    {
        fout << lost[i].id << " "
             << lost[i].name << " "
             << lost[i].location << endl;
    }

    fout << "\n--- FOUND ITEMS ---\n";

    for (int i = 0; i < foundCount; i++)
    {
        fout << found[i].id << " "
             << found[i].name << " "
             << found[i].location << endl;
    }

    fout.close();

    cout << "Report Exported Successfully to report.txt!\n";
}

// Main Function
int main()
{
    int choice;

    loadData();
    login();

    do
    {
        cout << "\n===== SMART CAMPUS LOST & FOUND SYSTEM =====";
        cout << "\n1. Report Lost Item";
        cout << "\n2. Report Found Item";
        cout << "\n3. Search Item";
        cout << "\n4. Auto Match Lost & Found";
        cout << "\n5. View All Records";
        cout << "\n6. Delete Record";
        cout << "\n7. Item Statistics";
        cout << "\n8. Export Report";
        cout << "\n9. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                reportLost();
                break;

            case 2:
                reportFound();
                break;

            case 3:
                searchItem();
                break;

            case 4:
                autoMatch();
                break;

            case 5:
                viewRecords();
                break;

            case 6:
                deleteRecord();
                break;

            case 7:
                statistics();
                break;

            case 8:
                exportReport();
                break;

            case 9:
                cout << "\nThank You! Exiting Program.\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 9);

    return 0;
}
