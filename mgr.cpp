// Kobe Norcross, CS 260, mgr.cpp
// implementation file of the app manager

#include "mgr.h"

AppMgr::AppMgr() 
{
	initTable();
}



void AppMgr::initTable()
{
	hashTable = new Table();
	hashTable->initTable("data.txt");
}



AppMgr::~AppMgr()
{
	if (hashTable) delete hashTable;
}



// ==========================================================================================================
// 					Calls to hash table
// ==========================================================================================================
void AppMgr::displayInfo()
{
	char buffer[MAX_SIZE];
	cin.ignore(MAX_SIZE, '\n');
	cout << endl << "Please enter in a search key -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	char * key = new char[strlen(buffer)+1];
	strcpy(key, buffer);
	hashTable->display(key);
	delete [] key;
}



void AppMgr::displayTable()
{
	hashTable->displayAll();
}



void AppMgr::addData()
{
	cout << endl << endl;
	hashTable->addData();
	cout << endl << endl;
}


void AppMgr::removeData()
{
	cout << endl;
	hashTable->remove();
	cout << "Removed all of the websites reviewed with 1 star!" << endl << endl;
}



void AppMgr::editData()
{
	char buffer[MAX_SIZE];
	cin.ignore(MAX_SIZE, '\n');
	cout << endl << "Please enter in a topic name to find --> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	char * key = new char[strlen(buffer)+1];
	strcpy(key, buffer);
	hashTable->editData(key);
	delete [] key;
}



// ==========================================================================================================
// 					Main Function functions
// ==========================================================================================================
void AppMgr::printOptions()
{
	cout << endl;
	cout << "------------------------------------------------------" << endl << endl;
       	cout << "		     Website Database" 			 << endl;
	cout << "		     ----------------"			 << endl << endl;	
	cout << "1. Display websites based on a topic."			 << endl << endl;
	cout << "2. Display all of the websites." 			 << endl << endl;
	cout << "3. Add a website by topic."	 			 << endl << endl;
	cout << "4. Remove all topics with a one star rating." 	 	 << endl << endl;
	cout << "5. Edit the rating and review of a website."		 << endl << endl;
	cout << "6. Quit program."					 << endl << endl;
	cout << "------------------------------------------------------" << endl << endl;
}



void AppMgr::getUserOption(int & choice)
{
	cin >> choice;
	while (!cin || choice < 1 || choice > 6)
	{
		cout << endl;
		cin.clear();
		cin.ignore(MAX_SIZE, '\n');
		cout << "Invalid option, please try again -> ";
		cin >> choice;
		cout << endl;
	}
}


void AppMgr::mainFunction(int c)
{
	if (c == 1)
	{
		displayInfo();
	}
	else if (c == 2)
	{
		displayTable();
	}
	else if (c == 3)
	{
		addData();
	}
	else if (c == 4)
	{
		removeData();
	}
	else if (c == 5)
	{
		editData();
	}
	else
	{
		cout << endl << "Quitting..." << endl << endl;
	}	
}
