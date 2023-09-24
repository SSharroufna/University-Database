//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------
#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void displayMenu();

int main (int argc, char* argv[])
{
    if (argc < 3 )
    {
        cout << "Invalid number of arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
    }

    //Comand arguments
    string programName = argv[0];
    string fileName = argv[1];
    int htsize = stoi(argv[2]);


    // initiate both hashing classes
    HashOpenAddressing OpenAddressing(htsize);
    HashChaining chaining(htsize);


    //variables for storing inputs from user
    string courseYear;
    string courseNumber;
    string profId;
    string choose;

    int intcourseYear;
    int intcourseNumber;

    displayMenu();

    int choice;
    cin >> choice;

    while (true)
    { 
        switch (choice)
        {
            case 1:
            cout << "[OPEN ADDRESSING] Hash table populated" << endl;
            cout << "--------------------------------------------------------" << endl;
            OpenAddressing.bulkInsert(fileName);

            cout << "[CHAINING] Hash table populated" << endl;
            cout << "-------------------------------------------" << endl;
            chaining.bulkInsert(fileName);

                break;
            case 2:
                cout << "Enter course year" << endl;
                getline(cin, courseYear);
                cin >> courseYear;
    
                cout << "Enter Course number" << endl; 
                getline(cin, courseNumber);
                cin >> courseNumber;

                cout <<  "Enter a professor’s ID" << endl;
                getline(cin, profId);
                cin >> profId;

                cout << "[OPEN ADDRESSING] Search for a course" << endl;
                cout << "-------------------------------------" << endl;
                OpenAddressing.search(stoi(courseYear), stoi(courseNumber), profId);
                cout << endl << endl;

                cout << "[CHAINING] Search for a course" << endl;
                cout << "-------------------------------------" << endl;
                chaining.search(stoi(courseYear), stoi(courseNumber), profId);
                cout << endl << endl;

                break;
            case 3:
                cout <<  "Enter a professor’s ID" << endl;
                getline(cin, profId);
                cin >> profId;
            
                cout << "[OPEN ADDRESSING] Search for a professor" << endl;
                cout << "-------------------------------------" << endl;
                OpenAddressing.profDb.publicSearchProfessor(profId);
                
                cout << "[CHAINING] Search for a professor" << endl;
                cout << "-------------------------------------" << endl;
                chaining.profDb.publicSearchProfessor(profId);
        
                break;
            case 4: 
                cout << "Which hash table would you like to display the courses for (O=Open Addressing, C=Chaining)? " << endl;
                cin >> choose;

                if ( choose == "O") 
                {
                    cout << "[OPEN ADDRESSING] displayAllCourses()" << endl;
                    cout << "--------------------------------" << endl;
                    OpenAddressing.displayAllCourses();
                } 
                else if ( choose == "C")
                {
                    cout << "[CHAINING] displayAllCourses()" << endl;
                    cout << "--------------------------------" << endl;
                    chaining.displayAllCourses();
                }
                else 
                {
                    cout << "Please enter a valid option ( O or C ). " << endl;
                }
                break;
            case 5:
                cout << "Exiting the program...goodbye!!" << endl;
                break;
                
            default:
               cout << "Please Enter a valid option." << endl;
               
        }
        displayMenu();
        cin >> choice;
    }
    return 0;
} 

void displayMenu()
{
    //Display the main menu
    cout << "======= Main Menu =======" << endl;
        
    cout <<  "1. Populate hash tables" << endl;
    cout <<  "2. Search for a course" << endl;
    cout <<  "3. Search for a professor" << endl;
    cout <<  "4. Display all courses" << endl;
    cout <<  "5. Exit" << endl;

    cout << "Please Choose an option: " << endl;
}