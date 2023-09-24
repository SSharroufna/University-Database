//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"

using namespace std;

HashChaining::HashChaining(int size)
{
    hashTableSize = size;
    hashTable = new Course*[size];

    for ( int i =0; i<size; i++)
    {
        hashTable[i] = nullptr;
    }
}

HashChaining::~HashChaining() //Hash table constructer 
{
    for(int i = 0; i < hashTableSize; i++) // For every bucket
    { 
        Course*temp = hashTable[i];
        while(temp != nullptr) 
        {
            temp = temp->next;
            delete temp;
        } 
        temp = nullptr;
    } 
    delete[] hashTable;
}

int HashChaining::hash(int courseNumber) // Calculate the hash function
{
    int hash = courseNumber % hashTableSize; 
    return hash;
}

void HashChaining::bulkInsert(string filename)
{
    ifstream readFile;
    readFile.open(filename);

    if (readFile.fail())
    {
        return;
    }

    string temp = " ";
    string year = " ";
    string department; 
    string course_name;
    string course_num;
    string prof_id;
    string prof_fname;
    string prof_lname;

    int searchesCounter = 0;
    int collisonsCounter = 0;

    getline(readFile,temp); //Ignoring the first line.

    while (getline(readFile,temp) )
    {
        stringstream readString (temp);

        getline(readString, year, ',');
        getline(readString, department, ',');
        getline(readString, course_num, ',');
        getline(readString, course_name, ',');
        getline(readString, prof_id, ',');
        getline(readString, prof_fname, ',');
        getline(readString, prof_lname, ',');

    //search if the professor exist - using proDb 
    //if professor null, add professor to BST using proDb

    Professor *pro = profDb.searchProfessor(prof_id);

    if (pro == nullptr)
    {
        string name = prof_fname + " " + prof_lname;
        profDb.addProfessor(prof_id, name);
        pro = profDb.searchProfessor(prof_id);
    }

    //create course ... = new course()
    Course* newCourse = new Course(stoi(year), department, stoi(course_num), course_name, nullptr);

    //Add the course to the professor list, and add prof to course
    newCourse->prof = pro;
    pro->coursesTaught.push_back(newCourse);
    
    //insert into hash table - chaining (doubly linked list)
    int index = hash(newCourse->courseNum);

    Course* curr = hashTable[index]; // Create me a linked list node with value to be the keu and next pointer to be null.
    Course* prev = nullptr;

    if (curr == nullptr){ // add newCourse if hash table has no collision 
        hashTable[index] = newCourse;
    } 
    else 
    {
        collisonsCounter++;
        
        while (curr->next != nullptr)
        {
            searchesCounter++;
            curr = curr->next;
            
        }
        searchesCounter++;
        curr->next = newCourse;
        newCourse->previous = curr;
    }
    }
     cout << "Collisions using chaining: " << collisonsCounter << endl;
     cout << "Search operations using chaining: " << searchesCounter << endl;
}


void HashChaining::search(int courseYear, int courseNumber, string profId) //Searches for a course using doubly linked list
{
    int searchOperations = 0;
    int index = hash(courseNumber);
  
    while (hashTable[index] != nullptr ) 
    {
        if( hashTable[index]->year == courseYear && hashTable[index]->courseNum == courseNumber && hashTable[index]->prof->profId == profId)
        {
            cout << "Search operations using chaining: " << searchOperations << endl;
            displayCourseInfo(hashTable[index]);
            return;
        }
        searchOperations++;
        hashTable[index] = hashTable[index]->next;
    } 
}     

void HashChaining::displayAllCourses()
{
    for (int i = 0; i < hashTableSize; i++) 
    {
        Course *currNode = hashTable[i];
        
        while(currNode != nullptr)
        {
            displayCourseInfo(currNode);
            currNode = currNode->next;
        }
        cout << endl;
    }
}

void HashChaining::displayCourseInfo(Course* c)
{
    cout << c->year << " " << c->department  << ": " << c->courseName << " " << c->courseNum << " " << c->prof->profName;
}