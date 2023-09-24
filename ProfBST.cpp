//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

ProfBST::ProfBST()
{
    root = nullptr;
}

void ProfBST::deleteHelper(Professor *temp)
{
    if ( temp!=nullptr ) 
    {
        deleteHelper(temp->left);
        deleteHelper(temp->right);
        delete (temp);
        temp = nullptr;
    } 
}

ProfBST::~ProfBST()
{
    deleteHelper(root);
}

void ProfBST::addProfessor(string profId, string profName)
{
    Professor* newPro = new Professor(profId, profName);
    Professor* curr = root;

     if (root == nullptr) 
     {
        root = newPro;
        return;
     } 

     while (true)
     {
        if (  newPro->profId < curr->profId ) 
        {
            if (curr->left == nullptr)
            {
                curr->left = newPro;
                return;
            }
            curr = curr->left;
        } 
        if ( curr->profId < newPro->profId )
        {
            if (curr->right == nullptr)
            {
                curr->right= newPro;
                return;
            }
            curr = curr->right;
        }
     }
}

Professor* ProfBST::searchProfessorHelper(Professor *root, string profId)
{
    if ( root == nullptr )
    {
        return nullptr;
    } 
    else if (root->profId == profId)
    {
        return root;
    } 
    else if (profId > root->profId) 
    {
        return searchProfessorHelper(root->right, profId);
    }
   
    return searchProfessorHelper(root->left, profId);
    
}

Professor* ProfBST::searchProfessor(string profId)
{
    return searchProfessorHelper(root, profId);
}

void ProfBST::publicSearchProfessor(string profId)
{
    Professor* pro = searchProfessor(profId);

    if ( pro == nullptr )
    {
        cout << "Professor does not exists!" << endl;
        return ;
    }
    else 
    {
        displayProfessorInfo(pro);
    }
}

void ProfBST::displayProfessorInfo(Professor* p)
{
    if (p == nullptr)
    {
        cout << "Professor does not exists!" << endl;
    } 
    else 
    {
        cout << "Professor Name: " << p->profName << endl;
       
        for (int i = 0; i < p->coursesTaught.size(); i++)
        {
            cout << p->coursesTaught[i]->courseName << endl;
        }
    }
}
