// Kobe Norcross, CS 260, data.h
// This is the header file of the data class

#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_SIZE = 256;

class Data
{
public:
	// constructor
	Data();

	// destructor
	~Data();

	// accessors
	char * getName() const;
	char * getAddress() const;
	char * getSummary() const;
	char * getReview() const;
	int getRating() const;
	void display() const;

	// mutators
	void setName(const char * name);
	void setAddress(const char * address);
	void setSummary(const char * summary);
	void setReview(const char * review);
	void setRating(int rating);

	// operator overload
	void operator=(const Data& data);

	// write to file 
	void writeToFile(ostream& out);

private:
	char * name;
	char * address;
	char * summary;
	char * review;
	int rating;
};

