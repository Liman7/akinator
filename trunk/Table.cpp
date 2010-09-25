#include <iostream>
#include <stdexcept>
#include <string>
#include "Table.h"
#include <vector>
#include <fstream>
using namespace std;

Node::Node()
{

}

Node::Node(int x)
{
	a = x;
	next = NULL;
}


Node::~Node()
{

}

Node& Node::operator=(const Node& node)
{
	a = node.a;
	next = node.next;
	return (*this);
}

Node& Node::operator++ ()
{
	//tmp = this;
	a = next->a;
	next = next->next;
	return *this;
}

/*void Node::deleteFromQueue()
{
	tmp->next = next;
	a = next->a;
	next = next->next;
	next = NULL;
}*/

Queue::Queue()
{
	head = NULL;
	tail = NULL;
	cur = NULL;
	prev = NULL;
}

Queue::~Queue()
{

}

void Queue::addToQueue(int x)
{
	Node* tmp = new Node(x);
	if (tail != NULL)
	{
		tail->next = tmp;
		tail = tmp;
	}
	else
	{
		head = tmp;
		tail = tmp;
		cur = tmp;
		prev = new Node();
		prev->next = cur;
	}
}

void Queue::addToQueue(Node* node)
{
	if (tail != NULL)
	{
		tail->next = node;
		tail = node;
	}
	else
	{
		head = node;
		tail = node;
	}
}

void Queue::addToQueue(Queue q)
{
	setCurrentToHead();
	Node* tmp;
	while ((tmp = q.headValue()) != NULL)
	{
		int b = tmp->a;
		while ((cur != NULL) && (cur->a < b))
		{
			cur = cur->next;
			prev = prev->next;
		}
		if (head == NULL)
		{
			head = tmp;
		}
		prev->next = tmp;
		tmp->next = cur;
		prev = tmp;
	}
	if (cur == NULL)
	{
		prev ->next = q.headValue();
		tail = prev;
	}
}

void Queue::deleteCurrent()
{
	if (cur == head)
		head = head->next;
	if (cur == tail)
		tail = prev;
	prev->next = cur->next;
	cur->next = NULL;
	cur = prev->next;
}

void Queue::incCurrent()
{
	cur++;
	prev++;
}

Node* Queue::currentNode()
{
	return cur;
}

void Queue::setCurrentToHead()
{
	cur = head;
	prev = new Node();
	prev->next = cur;
}

bool Queue::search(int k)
{
	while ((cur != NULL) && (cur->a < k))
	{
		cur = cur->next;
		prev = prev ->next;
	}
	if ((cur != NULL) && (cur -> a == k))
		return true;
	return false;
}

bool Queue::isEmpty() const
{
	if (head == NULL)
		return true;
	return false;
}

Node* Queue::headValue()
{
	Node* tmp = head;
	if (head != NULL)
		head = head->next;
	return tmp;
}

bool Queue::hasSingleCapacity() const
{
	if (head == tail)
		return true;
	return false;
}

Table::Table()
{

}

Table::Table(int n)
{
	t.resize(n);
	num = n;
	n0 = -1;
}

Table::~Table()
{

}

void Table::addToTable(int i, int j)
{
	if (i < num)
		t[i].addToQueue(j);
	if (n0 < i)
		n0 = i;
}

void Table::addToTable(Node* node, int i)
{
	if (i < num)
		t[i].addToQueue(node);
	if (n0 < i)
		n0 = i;
}

Node* Table::headValue()
{
	Node* tmp;
	while ((n0 >= 0) && ((tmp = t[n0].headValue()) == NULL))
		--n0;
	return tmp;
}

Node* Table::minValue()
{
	Node* tmp;
	while ((n0 < num) && ((tmp = t[n0].headValue()) == NULL))
	{
		++n0;
	}
	return tmp;
}

void Table::setCurrentToHead()
{
	for (int i = 0; i < num; ++i)
	{
		t[i].setCurrentToHead();
	}
}

float Table::currency(int k)
{
	for (int i = 0; i < num; ++i)
	{
		if (t[i].search(k))
			return (float)(1 / (i + 1));
	}
	return 0;
}

void Table::setN0(int i)
{
	n0 = i;
}

int Table::getN0() const
{
	return n0;
}

int Table::search(int k)
{
	for (int i = 0; i < num; ++i)
	{
		if (t[i].search(k))
		{
			return i;
		}
	}
	return -1;
}

Node* Table::current(int i)
{
	Node* tmp = t[i].currentNode();
	t[i].deleteCurrent();
	return tmp;
}

void Table::addTable(Table * tab)
{
	for (int i = 0; i < num; ++i)
	{
		t[i].addToQueue(tab->t[i]);
	}	
}

bool Table::isEmpty() const
{
	for (int i = 0; i < num; ++i)
	{
		if (!t[i].isEmpty()) return false;
	}
	return true;
}

bool Table::isClear() const
{
	int i = 0;
	for (int j = 0; j < num; ++j)
	{
		if (!t[i].isEmpty())
			break;
	}
	if (t[i].hasSingleCapacity() && ((i + 1 >= num) || (t[i + 1].isEmpty())))
		return true;
	return false;
}