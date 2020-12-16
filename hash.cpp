// Kobe Norcross, CS 260, hash.cpp
// This is the implementation file of the Table ADT

#include "hash.h"

//-------------------------------------------------------------------------
//			Constructors/Destructor
//-------------------------------------------------------------------------
Table::Table() : size(0), capacity(init_capacity)
{
	table = new Node * [capacity];
	for (int i = 0; i < capacity; i++) table[i] = nullptr;
}



// Initialization of the table from the list
void Table::initTable(const char * fileName)
{
	char strBuffer[MAX_SIZE];
	int intBuffer;
	ifstream inputFile;
	inputFile.open(fileName);
	if (inputFile.good())
	{
		while (!inputFile.eof())
		{
			Data * data = new Data();
			//name
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setName(strBuffer);
			//address
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setAddress(strBuffer);
			//summary
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setSummary(strBuffer);
			//review
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setReview(strBuffer);
			//rating
			inputFile >> intBuffer;
			data->setRating(intBuffer);
			inputFile.get();
			insert(data);
			size++;
		}
	}
	else
	{
		cerr << "Could not open file" << endl;
		exit(1);
	}
}


Table::Table(Table& aTable)
{
	*this = aTable;
}



Table::~Table()
{
	destroy();
}


void Table::destroy()
{
	ofstream out;
	out.open("data.txt");
	for (int i = 0; i < capacity; i++) 
	{
		if (out.good()) writeToFile(table[i], out);
		destroyChain(table[i]);
	}
	if (table) delete [] table;
	out.close();
}



void Table::writeToFile(Node * curr, ostream& out)
{
	if (curr)
	{
		curr->data->writeToFile(out);
		writeToFile(curr->next, out);
	}
}



void Table::destroyChain(Node *& head)
{
	if (head)
	{
		destroyChain(head->next);
		delete head;
		head = nullptr;
	}
}



//-------------------------------------------------------------------------
//			Accessors
//-------------------------------------------------------------------------
bool Table::retrieve(const char * key, int& idx)
{
	idx = hashFunction(key);
	if (table[idx])
	{
		cout << endl << "\t\tData found at key" << endl;
		cout << "\t\t-----------------" << endl << endl;
		return retrieve(key, idx, table[idx]);
	}
	return false;
}



bool Table::retrieve(const char * key, int& idx, Node * curr)
{
	if (curr)
	{
		if (strcmp(key, curr->data->getName()) == 0)
		{
			curr->data->display();
			cout << endl << endl;
		}
		return retrieve(key, idx, curr->next);
	}
	return true;
}	



void Table::display(const char * key) 
{
	int idx = 0;
	if (retrieve(key, idx) == false)
	{
		cout << endl << key << " could not be found." << endl << endl;
		return;
	}
}



bool Table::displayAll() 
{
	if (table)
	{
		for (int i = 0; i < capacity; i++)
		{
			cout << "------------------------------------------------------" << endl;
			cout << endl << "\t" << "\t" << "\t" << "Topic " << i << ". " << endl;
			displayAll(table[i]);
			cout << endl;
		}
		return true;
	}
	return false;
}



bool Table::displayAll(Node * head)
{
	if (head)
	{
		head->data->display();
		cout << endl;
		displayAll(head->next);
	}
	return true;
}



//-------------------------------------------------------------------------
//		    	Mutators
//-------------------------------------------------------------------------
void Table::insert(Data *& data)
{
	int index = hashFunction(data->getName());
	Node * newNode = new Node(data);
	newNode->next = table[index];
	table[index] = newNode;
	size++;
}



void Table::remove()
{
	// goes through the table
	for (int i = 0; i < capacity; i++)
	{
		// checks if it is empty or not
		if (table[i] != nullptr)
		{
/*
			Node * curr = table[i];
			Node * prev = nullptr;
			while (curr)
			{
				if (curr->data->getRating() == 1)
				{
					// if the curr node is the head node
					if (curr == table[i])
					{
						table[i] = curr->next;
						delete curr;
						curr = table[i];
					}
					// else curr is not the head node
					else
					{
						prev->next = curr->next;
						delete curr;
						curr = prev->next;
					}
				}
				prev = curr;
				curr = curr->next;
			}	
*/
			Node * curr = table[i];
			Node * next = curr->next;
			while (next)
			{
				if (curr->data->getRating() == 1)
				{
					if (curr == table[i]) 
					{
						table[i] = curr->next;
						delete curr;
						curr = table[i];
					}
					else
					{
						delete curr;
						curr = next;
					}
					next = curr->next;
				}
				else if (next->data->getRating() == 1)
				{
					curr->next = next->next;	
					delete next;
					next = curr->next;
				}
				else
				{
					curr = next;
					next = next->next;
				}
			}
			if (curr->data->getRating() == 1)
			{
					table[i] = curr->next;
					delete curr;
			}
		}
	}
}




