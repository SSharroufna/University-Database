//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

HashOpenAddressing::HashOpenAddressing(int size)
{
    hashTableSize = size;
    hashTable = new Course*[size];

    for ( int i =0; i<size; i++)
    {
        hashTable[i] = nullptr;
    }
}

HashOpenAddressing::~HashOpenAddressing()
{
    for (int i = 0; i < hashTableSize; ++i)
    {
        Course* curr = hashTable[i];
       hashTable[i] = nullptr;
       delete curr;
    }    
    delete[] hashTable;
}

int HashOpenAddressing::hash(int courseNumber)
{
    int hash = courseNumber % hashTableSize ;
    return hash;
}

void HashOpenAddressing::bulkInsert(string filename)
{
    ifstream readFile;
    readFile.open(filename.c_str());

    if (readFile.fail())
    {
        return;
    }

    string temp;
    string year;
    string department; 
    string course_name;
    string course_num;
    string prof_id;
    string prof_fname;
    string prof_lname;

    int searchesCounter = 0;
    int collisonsCounter = 0;
    int items = 0;

    getline(readFile,temp); //Ignoring the first line.

    while (getline(readFile,temp))
    {
        istringstream readString(temp);

        getline(readString, year, ',');
        getline(readString, department, ',');
        getline(readString, course_num, ',');
        getline(readString, course_name, ',');
        getline(readString, prof_id, ',');
        getline(readString, prof_fname, ',');
        getline(readString, prof_lname);

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
    Course* newCourse = new Course(stoi(year), department, stoi(course_num), course_name, pro);
   
    //Add the course to the professor list, and add prof to course
    pro->coursesTaught.push_back(newCourse);
    newCourse->prof = pro;
   
    //insert into hash table - chaining (doubly linked list)
    int index = hash(newCourse->courseNum);
    
    if (hashTable[index] == nullptr) // add newCourse if hash table has no collision 
    { 
        hashTable[index] = newCourse;
        items++;
    } 
    else 
    {
        collisonsCounter++;
        int i = 0;
    
        while (items < hashTableSize)
        {
            i++;
            searchesCounter++;
            index = (index + (i * i)) % hashTableSize; // Quadratic probing to find the new index
            
             if(hashTable[index] == nullptr)
             {
                hashTable[index] = newCourse;
                items++;
                break;
             }
        }
    }
}
  cout << "Collisions using open addressing: " << collisonsCounter << endl;
  cout << "Search operations using open addressing: " << searchesCounter << endl;
  
  readFile.close();
}

void HashOpenAddressing::search(int courseYear, int courseNumber, string profId) //Using Quadratic Probing to search for the course
{
    //insert into hash table - chaining (doubly linked list)
    //need to maintain DLL 
    int searchOperations = 0;
    int i = 0;

    int index = hash(courseNumber);
    Course *head = hashTable[index];
    
    while (hashTable[index]->year != courseYear || hashTable[index]->courseNum != courseNumber || hashTable[index]->prof->profId != profId)
    {
        i++;
        searchOperations++;
        index = (index + (i * i)) % hashTableSize; // Quadratic probing to find the new index
    }  
    cout << "Search operations using open addressing: " << searchOperations << endl;
    displayCourseInfo(hashTable[index]);
    return;
}

void HashOpenAddressing::displayAllCourses()
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

void HashOpenAddressing::displayCourseInfo(Course* c)
{
	cout << c->year << " " << c->department  << ": " << c->courseName << " " << c->courseNum << " " << c->prof->profName;
}