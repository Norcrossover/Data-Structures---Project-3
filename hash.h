// Kobe Norcross, CS 260, hash.h
// This is the header file of the Table ADT

#include "data.h"

class Table
{
public:
	// constructors
	Table();
	Table(Table& aTable);
	
	// init 
	void initTable(const char * fileName);

	// destructors
	~Table();

	// accessors
	void display(const char * key);
	bool displayAll();

	// mutators
	void addData();
	void insert(Data *& data);
	void remove();
	bool editData(const char * key);

	// operator overload
	const Table& operator=(Table& aTable);
	friend ostream& operator<<(ostream& out, const Table*& srcTable);

private:
	struct Node
	{
		Node()
		{
			data = nullptr;
			next = nullptr;
		}
		Node(Data *& newData)
		{
			data = newData;
		}
		~Node()
		{
			if (data != nullptr) delete data;
		}
		Data * data;
		Node * next;
	};

	// 
	Node ** table;
	const static int init_capacity = 317;
	const static int growth_factor = 2;
	int 		 capacity;
	int 		 size;

	// destructor functions
	void destroy();
	void destroyChain();
	void destroyChain(Node *& head);
	void writeToFile(Node * head, ostream& out);

	// hash function
	int hashFunction(const char * key) const;
	
	// Recursive Calls
	bool retrieve(const char * key, int& idx);
	bool retrieve(const char * key, int& idx, Node * curr);
	bool displayAll(Node * head);
	void copyChain(Node * srcHead, Node *& destHead);
	void remove(Node * prev, Node *& curr);
	bool editData(const char * website, Node *& curr);

	void displayChain(ostream& out, Node * curr) const;

};