void Table::addData()
{
	cin.ignore(MAX_SIZE, '\n');
	char buffer[MAX_SIZE];
	int rating;
	Data * data = new Data;

	// get topic name
	cout << "Enter the name of the topic" << endl << "-> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setName(buffer);

	// get web address
	cout << "Enter the address of the website" << endl << " -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setAddress(buffer);
	
	// get summary of data
	cout << "Enter a brief summary of what the topic is about" << endl << " -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setSummary(buffer);

	// get review of data
	cout << "Enter a review on the topic" << endl << " -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setReview(buffer);
		
	// get rating int
	cout << "Enter a rating (1-5)" << endl << " -> ";
	cin >> rating;
	while (!cin || rating < 1 || rating > 5)
	{
		cout << endl;
		cin.clear();
		cin.ignore(MAX_SIZE, '\n');
		cout << "Invalid input, please enter a valid rating [1-5] -> ";
		cin >> rating;
	}
	data->setRating(rating);

	// add data to the table
	insert(data);
}



// goes to the element in the table where it should be located
// then invokes the search through the chain
bool Table::editData(const char * key)
{
	int idx = hashFunction(key);
	bool retVal = false;
	if (table[idx])
	{
		char buffer[MAX_SIZE];
		cout << endl << endl << "Please enter in the address of the website" << endl;
		cout << "-> ";
		cin.getline(buffer, MAX_SIZE, '\n');
		char * website = new char[strlen(buffer)+1];
		strcpy(website, buffer);
		retVal = editData(website, table[idx]);
		delete [] website;
	}
	return retVal;
}



// searches the chain for the address
// returns true if it finds it and edits the data
// returns false if it couldn't be found
bool Table::editData(const char * website, Node *& curr)
{
	if (curr)
	{
		// compare's the website address to the website passed in to see if there is a match
		if (strcmp(curr->data->getAddress(), website) == 0)
		{
			char buffer[MAX_SIZE];
			int rating;
			cout << endl << endl << "Please give a new review of the website" << endl;
			cout << "-> ";
			cin.getline(buffer, MAX_SIZE, '\n');
			curr->data->setReview(buffer);
			cout << endl << "Please enter a new rating -> ";
			cin >> rating;
			while (!cin || rating < 1 || rating > 5)
			{
				cout << endl;
				cin.clear();	
				cin.ignore(MAX_SIZE, '\n');
				cout << "Invalid input, please enter a valid rating [1-5] -> ";
				cin >> rating;
			}
			curr->data->setRating(rating);	
			return true;
		}
		return editData(website, curr->next);
	}
	return false;
}


//-------------------------------------------------------------------------
//			Hash Function				
//-------------------------------------------------------------------------
int Table::hashFunction(const char * key) const
{
	int hash = 0;
	int index = 0;
	for (; *key != '\0'; key++)
	{
  		hash += ((*key)*index);
		index++;
	}
	return hash % capacity;
}





//-------------------------------------------------------------------------
//			Misc. Functions
//-------------------------------------------------------------------------
const Table& Table::operator=(Table& aTable)
{
	if (this == &aTable) return *this;
	if (table) destroy();
	size = aTable.size;
	capacity = aTable.capacity;
	table = new Node * [capacity];
	for (int i = 0; i < capacity; i++)
	{
		table[i] = nullptr;
		copyChain(aTable.table[i], table[i]);
	}
	return *this;
}


void Table::copyChain(Node * srcHead, Node *& destHead)
{
	if (srcHead)
	{
		destHead = new Node(srcHead->data);
		copyChain(srcHead->next, destHead->next);
	}
}




