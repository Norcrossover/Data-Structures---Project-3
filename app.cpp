// Kobe Norcross, CS 260, app.cpp
//
// Input:
// 	- Take in data from the external file
// 	- Take in data from user for a new website
//
// Output:
//	- Websites data upon key given
//	- Display all
//

#include "mgr.h"

int main()
{
	AppMgr mgr;
	int c = 0;
	
	while (c != 6)
        {
		mgr.printOptions();
		cout << "Please enter an option given in the list -> ";
		mgr.getUserOption(c);
		mgr.mainFunction(c);
        }

	return 0;
}
