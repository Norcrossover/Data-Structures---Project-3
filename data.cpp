// Kobe Norcross, CS 260, topic.cpp
// This is the implementation file for the topic class

#include "data.h"

//------------------------------------------------------------------------------------------------
//				Constructor/Destructor
//------------------------------------------------------------------------------------------------
Data::Data() : name(nullptr), address(nullptr), summary(nullptr), review(nullptr), rating(0) {}


Data::~Data()
{
	if (name) delete [] name;
	if (address) delete [] address;
	if (summary) delete [] summary;
	if (review) delete [] review;
	rating = 0;
}



//------------------------------------------------------------------------------------------------
//				   	Mutators	
//------------------------------------------------------------------------------------------------
void Data::setName(const char * name)
{
	if (this->name != nullptr) delete [] this->name;
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}



void Data::setAddress(const char * address)
{
	if (this->address != nullptr) delete [] this->address;
	this->address = new char[strlen(address)+1];
	strcpy(this->address, address);
}



void Data::setSummary(const char * summary)
{
	if (this->summary != nullptr) delete [] this->summary;
	this->summary = new char[strlen(summary)+1];
	strcpy(this->summary, summary);
}



void Data::setReview(const char * review)
{
	if (this->review != nullptr) delete [] this->review;
	this->review = new char[strlen(review)+1];
	strcpy(this->review, review);
}



void Data::setRating(int rating)
{
	this->rating = rating;
}


	
//------------------------------------------------------------------------------------------------
//					Accessors
//------------------------------------------------------------------------------------------------
char * Data::getName() const
{
	return name;
}



char * Data::getAddress() const
{
	return address;
}



char * Data::getSummary() const
{
	return summary;
}



char * Data::getReview() const
{
	return review;
}



int Data::getRating() const
{
	return rating;
}



void Data::display() const
{
	cout << "\t" << "Name: 		 "  << "\t" << getName()    << endl;
	cout << "\t" << "Website Address: " << "\t" << getAddress() << endl;
	cout << "\t" << "Summary: 	 "  << "\t" << getSummary() << endl;
	cout << "\t" << "Review: 	 "  << "\t" << getReview()  << endl;
	cout << "\t" << "Rating: 	 "  << "\t" << getRating()  << endl;
}



// operator overload
void Data::operator=(const Data& data)
{
	setName(data.name);
	setAddress(data.address);
	setSummary(data.summary);
	setRating(data.rating);
	setReview(data.review);
}



// write to file
void Data::writeToFile(ostream& out)
{
	out << name << ';' << address << ';' << summary << ';' << review << ';' << rating << '\n';
}
