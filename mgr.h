// Kobe Norcross, CS 260, mgr.h
// This is the app manager header file

#include "hash.h"

class AppMgr
{
public:
	// constructor and destructor
	AppMgr();
	~AppMgr();

	// Calls to hash table
	void displayInfo();
	void displayTable();
	void addData();
	void removeData();
	void editData();

	// Main Functions
	void printOptions();
	void mainFunction(int c);
	void getUserOption(int& choice);

private:
	Table * hashTable;
	void initTable();
};
