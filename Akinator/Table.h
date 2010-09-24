#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Node
{
public:
	int a;
	Node* next;
	Node();
	Node(int);
	~Node();
	Node& operator=(const Node&);
	void deleteFromQueue();
	Node& operator++();
private:
	//Node* tmp;
};

class Queue
{
private:
	Node* head;
	Node* tail;
	Node* cur;
	Node* prev;
public:
	Queue();
	~Queue();
	void addToQueue(int);
	void addToQueue(Node*);
	void addToQueue(Queue);
	void deleteCurrent();
	void incCurrent();
	Node* currentNode();
	void setCurrentToHead();
	bool search(int);
	bool isEmpty() const;
	Node* headValue();
	bool hasSingleCapacity() const;
};

class Table
{
private:
	vector<Queue> t;
	int num;
	int n0;
public:
	Table();
	Table(int);
	~Table();
	void addToTable(int, int);
	void addToTable(Node*, int);
	Node* headValue();
	Node* minValue();
	void setCurrentToHead();
	float currency(int);
	void setN0(int);
	int getN0() const;
	int search(int);
	Node* current(int);
	void addTable(Table*);
	bool isEmpty() const;
	bool isClear() const;
};
